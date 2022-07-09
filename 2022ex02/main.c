#include <stdio.h>

#define MAX_DATA 10

int input(FILE *infp, int *num, int *c) {
    int temp;
    int count = 0;
    while (fscanf(infp, "%d", &temp) == 1) {
        if (count >= MAX_DATA) {
            printf("Too much numbers.\n");
            return 0;
        }
        *(num + count) = temp;
        count++;
    }
    *c = count;
    return 1;
}

void output(FILE *outfp, const int *num, int count) {
    for (int i = 0; i < count; ++i) {
        fprintf(outfp, "%d ", *(num + i));
    }
}

void sort(int *num, int size) {
    if (size == 0) return;
    int max = 0, max_position = 0, temp;
    for (int i = 0; i < size; ++i) {
        if (*(num + i) > max) {
            max = *(num + i);
            max_position = i;
        }
    }
    temp = *(num + size - 1);
    *(num + size - 1) = max;
    *(num + max_position) = temp;
    sort(num, size - 1);
}

int main(int argc, char *argv[]) {
    FILE *infp, *outfp;
    int num[10];
    int count = 0;

    if (argc != 3) {
        fprintf(stderr, "Usage: %d infile outfile\n", argc);
        return 1;
    }
    infp = fopen(argv[1], "r");
    if (infp == NULL) {
        printf("Read input file error.\n");
        return 1;
    }

    outfp = fopen(argv[2], "w");
    if (outfp == NULL) {
        printf("Write output file error.\n");
        return 1;
    }

    if (input(infp, &num[0], &count)) {
        printf("size: %d\n", count);
        for (int i = 0; i < count; ++i) {
            printf("num: %d\n", num[i]);
        }
        sort(&num[0], count);
        output(outfp, &num[0], count);
    } else {
        return 1;
    }

    fclose(infp);
    fclose(outfp);
    return 0;
}