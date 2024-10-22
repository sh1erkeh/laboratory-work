#include <stdio.h>
#include <stdbool.h>
#include <math.h>

const int MaxSize = 100;

size_t size_of_array = 0;
int array[100];

int sum_of_digits(int number) {
    int sum = 0;
    while (number > 0) {
        sum += number % 10;
        number /= 10;
    }
    return sum;
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
    puts("Input array size (positive integer).");

    while (scanf("%zu", &size_of_array) != 1 || !valid_size(size_of_array)) {
        puts("Wrong input format. Try again");
    }

    puts("Input array elements (integers) in the following format:");
    puts("array[0] ... array[size_of_array]");
    input_array(size_of_array, array);

    // Main section
    for (size_t i = 0; i < size_of_array; i++) {
        array[i] = sum_of_digits(abs(array[i]));
    }
    
    // Output section
    puts("Result:");
    for (size_t i = 0; i < size_of_array; i++) {
        printf("%d ", array[i]);
    }
    return 0;
}
