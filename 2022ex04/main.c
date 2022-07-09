#include <stdio.h>

#define MAX_N 5
#define MAX_POWER 5

int input_matrix(float (*a)[MAX_N], int *n, int *power) {
    printf("Please input n:");
    scanf("%d", n);
    if (*n > MAX_N || *n <= 0) {
        printf("Error: n is too big.\n");
        return 1;
    }

    printf("Please input your matrix:\n");
    for (int i = 0; i < *n; ++i) {
        for (int j = 0; j < *n; ++j) {
            scanf("%f", &a[i][j]);
        }
    }

    printf("Please input power:");
    scanf("%d", power);
    if (*power > MAX_POWER || *power <= 0) {
        printf("Error: power is too big.\n");
        return 1;
    }
    return 0;
}

void multiply_matrix(float (*out)[MAX_N], float (*a)[MAX_N], float (*b)[MAX_N], int n) {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            out[i][j] = 0;
            for (int k = 0; k < n; k++)
                out[i][j] += a[i][k] * b[k][j];
        }
    }
}

void output_matrix(float (*ak)[MAX_N], int n) {
    printf("The square of the matrix.\n");
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            printf("%f\t", ak[i][j]);
        }
        printf("\n");
    }
}

void power_matrix(float (**ak)[MAX_N], float (*x)[MAX_N], float (*y)[MAX_N], int n, int power) {
    float (*temp)[MAX_N];
    if (power == 1) {
        return;
    } else {
        multiply_matrix(x, *ak, *ak, n);
        for (int i = 0; i < power - 2; ++i) {
            multiply_matrix(y, *ak, x, n);
            temp = x;
            x = y;
            y = temp;
        }
        *ak = x;

        return;
    }
}

int main() {
    int n, power;
    float A[MAX_N][MAX_N];
    float X[MAX_N][MAX_N];
    float Y[MAX_N][MAX_N];
    float (*a)[MAX_N] = A;
    float (*x)[MAX_N] = X;
    float (*y)[MAX_N] = Y;

    //input matrix
    if (input_matrix(a, &n, &power)) {
        return 1;
    }

    //multiply matrix
    power_matrix(&a, x, y, n, power);

    //output matrix

    output_matrix(a, n);


    return 0;
}
