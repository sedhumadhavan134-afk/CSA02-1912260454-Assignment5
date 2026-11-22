#include <stdio.h>

/* Demonstration of the unsafe pattern from the assignment.
   Do NOT provide an overlong name to this program: %s has no width limit
   and can write beyond the 16-byte array. Prefer fgets as shown in adversarial.c. */
int main(void)
{
    char donor_name[16];
    puts("Enter a short test name only (unsafe scanf demo):");
    if (scanf("%15s", donor_name) != 1) return 1;
    printf("Bounded scanf stored: %s\n", donor_name);
    return 0;
}
