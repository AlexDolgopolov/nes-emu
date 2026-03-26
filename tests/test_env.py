import os
import json
import subprocess

cpu_path = "../build/Debug/my_app.exe"

class InfoContainer():
    def __init__(self, threads, cpu_debug, all_tests, test_name, all_files, filename):
        self.threads = threads
        self.cpu_debug = cpu_debug
        self.all_tests = all_tests
        self.test_name = test_name
        self.all_files = all_files
        self.filename = filename

class TestHandler():
	def __init__(self, name, initial_data, final_data, debug, pid):
		self.pid = pid
		self.initial_data = initial_data
		self.final_data = final_data
		self.debug = debug
		self.name = name
	def _send_msg(self, proc, msg):
		if self.debug:
			if type(msg) is int:
				print(f"send: {hex(msg)}\n", end = "")
			else:
				print(f"send: {msg}\n", end = "")
		proc.stdin.write(f"{msg}\n")
		proc.stdin.flush()
	def _wait_msg(self, proc, msg):
		while True:
			data = proc.stdout.readline().strip()
			if data != "":
				if self.debug:
					print(data)
			yield data
			if data == msg:
				break
	def start(self):
		print(f"TEST = {self.name}")
		if self.debug:
			print(f"INITIAL:")
			print(self.initial_data)
			print(f"FINAL: ")
			print(self.final_data)
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
		for line in self._wait_msg(self.proc, "OK"):
			pass
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
				if self.debug:
					print(f"{key}: {hex(value)}, {hex(registers_list[r_idx])}")
				break
			else:
				r_idx = r_idx + 1
		else:
			for ramval in value:
				if ramval[1] != ramval_list[ram_idx]:
					if self.debug:
						print(f"ram compare error - {hex(ramval[0])}: {hex(ramval[1])}, {hex(ramval_list[ram_idx])}")
					compare_result = False
					break
				else:
					ram_idx = ram_idx + 1
		print(f"compare result = {compare_result}")
		self._send_msg(self.proc, "END")
		self._wait_msg(self.proc, "OK")
		self.proc.terminate()
		self.proc.wait()
		return compare_result


def create_and_execute(name, initial_data, final_data, debug, pid):
	test = TestHandler(name, initial_data, final_data, debug, pid)
	return test.start()

class FileHandler():
	def __init__(self, test_dir, container):
		self._threads = container.threads
		self._cpu_debug = container.cpu_debug
		self._all_tests = container.all_tests
		self._test_name = container.test_name
		self._all_files = container.all_files
		self._filename = container.filename
		self._test_dir = test_dir
		self.files = os.listdir(test_dir)
	def start(self):
		for filename in self.files:
			if not self._all_files:
				if filename != self._filename:
					continue
			with open(self._test_dir+filename, "r") as file:
				test_json_dict = json.loads(file.read())
				threads_list = []
				for test in test_json_dict:
					if not self._all_tests:
						if test['name'] != self._test_name:
							continue
					create_and_execute(test['name'], test['initial'], test['final'], self._cpu_debug, 0)
		exit()



