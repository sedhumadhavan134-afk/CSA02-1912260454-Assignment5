#include <stdio.h>
#include <string.h>

#define NAME_SIZE 16

static int valid_group(const char *g)
{
    const char *groups[] = {"A+", "A-", "B+", "B-", "AB+", "AB-", "O+", "O-"};
    for (size_t i = 0; i < sizeof groups / sizeof groups[0]; ++i)
        if (strcmp(g, groups[i]) == 0) return 1;
    return 0;
}

int main(int argc, char *argv[])
{
    char name[NAME_SIZE];
    puts("Enter donor name (bounded fgets):");
    if (fgets(name, sizeof name, stdin) == NULL) {
        fputs("No name input received.\n", stderr);
        return 1;
    }

    size_t length = strcspn(name, "\n");
    int truncated = (name[length] != '\n' && length == sizeof name - 1);
    name[length] = '\0';
    if (truncated) {
        int ch;
        while ((ch = getchar()) != '\n' && ch != EOF) { }
        puts("Name exceeded the input field; extra characters were discarded.");
    }
    printf("Stored name: %s\n", name);

    FILE *fp = fopen("missing_donor_data.txt", "r");
    if (fp == NULL) perror("fopen missing_donor_data.txt");
    else fclose(fp);

    if (argc != 3 || strcmp(argv[1], "find") != 0 || !valid_group(argv[2])) {
        fprintf(stderr, "Usage: %s find <A+|A-|B+|B-|AB+|AB-|O+|O->\n", argv[0]);
        return 2;
    }
    printf("Validated command: find %s\n", argv[2]);
    return 0;
}
