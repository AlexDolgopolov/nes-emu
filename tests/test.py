import os
import json
import subprocess
import signal
import sys

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


for filename in files:
    with open(test_dir+filename, "r") as file:
        test_dict = json.loads(file.read())
        for elem in test_dict:
            print(f"NAME: {elem['name']}")
            print(f"INITIAL: {elem['initial']}")
            print(f"FINAL: {elem['final']}")
            print(f"CYCLES: {elem['cycles']}")
            print(type(elem['initial']))
            proc = subprocess.Popen([main_program_dir+main_program_name], stdin=subprocess.PIPE, stdout=subprocess.PIPE, stderr=subprocess.PIPE, text=True)
            print("Test started")
            while proc.stdout.readline().strip() != "CPU STARTED":
                pass
            send_and_wait(proc, "CMD\n", "OK")
            send_and_wait(proc, elem['name']+"\n", "OK")
            send_and_wait(proc, "PC\n", "OK")
            send_and_wait(proc, elem['initial']['pc']+"\n", "OK")
            send_and_wait(proc, "S\n", "OK")
            send_and_wait(proc, elem['initial']['s']+"\n", "OK")
            send_and_wait(proc, "A\n", "OK")
            send_and_wait(proc, elem['initial']['a']+"\n", "OK")
            send_and_wait(proc, "X\n", "OK")
            send_and_wait(proc, elem['initial']['x']+"\n", "OK")
            send_and_wait(proc, "Y\n", "OK")
            send_and_wait(proc, elem['initial']['y']+"\n", "OK")
            send_and_wait(proc, "P\n", "OK")
            send_and_wait(proc, elem['initial']['p']+"\n", "OK")
            for ramdata in elem['initial']['ram']:
                send_and_wait(proc, "RAM\n", "OK")
                send_and_wait(proc, f"{ramdata[0]}", "OK")
                send_and_wait(proc, f"{ramdata[1]}", "OK")
            while proc.stdout.readline().strip() != "TEST FINISH":
                pass
            pc = proc.stdout.readline()
            s = proc.stdout.readline()
            a = proc.stdout.readline()
            x = proc.stdout.readline()
            y = proc.stdout.readline()
            p = proc.stdout.readline()
            send_and_wait(proc, "READRAM\n", "OK")
            fin_ramdata = list()
            for ramdata in elem['initial']['ram']:
                send_and_wait(proc, "RADDR\n", "OK")
                send_and_wait(proc, ramdata[0], "OK")
                fin_ramdata.append(proc.stdout.readline())
            print(f"{pc},{s},{a},{x},{y},{p}")
            print(fin_ramdata)
            print("TODO: MAKE TEST DATA COMPARE")


def send_and_wait(proc, msg, waitstr):
    proc.stdin.write(msg)
    proc.stdin.flush()
    while proc.stdout.readline().strip() != waitstr:
        pass


