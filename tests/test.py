import signal
import sys
import time
import re
from test_env import *



def signal_handler(sig, frame):
    print('\nВы нажали Ctrl+C! Завершаю программу...')
    sys.exit(0)

signal.signal(signal.SIGINT, signal_handler)

container = InfoContainer(threads = 30, cpu_debug = False, all_tests = True, filter_file = "./valid_opcodes.txt", numtest=10, test_name = "c4 74 d7", all_files = True, filename = "00.json")
file_handler = FileHandler("./target/6502/v1/", container)
file_handler.start()

