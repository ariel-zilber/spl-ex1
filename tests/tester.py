from __future__ import annotations
import os
from dataclasses import dataclass
import sys
from pathlib import Path
import pytest
import subprocess
from typing import List, Union
from tempfile import NamedTemporaryFile
import  json
USE_VALGRIND = True

TEST_DIR = Path(__file__).parent
BASE_DIR="/media/ariel/k8s/spl/ex1/SkeletonFiles(2)"

EXECUTABLE_PATH = Path(Path(TEST_DIR) / "../bin/cRace")

if not EXECUTABLE_PATH.exists():
    print(f"Couldn't find your executable at {EXECUTABLE_PATH}", file=sys.stderr)
    sys.exit(-1)


VALID_DIR = TEST_DIR / "valid"
INVALID_DIR = TEST_DIR / "invalid"


@dataclass
class Output:
    return_code: int
    stdout: str
    stderr: str
    valgrind_out: str

    def compare_to(self, other: Output):
        # "self" is the school's output and "other" is YOUR output
        assert self.return_code == other.return_code, "Return code mismatch(left=school, right=yours)"
        assert self.stdout == other.stdout, "STDOUT mismatch(left=school, right=yours)"
        assert self.stderr == other.stderr, "STDERR mismatch(left=school, right=yours)"

    def check_valgrind_out(self):
        if "ERROR SUMMARY: 0" not in self.valgrind_out:
            print(f"Valgrind failed:\n{self.valgrind_out}", file=sys.stderr)

def run_with_cmd(command_list: List[str], str="", valgrind=False) -> Output:
    """
    Execute the given command list with the input
    """
    valgrind_outfile, valgrind_output = None, ""
    if valgrind:
        valgrind_outfile = NamedTemporaryFile(mode='r+', encoding='utf-8')
        command_list = ['valgrind', '--leak-check=yes', f'--log-file={valgrind_outfile.name}'] + command_list

    print(f"Running command \"{' '.join(command_list)}\"")
    try:
        process = subprocess.run(command_list, shell=False, input=str,
                                 stdout=subprocess.PIPE,
                                 stderr=subprocess.PIPE, text=True)

        if valgrind:
            valgrind_outfile.seek(0)
            valgrind_output = valgrind_outfile.read()
            valgrind_outfile.close()

        return Output(process.returncode, process.stdout, process.stderr, valgrind_output)
    except Exception as e:
        print(f"Error while running subprocess: {e}")
        sys.exit(-1)

TEST_CASES = [
    # the score for the text is 145
    ("test 1",BASE_DIR+"/tests/01.json",BASE_DIR+ "/tests/01_sol.out"),
]
def read_file_content(file_path):
    data=[]
    with open(file_path,'r') as f:
        data=f.read()
    return json.loads(data)

@pytest.mark.parametrize("test_name,input_path,output_path", TEST_CASES)
def test( test_name:str,input_path: str, output_path: str):
    print("Testing: ", input_path)
    my_out = run_with_cmd([str(EXECUTABLE_PATH), input_path], valgrind=USE_VALGRIND)
    actual_content=read_file_content(input_path.replace(".json",".out"))
    expected_content=read_file_content(output_path)
    if actual_content!=expected_content:
        print("Error with test :"+test_name)
        print("Error actual:",actual_content)
        print("Expected error:",expected_content)
        raise Exception("Error with test :"+test_name)
    else:
        print('Test ',test_name,'passed')
    if USE_VALGRIND:
        my_out.check_valgrind_out()

if __name__ == '__main__':
    exit_code = pytest.main([__file__, '-vvs'])
    sys.exit(exit_code)


