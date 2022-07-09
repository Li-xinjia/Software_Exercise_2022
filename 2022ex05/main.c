#include <stdio.h>
#include <stdlib.h>

int input(char *file, int **num, int *c) {
    FILE *infp;
    infp = fopen(file, "r");
    if (infp == NULL) {
        printf("Write output file error.\n");
        return 0;
    }
    int count = 0;
    fscanf(infp, "%d", &count);

    fclose(infp);
    *num = malloc(sizeof(int) * count);

    infp = fopen(file, "r");
    if (infp == NULL) {
        printf("Write output file error.\n");
        return 0;
    }
    for (int i = 0; i < count; ++i) {
        fscanf(infp, "%d", *num + i);
    }
    fclose(infp);

    *c = count;
    return 1;
}

int output(char *file, const int *num, int count) {
    FILE *outfp;
    outfp = fopen(file, "w");
    if (outfp == NULL) {
        return 1;
    }
    for (int i = 0; i < count; ++i) {
        fprintf(outfp, "%d ", *(num + i));
    }
    fclose(outfp);
    return 0;
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
    int *num;
    int count = 0;

    if (argc != 3) {
        fprintf(stderr, "Usage: %d infile/outfile\n", argc);
        return 1;
    }

    if (input(argv[1], &num, &count)) {
        printf("size: %d\n", count);
        sort(num, count);
        if (output(argv[2], num, count)) {
            free(num);
            return 1;
        }
    } else {
        free(num);
        return 1;
    }
    free(num);
    return 0;
}