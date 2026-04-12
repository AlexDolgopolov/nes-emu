import os
import json
import subprocess
import threading
from multiprocessing import Process
from print_summary import *
import copy

cpu_path = "../build/Debug/my_app.exe"

class InfoContainer():
    def __init__(self, threads, cpu_debug, all_tests, filter_file, numtest, test_name, all_files, filename):
        self.threads = threads
        self.cpu_debug = cpu_debug
        self.all_tests = all_tests
        self.test_name = test_name
        self.all_files = all_files
        self.filename = filename
        self.numtest = numtest
        self.filter_file = filter_file

class TestHandler():
	def __init__(self, name, initial_data, final_data, debug, pid):
		self.pid = pid
		self.initial_data = initial_data
		self.final_data = final_data
		self.debug = debug
		self.name = name
	def _send_msg(self, proc, msg):
		proc.stdin.write(f"{msg}\n")
		proc.stdin.flush()
	def _wait_msg(self, proc, msg):
		while True:
			data = proc.stdout.readline().strip()
			yield data
			if data == msg:
				break
	def start(self):
		self.proc = subprocess.Popen([cpu_path, "1"], stdin=subprocess.PIPE, stdout=subprocess.PIPE, stderr=subprocess.PIPE, text=True)
		self._send_msg(self.proc, "WREGISTERS\n")
		self._send_msg(self.proc, self.initial_data['pc'])
		self._send_msg(self.proc, self.initial_data['s'])
		self._send_msg(self.proc, self.initial_data['a'])
		self._send_msg(self.proc, self.initial_data['x'])
		self._send_msg(self.proc, self.initial_data['y'])
		self._send_msg(self.proc, self.initial_data['p'])
		for line in self._wait_msg(self.proc, "OK"):
			pass
		for ramval in self.initial_data['ram']:
			self._send_msg(self.proc, "WMEMORY\n")
			self._send_msg(self.proc, ramval[0])
			self._send_msg(self.proc, ramval[1])
			for line in self._wait_msg(self.proc, "OK"):
				pass
		self._send_msg(self.proc, "STEP\n")
		extended_cpu_string = ""
		for line in self._wait_msg(self.proc, "OK"):
			extended_cpu_string = extended_cpu_string+line+'\n'
		self._send_msg(self.proc, "RREGISTERS")
		registers_list = list() # pc, s, a, y, p
		for line in self._wait_msg(self.proc, "OK"):
			spl = line.split('=')
			if(len(spl) == 2):
				registers_list.append(int(spl[1].strip(), base = 16))
		ramval_list = list()
		for ramval in self.final_data['ram']:
			self._send_msg(self.proc, "RMEMORY\n")
			self._send_msg(self.proc, ramval[0])
			for line in self._wait_msg(self.proc, "OK"):
				spl = line.split('=')
				if(len(spl) == 2):
					ramval_list.append(int(spl[1].strip(), base = 16))
		compare_result = True
		r_idx = 0
		ram_idx = 0

		
		for key,value in self.final_data.items():
			if key != "ram":
				if value != registers_list[r_idx]:
					compare_result = False
					break
				else:
					r_idx = r_idx + 1
			else:
				for ramval in value:
					if ramval[1] != ramval_list[ram_idx]:
						compare_result = False
						break
					else:
						ram_idx = ram_idx + 1


		real_state = {'pc': registers_list[0], 's': registers_list[1], 'a': registers_list[2], \
					 'x': registers_list[3], 'y': registers_list[4], 'p': registers_list[5], \
					 'ram': copy.deepcopy(self.final_data['ram'])}
		ram_idx = 0
		for ramdata in real_state['ram']:
			ramdata[1] = ramval_list[ram_idx]
			ram_idx = ram_idx + 1

		self._send_msg(self.proc, "END")
		self._wait_msg(self.proc, "OK")
		self.proc.terminate()
		self.proc.wait()
		return [compare_result, real_state, extended_cpu_string]


def create_and_execute(name, initial_data, final_data, debug, pid):
	test = TestHandler(name, initial_data, final_data, debug, pid)
	result = test.start()
	print(f"{pid} : result = {result[0]}")
	if debug:
		print_summary(initial_data, final_data, result[1], name, result[2])
	return result

class FileHandler():
	def __init__(self, test_dir, container):
		self._threads = container.threads
		self._cpu_debug = container.cpu_debug
		self._all_tests = container.all_tests
		self._test_name = container.test_name
		self._all_files = container.all_files
		self._filename = container.filename
		self._numtest = container.numtest
		self._filter_file = container.filter_file
		self._test_dir = test_dir
		self.files = os.listdir(test_dir)
		self.threads_list = []
		self.threads_clear = 0
	def wait_thread(self, waitlen):
		while(True):
			for thread in self.threads_list:
				if not thread.is_alive():
					self.threads_list.remove(thread)
			if len(self.threads_list) < waitlen:
				break
	def run_test_in_file(self):
		for filename in self.files:
			if filename != self._filename:
				continue
			with open(self._test_dir+filename, "r") as file:
				test_json_dict = json.loads(file.read())
				for test in test_json_dict:
					if test['name'] != self._test_name:
						continue
					create_and_execute(test['name'], test['initial'], test['final'], self._cpu_debug, test['name'])
		pass
	def run_all_test_in_file(self):
		for filename in self.files:
			if filename != self._filename:
				continue
			with open(self._test_dir+filename, "r") as file:
				test_json_dict = json.loads(file.read())
				numtest_ctr = 0
				for test in test_json_dict:
					if self._numtest != 0:
						if numtest_ctr >= self._numtest:
							self.wait_thread()
							return
						numtest_ctr = numtest_ctr+1
					if len(self.threads_list) >= self._threads:
						self.wait_thread()
					thread = threading.Thread(target=create_and_execute, args=(test['name'], test['initial'], test['final'], self._cpu_debug, test['name']))
					self.threads_list.append(thread)
					thread.start()
					self.wait_thread(self._threads)
			self.wait_thread(waitlen = 1)
		pass
	def run_tests(self):
		file_filter = False
		file_filter_list = []
		if self._filter_file != "":
			file_filter = True
			with open(self._filter_file, "r") as file:
				for readline in file:
					file_filter_list.append(readline.strip('\n'))
		for filename in self.files:
			if file_filter:
				try:
					file_filter_list.index(filename)
				except ValueError:
					print(f"not find {filename}")
					continue
			with open(self._test_dir+filename, "r") as file:
				test_json_dict = json.loads(file.read())
				numtest_ctr = 0
				for test in test_json_dict:
					if self._numtest != 0:
						if numtest_ctr >= self._numtest:
							self.wait_thread()
							break
						numtest_ctr = numtest_ctr+1
					if len(self.threads_list) >= self._threads:
						self.wait_thread()
					thread = threading.Thread(target=create_and_execute, args=(test['name'], test['initial'], test['final'], self._cpu_debug, test['name']))
					self.threads_list.append(thread)
					thread.start()
					self.wait_thread(self._threads)
			self.wait_thread(waitlen = 1)
	def start(self):
		if self._all_files:
			self.run_tests()
		if (not self._all_files) and self._all_tests:
			self.run_all_test_in_file()
		if (not self._all_files) and (not self._all_tests):
			self.run_test_in_file()
		exit()
