#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

const size_t MaxSize = 100;

int* count(size_t length, int *array) {
    int* cnt = (int*)malloc(length * sizeof(int));
    for (size_t i = 0; i < length; i++) {
        for (size_t j = 0; j < length; j++) {
            if (array[i] == array[j]) {
                cnt[i]++;
            }
        }
    }
    return cnt;
}

size_t delete_unique(size_t length, int *array) {
    int *cnt = count(length, array);
    size_t lastFreePos = 0;

    for (size_t i = 0; i < length; i++) {
        if (cnt[i] != 1) {
            array[lastFreePos++] = array[i];
        }
    }
    array = realloc(array, lastFreePos * sizeof(int));
    return lastFreePos;
}

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

void output(size_t new_length, int *array) {
    if (new_length != 0) {
        puts("Resulting array:");
        for (size_t i = 0; i < new_length; i++) {
            printf("%d ", array[i]);
        }
    } else {
        puts("Resulting array is empty");
    }
}

int main() {
    puts("Task 3");
    puts("Input array size");

    size_t length;
    while (scanf("%zu", &length) != 1 || !valid_size(length)) {
        puts("Wrong input format. Try again");
    }

    puts("Input array elements (integers) in the following format:");
    puts("array[0] ... array[size_of_array]");

    int* array = (int*)malloc(length * sizeof(int));
    input_array(length, array);

    size_t new_length = delete_unique(length, array);
    output(new_length, array);
    return 0;
}
