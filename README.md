# OSN 2019 Problem Repository

Problem repository of **OSN 2019** (also known internationally as
**TOKI OSN Open Contest 2019**).

## Problems

| Alias | Slug                            | Title (id)           | Title (en)               | Type        |
| ----- | ------------------------------- | -------------------- | ------------------------ | ----------- |
| 0A    | `osn-2019-mengawasi-peserta`    | Mengawasi Peserta    | Invigilating Contestants | output-only |
| 0B    | `osn-2019-berbagi-harta`        | Berbagi Harta        | Treasure Sharing         | batch       |
| 0C    | `osn-2019-mengadakan-pesta`     | Mengadakan Pesta     | Organizing Party         | interactive |
| 1A    | `osn-2019-mengumpulkan-peserta` | Mengumpulkan Peserta | Gathering Contestants    | batch       |
| 1B    | `osn-2019-pertahanan-manado`    | Pertahanan Manado    | Manado Defense           | batch       |
| 1C    | `osn-2019-rekreasi-osn`         | Rekreasi OSN         | OSN Excursion            | output-only |
| 2A    | `osn-2019-tempat-wisata`        | Tempat Wisata        | Tourist Attraction       | batch       |
| 2B    | `osn-2019-mencari-emas`         | Mencari Emas         | Detecting Gold           | interactive |
| 2C    | `osn-2019-penyebaran-hoaks`     | Penyebaran Hoaks     | Hoax Spreading           | batch       |

## Credits

| Slug                            | Problem Author(s)                                    |
| ------------------------------- | ---------------------------------------------------- |
| `osn-2019-mengawasi-peserta`    | Jonathan Irvin Gunawan                               |
| `osn-2019-berbagi-harta`        | Jonathan Irvin Gunawan, Prabowo Djonatan             |
| `osn-2019-mengadakan-pesta`     | Jonathan Irvin Gunawan, Lie Maximilianus Maria Kolbe |
| `osn-2019-mengumpulkan-peserta` | Jonathan Irvin Gunawan, Lie Maximilianus Maria Kolbe |
| `osn-2019-pertahanan-manado`    | Ashar Fuadi                                          |
| `osn-2019-rekreasi-osn`         | Jonathan Irvin Gunawan, Lie Maximilianus Maria Kolbe |
| `osn-2019-tempat-wisata`        | Suhendry Effendy                                     |
| `osn-2019-mencari-emas`         | Jonathan Irvin Gunawan                               |
| `osn-2019-penyebaran-hoaks`     | Suhendry Effendy                                     |

## Upsolving

The problem statements and upsolving are available
[on TLX](https://training.ia-toki.org/archives/66).

## Problem Repository Structure

Each problem contains a problem directory root (e.g.
`osn-2019-mengawasi-peserta/` in this directory is a problem directory root). A
problem directory root contains **exactly** the following directories and files:

- [Communicator (optional) (`communicator`)](#communicator-optional)
- [Configuration file (`config.json`)](#configuration-file)
- [EN problem description (`description-en.html`)](#en-problem-description)
- [ID problem description (`description-id.html`)](#id-problem-description)
- [Helper files directory (optional) (`helpers/`)](#helper-files-directory-optional)
- [Open subtasks directory (optional) (`opens/`)](#open-subtasks-directory-optional)
- [Render directory (optional) (`render/`)](#render-directory-optional)
- [Sample cases directory (`samples/`)](#sample-cases-directory)
- [Output validator (optional) (`scorer.cpp`)](#output-validator-optional)
- [Model solution (`solution.cpp`)](#model-solution)
- [Solutions directory (`solutions/`)](#solutions-directory)
- [Test case generator (`spec.cpp`)](#test-case-generator)
- [Input verifier (`verifier.py`)](#input-verifier)

### Communicator (optional)

Communicator is named `communicator.cpp`. It follows
[tcframe communicator format](http://docs.tcframe.org/en/stable/topic-guides/styles.html#communicator).
If the problem type is not interactive, this file can be ignored.

### Configuration file

Configuration file is named `config.json`. Configuration file makes it easier
for automated tools and problem uploader to choose the correct
settings/configurations in online judges. Configuration file contains a JSON
object contains the following:

#### `"title_en"` (str)

Problem Title in English.

#### `"title_id"` (str)

Problem Title in Bahasa.

#### `"memory_limit_mb"` (int)

Problem Memory Limit (in MB).

#### `"time_limit_ms"` (int)

Problem Time Limit (in ms).

#### `"points"` (List[int])

The points of each subtasks. The length of this array indicates the number of
subtasks. The i-th element of this array is the points of the i-th subtask.

#### `"sample_cases"` (List[List[bool]])

Sample cases properties. The length of this array indicates the number of sample
cases. The i-th element of this array contains S booleans, where S is the number
of subtasks. The j-th element of this array indicates whether the i-th sample
case satisfies the j-th subtask constraint.

#### `"test_groups"` (List[List[bool]])

Test groups properties. The length of this array indicates the number of test
groups. The i-th element of this array contains S booleans, where S is the
number of subtasks. The j-th element of this array indicates whether every test
case in the i-th test group satisfies the j-th subtask constraint.

#### `"solutions"` (List[Object])

Solutions properties. The length of this array indicates the number of solutions
(excluding model solution). The i-th element of this array contains an object.
The object contains the following:

- `filename` (str): The filename of the solution in the `solution/` directory.
  This file must exists.
- `verdicts` (List[str]): An array containing S elements, where S is the number
  of subtasks. The i-th element of this array represents the expected verdict of
the i-th subtask, either one of the following:
  - `ACCEPTED`: The solution is expected to be correct.
  - `WRONG_ANSWER`: The solution is expected to produce a wrong answer.
  - `TIME_LIMIT_EXCEEDED`: The solution is expected to timed out.
  - `RUNTIME_ERROR`: The solution is expected to crash.
  - `INCORRECT_SOLUTION`: The solution is expected to be not correct. This is
    used when it is not clear whether the solution will crash or produce a wrong
    answer, usually due to an undefined behaviour.
  - `DO_NOT_RUN`: Do not use this for now.

#### `"interactive"` (Optional[bool])

Interactive-type problem label. If left blank, the default value is `False`.

### EN problem description

English problem description is named `description-en.html`. Please refer to the
`description-en.html` in the sample problem for the template of this HTML. Note
that the sample cases are not included in this HTML file.

Three custom tags are used:
- A `<samplecase{i}/>` tag is used to indicate where to put the i-th sample
  case.
- A `<open{i}/>` tag is used to indicate where to put the i-th open subtask.
- A `<subtask{i}/>` tag is used to indicate where to put the i-th subtask
  header.

The finalized problem description HTML can be generated using
[gen_problem.py](https://github.com/jonathanirvings/osn-2019-utils/blob/master/gen_problem.py)
utility.

### ID problem description

Bahasa problem description is named `description-id.html`. It has the same
format as [EN problem description](#en-problem-description)

### Helper files directory (optional)

Helper files directory is named `helpers/`. This directory exists if there
is/are helper files (such as scripts) specific to the problem. For example, a
helper file could be a Python script to plot input files for geometry problems.

### Open subtasks directory (optional)

Open subtasks directory is named `opens/`. The directory contains `open_{i}.in`
for all 1 ≤ i ≤ N where N is the number of open subtasks. Intuitively,
`open_{i}.in` contains the i-th open subtask input. If there is no open subtask,
this directory can be ignored.

### Render directory (optional)

Render directory is named `render/`. This directory contains supplementary files
to the problem description (e.g. images). If there is no supplementary files,
this directory can be ignored.

### Sample cases directory

Sample cases directory is named `samples/`. The directory contains
`sample_{i}.in` and `sample_{i}.out` for all 1 ≤ i ≤ N where N is the number of
sample cases. Intuitively, `sample_{i}.in` contains the i-th sample input and
`sample_{i}.out` contains the i-th sample output.

### Output validator (optional)

Output validator is named `scorer.cpp`. It follows
[tcframe output validator format](http://docs.tcframe.org/en/stable/topic-guides/styles.html#scorer).
Note that `scorer.cpp` must exist in **all** non-interactive type problems. If
the problem type is interactive, this file can be ignored.

### Model solution

Model solution is named `solution.cpp`. This solution is used to generate the
output of each test data. The output produced by this solution for
`sample_{i}.in` must exactly match `sample_{i}.out`.

### Solutions directory

Solutions directory is named `solutions/`. Solutions other than model solution
(usually for testing purposes) are stored in this directory.

### Test case generator

Test case generator is named `spec.cpp`. It uses
[tcframe](http://docs.tcframe.org/en/stable/index.html)
[version 1.6.0](https://github.com/ia-toki/tcframe/releases/tag/v1.6.0). The
test case generator must **not** specify the number of points given to any
subtask. For all 1 ≤ i ≤ N where N is the number of open subtasks, the generated
i-th test group must only contains one test case and matches
`opens/open_{i}.in`.

### Input verifier

Input verifier is named `verifier.py`. It reads the input file from `stdin` and
the subtask index (1-based) from `argv[1]`. It should exit gracefully and
produce no output if the input is correct, and should crash if the input is not
correct.

## Several notes

### C++ versions

All C++ scripts (testdata generators, solutions, output validators, and
communicators) must be compilable with C++11.

### Python versions

All Python scripts (input verifiers) must be runnable with Python 3.

## License

All tasks and materials are published under the [Creative Commons Attribution
(CC-BY)](https://en.wikipedia.org/wiki/Creative_Commons_license) License.
