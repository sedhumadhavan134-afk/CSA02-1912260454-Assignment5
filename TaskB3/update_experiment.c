#include <stdio.h>
#include <stdlib.h>
#include <time.h>

typedef struct { int group_code; int units; } Stock;

static int update_binary(FILE *fp, long index, int units)
{
    Stock s;
    if (index < 0 || fseek(fp, index * (long)sizeof s, SEEK_SET) != 0) return 0;
    if (fread(&s, sizeof s, 1, fp) != 1) return 0;
    s.units = units;
    if (fseek(fp, -(long)sizeof s, SEEK_CUR) != 0) return 0;
    return fwrite(&s, sizeof s, 1, fp) == 1 && fflush(fp) == 0;
}

int main(void)
{
    const long count = 100000;
    FILE *bin = tmpfile(), *txt = tmpfile(), *rewrite = tmpfile();
    if (!bin || !txt || !rewrite) { perror("tmpfile"); return 1; }

    for (long i = 0; i < count; ++i) {
        Stock s = {(int)(i % 8), (int)(i % 100)};
        if (fwrite(&s, sizeof s, 1, bin) != 1 ||
            fprintf(txt, "%d %d\n", s.group_code, s.units) < 0) {
            fputs("Initial write failed\n", stderr); return 1;
        }
    }

    clock_t start = clock();
    int ok = update_binary(bin, 49999, 777);
    double binary_seconds = (double)(clock() - start) / CLOCKS_PER_SEC;

    rewind(txt);
    start = clock();
    char line[64];
    long index = 0;
    while (fgets(line, sizeof line, txt)) {
        int group, units;
        if (sscanf(line, "%d %d", &group, &units) != 2) return 1;
        if (index == 49999) units = 777;
        if (fprintf(rewrite, "%d %d\n", group, units) < 0) return 1;
        ++index;
    }
    double text_seconds = (double)(clock() - start) / CLOCKS_PER_SEC;
    printf("binary update: %s, %.6f seconds\n", ok ? "done" : "failed", binary_seconds);
    printf("text rewrite: %ld records, %.6f seconds\n", index, text_seconds);
    fclose(bin); fclose(txt); fclose(rewrite);
    return 0;
}
