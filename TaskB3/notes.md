# B3 – Text versus Binary Experiments

Run `benchmark.c` for 1,000, 10,000 and 100,000 generated records; it reports text/binary file sizes and read/write CPU times from the current run. Run `update_experiment.c` to compare an in-place update of zero-based record index 49,999 in the binary file with a full text rewrite. `file_benchmark.c` is the completed supplied TODO and checks that an out-of-range record update fails.

Record the results from repeated runs. `clock()` measures process CPU time and very short runs can be noisy; do not treat a single measurement as universal.
