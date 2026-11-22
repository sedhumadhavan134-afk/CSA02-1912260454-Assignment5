# CSA02 – C Programming Assignment 5 (CO5)
## Modular, Memory-Aware and Persistent Program Engineering

**Student:** Sedhu Madhavan V  
**Register Number:** 1912260454  
**Institution:** Saveetha Institute of Medical and Technical Sciences (SIMATS), Chennai  
**Repository:** https://github.com/sedhumadhavan134-afk/CSA02-1912260454-Assignment5

> This is the design/report draft. Add actual local measurements, screenshots, GCC version and sanitizer results before submission.

## Case study
The district blood bank manages donor records and blood-group stock. It must register donors, find eligible donors, update stock, and preserve information in files.

## A1 – Functional decomposition and interfaces
Suggested structure chart:
```text
bloodbank
├── register_donor
├── check_eligibility
├── find_donors
│   └── check_eligibility
├── update_stock
├── save_donors / load_donors
└── save_stock / load_stock
```
Prototypes:
- `int register_donor(DonorList *list, const Donor *donor)`
- `int check_eligibility(const Donor *donor, Date today)`
- `size_t find_donors(const Donor *donors, size_t count, const char *group, int *youngest_id)`
- `int update_stock(Stock *stock, size_t count, const char *group, int delta)`
- `int save_donors(const char *path, const Donor *donors, size_t count)`
- `int load_donors(const char *path, DonorList *list)`
- `int save_stock(const char *path, const Stock *stock, size_t count)`
- `int load_stock(const char *path, Stock *stock, size_t capacity, size_t *count)`

Use values for small scalars, const pointers for read-only records/strings, and mutable pointers for caller-owned data that must change. For multiple outputs, either output parameters (count + youngest ID) or a result structure; the result structure groups related outputs and avoids partially optional pointer arguments. Globals do not change asymptotic time or storage, but increase coupling and make tests/reuse harder.

## A2 – Recursion
Digital root recursive design: if n < 10 return n; otherwise sum decimal digits and recurse on that sum. Base case is a single digit; recursive case reduces digit count. Power: for n=0 return 1; compute h=power(base,n/2) once; return h*h for even n and h*h*base for odd n. Linear power makes n+1 calls (O(n) time and O(n) stack); halving power makes O(log n) calls and O(log n) stack. Iterative square-and-multiply keeps O(log n) time and O(1) auxiliary space. For positive n, digital root can also be computed in O(1) as n==0 ? 0 : 1+(n-1)%9.

## A3 – Pointers and command line
For `int *p=stock`: `p+3` points to element 3; `*(p+3)` and `p[3]` read element 3; `*p++` reads element 0 then advances p to element 1. A lowest-stock function returns `&stock[index]`, never the address of a local variable. Alternative index return is also O(n) time/O(1) space and avoids retaining an invalid pointer if a dynamic array is reallocated. Example CLI: `bloodbank find O+`, `bloodbank issue A- 2`; validate argc, operation and group, and reject malformed counts/negative quantities.

## A4 – Dynamic memory
Grow a donor array from capacity 0 to 2, then double. Use a temporary pointer for realloc; on failure keep the old allocation intact and return failure. Doubling has O(n) amortized append time and O(n) total relocation work; fixed increments of 10 can cause O(n²) total copying. Always free the final allocation once. A leak loses the last pointer without freeing; a dangling pointer remains after free/realloc; double-free releases the same allocation twice. Ownership rules and nulling pointers after free prevent these errors.

## A5 – File storage
Write donors as readable text rows using fprintf/fgets or fscanf with validation. Store fixed-size stock records in binary using fwrite/fread. To update one stock record: fseek to index*sizeof(Stock), fread the record, change units, fseek back to the record start and fwrite it. Fixed-size binary update is O(1) record access; rewriting a text file is O(n). Binary is compact and fast but may not be portable across different endianness, padding and ABI layouts; text is more portable and inspectable.

## B1 – Instrumented recursion
The complete-code TODO must compute the half power once, then square it and multiply by base for odd exponents. The expected 2^30 test is 1,073,741,824; linear recursion makes 31 calls and halving recursion 6 calls. Calling power_fast twice in the multiplication duplicates work. Record actual counts and the linear-recursion crash threshold locally; it depends on environment and must not be guessed.

## B2 – Adversarial inputs
Compare unsafe scanf("%s") with bounded input and fgets. Use perror for missing/unreadable files. Validate argc/argv and blood-group names. Run AddressSanitizer or Valgrind and record actual diagnostics. getline reads L characters in O(L) time with O(L) allocated buffer space; caller must free the buffer.

## B3 – Text versus binary
Write/read identical donor records in both formats and compare every field. Measure file sizes and read/write times at 1,000, 10,000 and 100,000 records; update the 50,000th stock record in place in binary and by rewriting text. A one-call fwrite of an array reduces library-call count but requires O(n) contiguous memory; per-record writes can stream with O(1) extra memory.

## B4 – Engineering decision
Load the donor file into a growable list for the nightly report if measured memory fits comfortably and repeated in-memory eligibility checks are needed. For a much larger district, process in batches or maintain a sorted ID/offset index to reduce RAM. Measure the actual resident/malloc memory and execution time; use sanitizer/Valgrind to confirm every allocation is released.

## Evidence and final recommendation
Attach real screenshots, test input/output, timing tables, file sizes and sanitizer summaries. The design uses small cohesive functions, explicit pointer ownership, checked dynamic allocation, and file formats chosen for the access pattern. Do not submit placeholder or invented experimental values.
