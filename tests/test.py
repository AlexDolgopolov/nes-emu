import os
import json
import subprocess
import signal
import sys
import time
import re

test_dir = "./target-test/"
files = os.listdir(test_dir)
main_program_dir = "../build/Debug/"
main_program_name = "my_app.exe"
proc = None

def signal_handler(sig, frame):
    print('\nВы нажали Ctrl+C! Завершаю программу...')
    if proc != None:
        proc.terminate()
        proc.wait()
    sys.exit(0)

signal.signal(signal.SIGINT, signal_handler)

def wait_msg(proc, msg):
    while True:
        data = proc.stdout.readline().strip()
        if data != "":
            yield data
        if data == msg:
            break

cpu_debug = False

def send_msg(proc, msg):
    if cpu_debug:
        print(f"send: {msg}\n")
    proc.stdin.write(f"{msg}\n")
    proc.stdin.flush()

#temp variable TODO remove

test_dec = 798
all_tests = False


for filename in files:
    with open(test_dir+filename, "r") as file:
        test_dict = json.loads(file.read())
        for elem in test_dict:
            if all_tests == True:
                if test_dec != 0:
                    test_dec = test_dec - 1
                    continue
            print(f"NAME: {elem['name']}")
            if cpu_debug:
                print(f"INITIAL:")
            for key,value in elem['initial'].items():
                if key != "ram":
                    if cpu_debug:
                        print(f"{key}, {hex(value)}")
                else:
                    if cpu_debug:
                        print("ram")
                    for ramval in value:
                        if cpu_debug:
                            print(f"{hex(ramval[0])}, {hex(ramval[1])}")
            if cpu_debug:
                print(f"FINAL: ")
            for key,value in elem['final'].items():
                if key != "ram":
                    if cpu_debug:
                        print(f"{key}, {hex(value)}")
                else:
                    if cpu_debug:
                        print("ram")
                    for ramval in value:
                        if cpu_debug:
                            print(f"{hex(ramval[0])}, {hex(ramval[1])}")
            if cpu_debug:
                print(f"CYCLES: {elem['cycles']}")
            proc = subprocess.Popen([main_program_dir+main_program_name, "1"], stdin=subprocess.PIPE, stdout=subprocess.PIPE, stderr=subprocess.PIPE, text=True)
            send_msg(proc, "WREGISTERS\n")
            send_msg(proc, elem['initial']['pc'])
            send_msg(proc, elem['initial']['s'])
            send_msg(proc, elem['initial']['a'])
            send_msg(proc, elem['initial']['x'])
            send_msg(proc, elem['initial']['y'])
            send_msg(proc, elem['initial']['p'])
            for line in wait_msg(proc, "OK"):
                if cpu_debug:
                    print(line)
            for ramval in elem['initial']['ram']:
                send_msg(proc, "WMEMORY\n")
                send_msg(proc, ramval[0])
                send_msg(proc, ramval[1])
                for line in wait_msg(proc, "OK"):
                    if cpu_debug:
                        print(line)
            send_msg(proc, "STEP\n")
            for line in wait_msg(proc, "OK"):
                if cpu_debug:
                    print(line)
            send_msg(proc, "RREGISTERS")
            registers_list = list() # pc, s, a, y, p
            for line in wait_msg(proc, "OK"):
                if cpu_debug:
                    print(line)
                spl = line.split('=')
                if(len(spl) == 2):
                    registers_list.append(int(spl[1].strip(), base = 16))
            ramval_list = list()
            for ramval in elem['final']['ram']:
                send_msg(proc, "RMEMORY\n")
                send_msg(proc, ramval[0])
                for line in wait_msg(proc, "OK"):
                    if cpu_debug:
                        print(line)
                    spl = line.split('=')
                    if(len(spl) == 2):
                        ramval_list.append(int(spl[1].strip(), base = 16))
            if cpu_debug:
                print("start compare")
            compare_result = True
            r_idx = 0
            ram_idx = 0
            for key,value in elem['final'].items():
                if key != "ram":
                    if value != registers_list[r_idx]:
                        compare_result = False
                        if cpu_debug:
                            print(f"{key}: {hex(value)}, {hex(registers_list[r_idx])}")
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
            print(f"compare result = {compare_result}")
            send_msg(proc, "END")
            wait_msg(proc, "OK")
            proc.terminate()
            proc.wait()
            if compare_result == False:
                exit()
            if all_tests == True:
                exit()

