# B2 – Adversarial Inputs

An unbounded `scanf("%s", name)` does not know the destination capacity and can overwrite adjacent memory when the token is too long. `scanf("%15s", name)` is bounded for a 16-byte array; `fgets(name, sizeof name, stdin)` also bounds the read and can preserve spaces. The supplied demonstration uses `fgets` and detects truncation. `perror` reports file-open errors, and the CLI validates argument count, operation and blood group.

The included `scanf_width_demo.c` deliberately uses a width limit so it is safe to run. Do not test an unbounded `%s` against an overlong string outside a controlled sanitizer exercise.
