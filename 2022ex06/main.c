#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct school_record {
    float gpa;
    int credit;
    char name[200];
} SRec;

int input(char *file, SRec **sr, int *count) {
    FILE *infp;
    infp = fopen(file, "r");
    if (infp == NULL) {
        printf("Read input file error.\n");
        return 1;
    }
    fscanf(infp, "%d", count);


    *sr = malloc(sizeof(SRec) * *count);
    for (int i = 0; i < *count; ++i) {
        fscanf(infp, "%f", &((*sr + i)->gpa));
        fscanf(infp, "%d", &((*sr + i)->credit));
        fscanf(infp, "%s", &((*sr + i)->name[0]));
    }

    fclose(infp);


    return 0;
}

int cmpgpa(const void *a, const void *b) {
    return ((SRec *) a)->gpa > ((SRec *) b)->gpa ? 1 : -1;
}

int cmpcredit(const void *a, const void *b) {
    return ((SRec *) a)->credit > ((SRec *) b)->credit ? 1 : -1;
}

int cmpname(const void *a, const void *b) {
    return ((SRec *) a)->name[0] > ((SRec *) b)->name[0] ? 1 : -1;
}

int output(char *file, const SRec *sr, int count, char *mode) {
    FILE *outfp;
    outfp = fopen(file, "w");
    if (outfp == NULL) {
        printf("Write output file error.\n");
        return 1;
    }
    fprintf(outfp, "%s\n", mode);
    for (int i = 0; i < count; ++i) {
        fprintf(outfp, "%.1f %d %s\n", sr[i].gpa, sr[i].credit, sr[i].name);
    }
    fclose(outfp);
    return 0;
}

int main(int argc, char *argv[]) {
    SRec *date_p;
    int count;

    if (argc != 4) {
        fprintf(stderr, "Usage: %d infile/outfile\n", argc);
        return 1;
    }
    char *mode = argv[1];
    if (input(argv[2], &date_p, &count)) {
        return 1;
    }

    if (strcmp(mode, "gpa") == 0) {
        qsort(date_p, count, sizeof(SRec), cmpgpa);
    } else if (strcmp(mode, "credit") == 0) {
        qsort(date_p, count, sizeof(SRec), cmpcredit);
    } else if (strcmp(mode, "name") == 0) {
        qsort(date_p, count, sizeof(SRec), cmpname);
    } else {
        printf("Don't know what to sort.\n");
        return 1;
    }

    if (output(argv[3], date_p, count, mode)) {
        return 1;
    }
}
