#include <stdio.h>
#include <stdlib.h>
#include <time.h>

typedef struct { int group_code; int units; } Stock;

/* Overwrites the units of zero-based record index directly in the binary file. */
int update_units(FILE *fp, int index, int units)
{
    Stock s;
    if (fp == NULL || index < 0) return 0;
    if (fseek(fp, (long)index * (long)sizeof s, SEEK_SET) != 0) return 0;
    if (fread(&s, sizeof s, 1, fp) != 1) return 0;
    s.units = units;
    if (fseek(fp, -(long)sizeof s, SEEK_CUR) != 0) return 0;
    if (fwrite(&s, sizeof s, 1, fp) != 1) return 0;
    return fflush(fp) == 0;
}

int main(void)
{
    FILE *fp = tmpfile();
    if (fp == NULL) { perror("tmpfile"); return 1; }
    Stock initial[5] = {{1, 40}, {2, 25}, {3, 12}, {4, 8}, {5, 30}};
    if (fwrite(initial, sizeof(Stock), 5, fp) != 5) {
        perror("fwrite"); fclose(fp); return 1;
    }
    printf("update record 3: %s\n", update_units(fp, 3, 20) ? "done" : "failed");
    printf("update record 9: %s\n", update_units(fp, 9, 20) ? "done" : "failed");
    rewind(fp);
    Stock s;
    while (fread(&s, sizeof s, 1, fp) == 1)
        printf("%d:%d ", s.group_code, s.units);
    putchar('\n');
    fclose(fp);
    return 0;
}
