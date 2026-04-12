import signal
import sys
import time
import re
from test_env import *

def signal_handler(sig, frame):
    print('\nВы нажали Ctrl+C! Завершаю программу...')
    sys.exit(0)

signal.signal(signal.SIGINT, signal_handler)
container = InfoContainer(threads = 30, cpu_debug = True, all_tests = False, filter_file = "./valid_opcodes.txt", numtest=30, test_name = "fd b7 c5", all_files = False, filename = "c9.json")
container1 = InfoContainer(threads = 30, cpu_debug = False, all_tests = True, filter_file = "./valid_opcodes.txt", numtest=0, test_name = "24 1a 14", all_files = False, filename = "e0.json")
file_handler = FileHandler("./target/nes6502/v1/", container1)
file_handler.start()

