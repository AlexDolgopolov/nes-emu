import signal
import sys
import time
import re
from test_env import *



def signal_handler(sig, frame):
    print('\nВы нажали Ctrl+C! Завершаю программу...')
    sys.exit(0)

signal.signal(signal.SIGINT, signal_handler)

container = InfoContainer(threads = 1, cpu_debug = True, all_tests = False, test_name = "00 b0 ba", all_files = False, filename = "00.json")
file_handler = FileHandler("./target/6502/v1/", container)
file_handler.start()

