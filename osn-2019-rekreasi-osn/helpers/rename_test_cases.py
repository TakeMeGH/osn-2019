# Rename test cases in testcases.zip and create inputs.zip to be uploaded for
# contestants.
# Call this script in the problem directory root after running gen_problem.py.

import os
import zipfile

_SAMPLE_COUNT = 2
_TEST_CASE_COUNT = 10

_SOURCE_SAMPLE_FORMAT = "osn-2019-rekreasi-osn_sample_{}"
_DESTINATION_SAMPLE_FORMAT = "rekreasi_sample_{}"
_SOURCE_TEST_CASE_FORMAT = "osn-2019-rekreasi-osn_{}_1"
_DESTINATION_TEST_CASE_FORMAT = "rekreasi_{}"

def main():
  if os.path.exists(os.path.join("generated", "testcases.zip")):
    zip = zipfile.ZipFile('generated/testcases.zip')
    zip.extractall()

    os.remove(os.path.join("generated", "testcases.zip"))
    testcases_zip = zipfile.ZipFile(os.path.join("generated", "testcases.zip"),
                                    "w")
    inputs_zip = zipfile.ZipFile(os.path.join("generated", "inputs.zip"), "w")
    
    for suffix in [".in", ".out"]:
      for sample in range(1, _SAMPLE_COUNT + 1):
        testcases_zip.write(_SOURCE_SAMPLE_FORMAT.format(sample) + suffix,
                            _DESTINATION_SAMPLE_FORMAT.format(sample) + suffix)
      for test_case in range(1, _TEST_CASE_COUNT + 1):
        testcases_zip.write(
            _SOURCE_TEST_CASE_FORMAT.format(test_case) + suffix,
            _DESTINATION_TEST_CASE_FORMAT.format(test_case) + suffix)

    for sample in range(1, _SAMPLE_COUNT + 1):
      inputs_zip.write(_SOURCE_SAMPLE_FORMAT.format(sample) + ".in",
                       _DESTINATION_SAMPLE_FORMAT.format(sample) + ".in")
    for test_case in range(1, _TEST_CASE_COUNT + 1):
      inputs_zip.write(_SOURCE_TEST_CASE_FORMAT.format(test_case) + ".in",
                       _DESTINATION_TEST_CASE_FORMAT.format(test_case) + ".in")

    testcases_zip.close()
    inputs_zip.close()

    for suffix in [".in", ".out"]:
      for sample in range(1, _SAMPLE_COUNT + 1):
        os.remove(_SOURCE_SAMPLE_FORMAT.format(sample) + suffix)
      for test_case in range(1, _TEST_CASE_COUNT + 1):
        os.remove(_SOURCE_TEST_CASE_FORMAT.format(test_case) + suffix)


if __name__ == "__main__":
  main()
