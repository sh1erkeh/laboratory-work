#include <stdio.h>
#include <math.h>
#include <stdlib.h>

size_t n;
float x, h, a, *r = NULL;

int task1() {
    printf("Input format: 'n x h a'.\n");
    printf("Variables must be of the following types: n(positive integer), x(float), h(float), a(float).\n");

    int counter = 0;
    while (scanf("%zu%f%f%f", &n, &x, &h, &a) != 4 || n == 0) {
        if (++counter > 5) {
            printf("Too many attempts.\n");
            return 1;
        }
        printf("Input format is incorrect. Try again.\n");
    }

    r = (float*)calloc(n, sizeof(float));
    if (r == NULL) {
        printf("Memory allocation error.\n");
        return 1;
    }

    for (int i = 1; i <= n; i++) {
        r[i - 1] = 0.3 * cos(2 * a * x - i * i * h);;
    }
    return 0;
}

int task2() {
    if (r == NULL) {
        printf("Array is empty or not initialized.\n");
        return 1;
    }

    int last_free_pos = 0;
    for (int i = 0; i < n; i++) {
        if (abs(r[i]) >= 0.7) {
            r[last_free_pos++] = r[i];
        }
    }

    n = last_free_pos;
    r = realloc(r, n * sizeof(float));
    return 0;
}

int task3() {
    if (r == NULL) {
        printf("Array is empty or not initialized.\n");
        return 1;
    }
    if (n == 1) {
        printf("There are no elements after first maximum.\n");
        return 1;
    }

    int first_maximum_index = 0;
    float sum = 0;

    for (int i = 0; i < n; i++) {
        if (r[i] > r[first_maximum_index]) {
            first_maximum_index = i;
            sum = 0;
        } else {
            sum += r[i];
        }
    }
    printf("%f", sum / n);
    return 0;
}

int main() {
    if (task1()) {
        printf("Task 1 failed.\n");
        return 1;
    }
    if (task2()) {
        printf("Task 2 failed.\n");
        return 1;
    }
    if (task3()) {
        printf("Task 3 failed.\n");
        return 1;
    }
    free(r);
    return 0;
}
