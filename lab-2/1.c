#include <stdio.h>
#include <stdbool.h>
#include <math.h>

const int MaxSize = 100;

size_t rows = 0, cols = 0, size_of_array = 0;
int matrix[100 * 100], array[100];

bool find(int element, int size_of_array, int *array) {
    for (size_t i = 0; i < size_of_array; i++) {
        if (array[i] == element) {
            return true;
        }
    }
    return false;
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

bool valid_size(size_t size) {
    return 0 < size && size <= MaxSize;
}

int main() {
    // Input section
    puts("Input matrix dimensions in the following format:");
    puts("'number of rows' 'number of columns'");
    puts("Both numbers must be positive integers.");

    while (scanf("%zu%zu", &rows, &cols) != 2 || !valid_size(rows) || !valid_size(cols)) {
        puts("Wrong input format. Try again.");
    }

    puts("Input matrix in the following format:");
    puts("matrix[0][0] matrix[0][1] ... matrix[1][1] ... matrix[rows][cols]");
    input_array(rows * cols, matrix);

    puts("Input array size (positive integer).");
    while (scanf("%d", &size_of_array) != 1 || !valid_size(size_of_array)) {
        puts("Wrong input format. Try again.");
    }

    puts("Input array in the following format:");
    puts("array[0] array[1] ... array[size_of_array]");
    input_array(size_of_array, array);

    // Main section
    for (size_t i = 0; i < rows; i++) {
        size_t maximum_index = 0;
        for (size_t j = 0; j < cols; j++) {
            if (abs(matrix[i * cols + j]) > abs(matrix[i * cols + maximum_index])) {
                maximum_index = j;
            }
        }
        for (size_t j = 0; j < cols; j++) {
            if (abs(matrix[i * cols + j]) == abs(matrix[i * cols + maximum_index])) {
                matrix[i * cols + j] = 0;
            }
        }
    }

    // Output section
    puts("Result:");
    for (size_t i = 0; i < rows; i++) {
        for (size_t j = 0; j < cols; j++) {
            printf("%d ", matrix[i * cols + j]);
        }
        printf("\n");
    }

    return 0;
}