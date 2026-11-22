#include <stdio.h>
#include <limits.h>

long long digital_root_recursive(long long n)
{
    if (n < 0) n = -n;
    if (n < 10) return n;
    long long sum = 0;
    while (n > 0) { sum += n % 10; n /= 10; }
    return digital_root_recursive(sum);
}

long long digital_root_loop(long long n)
{
    if (n < 0) n = -n;
    while (n >= 10) {
        long long sum = 0;
        while (n > 0) { sum += n % 10; n /= 10; }
        n = sum;
    }
    return n;
}

long long digital_root_formula(long long n)
{
    if (n < 0) n = -n;
    return n == 0 ? 0 : 1 + (n - 1) % 9;
}


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

    printf("digital root recursive/loop/formula for 98765: %lld / %lld / %lld\\n",\n           digital_root_recursive(98765), digital_root_loop(98765),\n           digital_root_formula(98765));\n\n    puts("Call-count experiment (base 1 avoids arithmetic overflow):");
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
