#include <stdio.h>
#include <limits.h>
#include <stdbool.h>
#include <math.h>
#include <stdlib.h>

const size_t MaxSize = 100;

int max(int a, int b) { return (a > b ? a : b); }
int min(int a, int b) { return (a < b ? a : b); }

bool valid_size(size_t size) {
    return 0 < size && size <= MaxSize;
}

void input_array(size_t size, int* array) {
    bool correct_input;
    do {
        correct_input = true;
        for (size_t i = 0; i < size; i++) {
            if (scanf("%d", &array[i]) != 1) {
                correct_input = false;
            }
        }
        if (!correct_input) {
            ("Wrong input format. Try again.");
        }
    } while (!correct_input);
}

void input_dimensions(size_t *rows, size_t *cols) {
    while (scanf("%zu%zu", rows, cols) != 2 || !valid_size(*rows) || !valid_size(*cols) || *cols < 2) {
        puts("Wrong input format. Try again.");
    }
}

int main() {
    puts("Task 2");
    puts("Input matrix dimensions in the following format:\
 'number of rows' 'number of columns'");
    puts("Number of columns must be greater than 1");

    size_t rows, cols;
    input_dimensions(&rows, &cols);

    puts("Input matrix in the following format:");
    puts("matrix[0][0] matrix[0][1] ... matrix[1][1] ... matrix[rows][cols]");

    int* matrix = (int*)malloc(rows * cols * sizeof(int));
    input_array(rows * cols, matrix);

    int result = INT_MAX;
    for (size_t i = 0; i < rows; i++) {
        int maximum = INT_MIN;
        for (size_t j = 0; j + 1 < cols; j++) {
            maximum = max(maximum, abs(matrix[i * rows + j] - matrix[i * rows + j + 1])); 
        }
        result = min(result, maximum);
    }

    printf("Result: %d\n", result);
    return 0;
}
