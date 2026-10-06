from pathlib import Path
import json,subprocess
root=Path(__file__).resolve().parents[1]
json.loads((root/"sample-data/example.json").read_text())
subprocess.run(["g++","-std=c++17","-Wall","-Wextra","-Werror","tests/policy_test.cpp","-o","/tmp/offline-test"],cwd=root,check=True)
subprocess.run(["/tmp/offline-test"],check=True)
print("Dark hysteresis, debounce, bounce, RGB rule, invalid ADC and rollover passed")
