import os
import json
import subprocess

test_dir = "./target-test/"
files = os.listdir(test_dir)
main_program_dir = "../build/Debug/"
main_program_name = "my_app.exe"

for filename in files:
    with open(test_dir+filename, "r") as file:
        test_dict = json.loads(file.read())
        for elem in test_dict:
            print(f"NAME: {elem['name']}")
            print(f"INITIAL: {elem['initial']}")
            print(f"FINAL: {elem['final']}")
            print(f"CYCLES: {elem['cycles']}")
            result = subprocess.run([main_program_dir+main_program_name], capture_output=True, text=True)
            print("Return code:", result.returncode)
            print("Output:", result.stdout)
            if result.stderr != "":
                print("Error:", result.stderr)
                break
