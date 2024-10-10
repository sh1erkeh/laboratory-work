#include <stdio.h>
#include <math.h>
#include <stdlib.h>

const int MAX_N = 100;

size_t n;
float x, h, a;

int main() {
    printf("Laboratory work 1\n");
    printf("Task 1\n");
    printf("Input format: 'n x h a'\n");
    printf("Variables must be of the following types:\n");
    printf("n(positive integer), x(float), h(float), a(float)\n");

    while (scanf("%zu%f%f%f", &n, &x, &h, &a) != 4 || n == 0 || n > MAX_N) {
        printf("Input format is incorrect. Try again.\n");
    }

    float r[MAX_N];
    for (int i = 1; i <= n; i++) {
        r[i - 1] = 0.3 * cos(2 * a * x - i * i * h);
    }

    printf("Array elements:\n");
    for (int i = 0; i < n; i++) {
        if (i == n - 1)
            printf("r[%d] = %f\n", i, r[i]);
        else
            printf("r[%d] = %f ", i, r[i]);
    }

    printf("Task 2\n");
    int last_free_pos = 0;
    for (int i = 0; i < n; i++) {
        if (abs(r[i]) > 0.7) {
            r[last_free_pos++] = r[i];
        }
    }

    if (last_free_pos == 0) {
        printf("All elements have been deleted.\n");
        return 1;
    } else if (last_free_pos == n) {
        printf("Not a single element has been deleted.\n");
    }

    printf("New array of length %d:\n", last_free_pos);
    for (int i = 0; i < last_free_pos; i++) {
        if (i == last_free_pos - 1)
            printf("r[%d] = %f\n", i, r[i]);
        else
            printf("r[%d] = %f ", i, r[i]);
    }
    n = last_free_pos;

    printf("Task 3\n");
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

    if (first_maximum_index == n - 1) {
        printf("There are no elements after first maximum.\n");
        return 1;
    }

    printf("Mean value: %f", sum / (n - first_maximum_index - 1));
    return 0;
}
