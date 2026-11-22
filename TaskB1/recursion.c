#include <stdio.h>
#include <limits.h>

long long calls = 0;

/* Linear recursion: base^exp = base * base^(exp-1). */
long long power_linear(long long base, int exp)
{
    calls++;
    if (exp == 0) return 1;
    return base * power_linear(base, exp - 1);
}

/* Divide-and-conquer recursion: compute the half power exactly once. */
long long power_fast(long long base, int exp)
{
    calls++;
    if (exp == 0) return 1;                 /* TODO 1 completed */
    long long half = power_fast(base, exp / 2);
    long long square = half * half;
    return (exp % 2 == 0) ? square : square * base;
}

int main(void)
{
    calls = 0;
    long long a = power_linear(2, 30);
    printf("linear: %lld in %lld calls\n", a, calls);

    calls = 0;
    long long b = power_fast(2, 30);
    printf("fast : %lld in %lld calls\n", b, calls);

    puts("Call-count experiment (base 1 avoids arithmetic overflow):");
    const int exponents[] = {10, 100, 1000, 10000};
    for (size_t i = 0; i < sizeof exponents / sizeof exponents[0]; ++i) {
        int n = exponents[i];
        calls = 0;
        (void)power_linear(1, n);
        long long linear_calls = calls;
        calls = 0;
        (void)power_fast(1, n);
        printf("n=%d linear_calls=%lld fast_calls=%lld\n",
               n, linear_calls, calls);
    }
    return 0;
}
