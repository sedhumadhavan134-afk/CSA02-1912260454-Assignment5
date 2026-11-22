# CSA02 – C Programming Assignment 5 (CO5)
**Student:** Sedhu Madhavan V  
**Register Number:** 1912260454  
**Institution:** Saveetha Institute of Medical and Technical Sciences (SIMATS), Chennai  
**Topic:** Modular, Memory-Aware and Persistent Program Engineering

## Compiler
Record the actual local version with `gcc --version`. Compile with `-std=c11 -Wall -Wextra -pedantic`.

## Build and run
- B1 recursion: `gcc -std=c11 -Wall -Wextra -pedantic TaskB1/recursion.c -o TaskB1/recursion`; run `./TaskB1/recursion`.
- B2 adversarial input: `gcc -std=c11 -Wall -Wextra -pedantic TaskB2/adversarial.c -o TaskB2/adversarial`; run `./TaskB2/adversarial find O+` after entering a name.
- B2 bounded scanf comparison: `gcc -std=c11 -Wall -Wextra -pedantic TaskB2/scanf_width_demo.c -o TaskB2/scanf_demo`.
- B3 TODO update: `gcc -std=c11 -Wall -Wextra -pedantic TaskB3/file_benchmark.c -o TaskB3/file_benchmark`.
- B3 format benchmark: `gcc -std=c11 -Wall -Wextra -pedantic TaskB3/benchmark.c -o TaskB3/benchmark`.
- B3 50,000th-record update experiment: `gcc -std=c11 -Wall -Wextra -pedantic TaskB3/update_experiment.c -o TaskB3/update_experiment`.
- B4 growable list TODO: `gcc -std=c11 -Wall -Wextra -pedantic TaskB4/growable_list.c -o TaskB4/growable_list`.
- B4 nightly donor report: `gcc -std=c11 -Wall -Wextra -pedantic TaskB4/nightly_report.c -o TaskB4/nightly_report`; run `./TaskB4/nightly_report TaskB4/sample_donors.txt <current-day-ordinal> <minimum-interval-days>`.

## Contents
- `Assignment5_Report.md`: Part A design and Part B interpretation framework.
- `TaskB1`: digital root and instrumented linear/halving power.
- `TaskB2`: bounded input, file-error and CLI validation examples.
- `TaskB3`: completed binary update and text/binary timing experiments.
- `TaskB4`: realloc donor list and file-loaded eligibility report.

## Evidence to capture locally
- [ ] Actual GCC version, compile commands and screenshots for each program.
- [ ] B1 call counts for n=10,100,1000,10000 and measured linear-recursion stack limit (do not guess).
- [ ] B2 long-name, missing/read-only file, invalid CLI and sanitizer/Valgrind outputs.
- [ ] B3 file sizes and read/write/update timings for 1,000, 10,000 and 100,000 records, plus the 50,000th-record update.
- [ ] B4 memory usage and sanitizer/Valgrind summary for a large donor list.

No crash limits, timings, memory measurements or sanitizer results are fabricated. Capture them on the machine used for submission.
