#include <stdio.h>
#include <stdlib.h>

typedef struct { int id; char group[4]; int last_donation_day; } Donor;
typedef struct { Donor *data; size_t size, capacity; } DonorList;

static int append(DonorList *list, Donor d)
{
    if (list->size == list->capacity) {
        size_t cap = list->capacity ? list->capacity * 2 : 16;
        Donor *tmp = realloc(list->data, cap * sizeof *tmp);
        if (!tmp) return 0;
        list->data = tmp;
        list->capacity = cap;
    }
    list->data[list->size++] = d;
    return 1;
}

int main(int argc, char **argv)
{
    if (argc != 4) {
        fprintf(stderr, "Usage: %s donor-data.txt current-day-ordinal minimum-interval-days\n", argv[0]);
        return 2;
    }
    char *end = NULL;
    long current_day = strtol(argv[2], &end, 10);
    if (!end || *end || current_day < 0) {
        fputs("Invalid current-day value\n", stderr);
        return 2;
    }
    long min_interval = strtol(argv[3], &end, 10);
    if (!end || *end || min_interval < 0) {
        fputs("Invalid minimum-interval value\n", stderr);
        return 2;
    }

    FILE *fp = fopen(argv[1], "r");
    if (!fp) { perror("fopen donor file"); return 1; }
    DonorList list = {NULL, 0, 0};
    Donor d;
    while (fscanf(fp, "%d %3s %d", &d.id, d.group, &d.last_donation_day) == 3) {
        if (!append(&list, d)) {
            fputs("Allocation failed\n", stderr);
            fclose(fp);
            free(list.data);
            return 1;
        }
    }
    if (ferror(fp)) {
        perror("read donor file");
        fclose(fp);
        free(list.data);
        return 1;
    }
    fclose(fp);

    printf("Loaded %zu donor records; allocated capacity %zu records (%zu bytes)\n",
           list.size, list.capacity, list.capacity * sizeof *list.data);
    puts("Eligible donors (ordinal-day interval supplied by operator):");
    for (size_t i = 0; i < list.size; ++i) {
        if (current_day >= list.data[i].last_donation_day &&
            current_day - list.data[i].last_donation_day >= min_interval)
            printf("%d %s\n", list.data[i].id, list.data[i].group);
    }
    free(list.data);
    return 0;
}
