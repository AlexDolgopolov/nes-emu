import signal
import sys
import time
import re
from test_env import *



def signal_handler(sig, frame):
    print('\nВы нажали Ctrl+C! Завершаю программу...')
    sys.exit(0)

if __name__ == "__main__":
    signal.signal(signal.SIGINT, signal_handler)

    container = InfoContainer(threads = 30, cpu_debug = False, all_tests = True, test_name = "6c ff 32", all_files = False, filename = "85.json")
    file_handler = FileHandler("./target/6502/v1/", container)
    file_handler.start()

