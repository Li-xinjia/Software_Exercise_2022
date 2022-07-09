#include <stdio.h>

#define MAX_N 5

int input_matrix(float (*a)[MAX_N], int *n) {
    printf("Please input n:");
    scanf("%d", n);
    if (*n > 5) {
        printf("Error: n is too big.\n");
        return 1;
    }
    printf("Please input your matrix:\n");

    for (int i = 0; i < *n; ++i) {
        for (int j = 0; j < *n; ++j) {
            scanf("%f", &a[i][j]);
        }
    }
    return 0;
}

void multiply_matrix(float (*ak)[MAX_N], float (*a)[MAX_N], int n) {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            ak[i][j] = 0;
            for (int k = 0; k < n; k++)
                ak[i][j] += a[i][k] * a[k][j];
        }
    }
}

void output_matrix(float (*ak)[MAX_N], int *n) {
    printf("The square of the matrix.\n");
    for (int i = 0; i < *n; i++) {
        for (int j = 0; j < *n; j++) {
            printf("%f\t", ak[i][j]);
        }
        printf("\n");
    }
}

int main() {
    int n;
    float a[MAX_N][MAX_N];
    float ak[MAX_N][MAX_N];

    //input matrix
    if (input_matrix(a, &n)) {
        return 1;
    }

    //multiply matrix
    multiply_matrix(ak, a, n);

    //output matrix
    output_matrix(ak, &n);

    float (*b)[8];
    return 0;
}
