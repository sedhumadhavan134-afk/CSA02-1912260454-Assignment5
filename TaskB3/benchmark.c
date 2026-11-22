#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

typedef struct {
    int id;
    char name[32];
    char group[4];
    int age;
    char phone[16];
} Donor;

static void fill_donor(Donor *d, int id)
{
    d->id = id;
    snprintf(d->name, sizeof d->name, "Donor%07d", id);
    strcpy(d->group, (id % 2) ? "O+" : "A-");
    d->age = 18 + id % 55;
    snprintf(d->phone, sizeof d->phone, "%010d", id);
}

static int text_roundtrip(size_t n, long *bytes, double *write_s, double *read_s)
{
    FILE *fp = tmpfile();
    if (!fp) return 0;
    clock_t start = clock();
    for (size_t i = 0; i < n; ++i) {
        Donor d; fill_donor(&d, (int)i + 1);
        if (fprintf(fp, "%d|%s|%s|%d|%s\n", d.id, d.name, d.group, d.age, d.phone) < 0) {
            fclose(fp); return 0;
        }
    }
    *write_s = (double)(clock() - start) / CLOCKS_PER_SEC;
    fflush(fp);
    *bytes = ftell(fp);
    rewind(fp);
    start = clock();
    char line[160];
    size_t read_count = 0;
    while (fgets(line, sizeof line, fp)) ++read_count;
    *read_s = (double)(clock() - start) / CLOCKS_PER_SEC;
    fclose(fp);
    return read_count == n;
}

static int binary_roundtrip(size_t n, long *bytes, double *write_s, double *read_s)
{
    FILE *fp = tmpfile();
    if (!fp) return 0;
    clock_t start = clock();
    for (size_t i = 0; i < n; ++i) {
        Donor d; fill_donor(&d, (int)i + 1);
        if (fwrite(&d, sizeof d, 1, fp) != 1) { fclose(fp); return 0; }
    }
    *write_s = (double)(clock() - start) / CLOCKS_PER_SEC;
    fflush(fp);
    *bytes = ftell(fp);
    rewind(fp);
    start = clock();
    Donor d; size_t read_count = 0;
    while (fread(&d, sizeof d, 1, fp) == 1) ++read_count;
    *read_s = (double)(clock() - start) / CLOCKS_PER_SEC;
    fclose(fp);
    return read_count == n;
}

int main(void)
{
    const size_t sizes[] = {1000, 10000, 100000};
    puts("records,format,bytes,write_seconds,read_seconds");
    for (size_t i = 0; i < sizeof sizes / sizeof sizes[0]; ++i) {
        long bytes; double wt, rt;
        if (!text_roundtrip(sizes[i], &bytes, &wt, &rt)) {
            fputs("Text file experiment failed\n", stderr); return 1;
        }
        printf("%zu,text,%ld,%.6f,%.6f\n", sizes[i], bytes, wt, rt);
        if (!binary_roundtrip(sizes[i], &bytes, &wt, &rt)) {
            fputs("Binary file experiment failed\n", stderr); return 1;
        }
        printf("%zu,binary,%ld,%.6f,%.6f\n", sizes[i], bytes, wt, rt);
    }
    puts("Times above are measured by this run on this machine; repeat for stable comparison.");
    return 0;
}
