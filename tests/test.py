import os
import json
import subprocess
import signal
import sys
import time

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
            print(data)
        if data == msg:
            break


def send_msg(proc, msg):
#    print(f"send: {msg}\n")
    proc.stdin.write(f"{msg}\n")
    proc.stdin.flush()


for filename in files:
    with open(test_dir+filename, "r") as file:
        test_dict = json.loads(file.read())
        for elem in test_dict:
            print(f"NAME: {elem['name']}")
            print(f"INITIAL:")
            for key,value in elem['initial'].items():
                if key != "ram":
                    print(f"{key}, {hex(value)}")
                else:
                    print("ram")
                    for ramval in value:
                        print(f"{hex(ramval[0])}, {hex(ramval[1])}")
            print(f"FINAL: ")
            for key,value in elem['final'].items():
                if key != "ram":
                    print(f"{key}, {hex(value)}")
                else:
                    print("ram")
                    for ramval in value:
                        print(f"{hex(ramval[0])}, {hex(ramval[1])}")
            print(f"CYCLES: {elem['cycles']}")
            print(type(elem['initial']))
            proc = subprocess.Popen([main_program_dir+main_program_name, "1"], stdin=subprocess.PIPE, stdout=subprocess.PIPE, stderr=subprocess.PIPE, text=True)
            send_msg(proc, "WREGISTERS\n")
            send_msg(proc, elem['initial']['pc'])
            send_msg(proc, elem['initial']['s'])
            send_msg(proc, elem['initial']['a'])
            send_msg(proc, elem['initial']['x'])
            send_msg(proc, elem['initial']['y'])
            send_msg(proc, elem['initial']['p'])
            wait_msg(proc, "OK")
            for ramval in elem['initial']['ram']:
                send_msg(proc, "WMEMORY\n")
                send_msg(proc, ramval[0])
                send_msg(proc, ramval[1])
                wait_msg(proc, "OK")
            send_msg(proc, "STEP\n")
            wait_msg(proc, "OK")
            send_msg(proc, "RREGISTERS")
            wait_msg(proc, "OK")
            for ramval in elem['initial']['ram']:
                send_msg(proc, "RMEMORY\n")
                send_msg(proc, ramval[0])
                wait_msg(proc, "OK")
            send_msg(proc, "END")
            wait_msg(proc, "OK")
            proc.terminate()
            proc.wait()
            exit()

