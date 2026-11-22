# CSA02 – C Programming Assignment 5 (CO5)
**Student:** Sedhu Madhavan V  
**Register Number:** 1912260454  
**Institution:** Saveetha Institute of Medical and Technical Sciences (SIMATS), Chennai  
**Topic:** Modular, Memory-Aware and Persistent Program Engineering

## Compiler
Record the actual local version with `gcc --version`. Compile with `-std=c11 -Wall -Wextra -pedantic`.

## Build and run
- B1 recursion: `gcc -std=c11 -Wall -Wextra -pedantic TaskB1/recursion.c -o TaskB1/recursion`; run `./TaskB1/recursion`.
- B2 adversarial input demo: `gcc -std=c11 -Wall -Wextra -pedantic TaskB2/adversarial.c -o TaskB2/adversarial`; run `./TaskB2/adversarial`.
- B3 text/binary experiment: `gcc -std=c11 -Wall -Wextra -pedantic TaskB3/file_benchmark.c -o TaskB3/file_benchmark`; run `./TaskB3/file_benchmark`.
- B4 growable list: `gcc -std=c11 -Wall -Wextra -pedantic TaskB4/growable_list.c -o TaskB4/growable_list`; run `./TaskB4/growable_list`.

## Contents
- Part A design: function decomposition/interfaces, recursion, pointers/CLI, realloc strategy and text/binary file design.
- Part B implementation: recursive call instrumentation, adversarial input/error handling, text-versus-binary file benchmarks and growable donor list.
- `Assignment5_Report.md` consolidates the design and engineering decision.

## Evidence to capture locally
- [ ] Actual GCC version, compile commands and screenshots for each program.
- [ ] B1 call counts for n=10,100,1000,10000 and measured linear-recursion stack limit (do not guess).
- [ ] B2 long-name, missing/read-only file, invalid CLI and sanitizer/Valgrind outputs.
- [ ] B3 file sizes and read/write/update timings for 1,000, 10,000 and 100,000 records, plus the 50,000th-record update.
- [ ] B4 memory usage and sanitizer/Valgrind summary for a large donor list.

No crash limits, timings, memory measurements or sanitizer results are fabricated in this repository. Capture them on the machine used for submission.
