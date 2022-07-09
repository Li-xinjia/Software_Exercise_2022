#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

typedef struct school_record {
    float gpa;
    int credit;
    char name[200];
} SRec;

typedef int compare_func(const void *, const void *);

clock_t start;
clock_t end;

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
    return strcmp(((SRec *) a)->name, ((SRec *) b)->name);
}

void swap(char *a, char *b, int width) {
    char tmp;
    for (int i = 0; i < width; ++i) {
        tmp = *a;
        *a++ = *b;
        *b++ = tmp;
    }
}


void sort_simple(void *base, int count, int size, compare_func *compare) {
    int now = 0;
    for (int i = 0; i < count; ++i) {
        if (compare((base + i * size), (base + now * size)) > 0) {
            now = i;
        }
    }
    swap((base + now * size), (base + (count - 1) * size), size);
    if (count != 1) {
        sort_simple(base, count - 1, size, compare);
    }
}

int output(char *file, const SRec *sr, int count, char *mode) {
    FILE *outfp;
    outfp = fopen(file, "w");
    if (outfp == NULL) {
        printf("Write output file error.\n");
        return 1;
    }
    fprintf(outfp, "%d\n", count);
    for (int i = 0; i < count; ++i) {
        fprintf(outfp, "%.1f %d %s\n", sr[i].gpa, sr[i].credit, sr[i].name);
    }
    fclose(outfp);
    return 0;
}

int main(int argc, char *argv[]) {
    SRec *date_p;
    int count;
    double run_time;

    if (argc != 4) {
        fprintf(stderr, "Error: wrong number of parameter. Need 4. Now is %d.\n", argc);
        return 1;
    }
    char *mode = argv[1];
    if (input(argv[2], &date_p, &count)) {
        return 1;
    }


    if (strcmp(mode, "gpa") == 0) {
        start = clock();
        sort_simple(date_p, count, sizeof(SRec), cmpgpa);
        end = clock();
    } else if (strcmp(mode, "credit") == 0) {
        start = clock();
        sort_simple(date_p, count, sizeof(SRec), cmpcredit);
        end = clock();
    } else if (strcmp(mode, "name") == 0) {
        start = clock();
        sort_simple(date_p, count, sizeof(SRec), cmpname);
        end = clock();
    } else {
        printf("Don't know what to sort.\n");
        return 1;
    }
    run_time = (double) (end - start) / CLOCKS_PER_SEC;
    printf("%lf",run_time);
    if (output(argv[3], date_p, count, mode)) {
        return 1;
    }
}