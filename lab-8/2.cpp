#include <iostream>

void task2(size_t rows, size_t cols, int** const matrix) {
    for (size_t j = 0; j < cols; j += 2) {
        int* first = nullptr;
        int* second = nullptr;

        for (size_t i = 0; i < rows; i++) {
            if (*(*(matrix + i) + j) > 0) {
                first = second;
                second = *(matrix + i) + j;
            }
        }

        if (first != nullptr && second != nullptr) {
            std::swap(*first, *second);
        }
    }
}

void printMatrix(size_t rows, size_t cols, int* const* const matrix) {
    for (int* const* x = matrix; x != matrix + rows; x++) {
        for (int* y = *x; y != *x + cols; y++) {
            std::cout << *y << ' ';
        }
        std::cout << '\n';
    }
}

int** inputMatrix(size_t rows, size_t cols) {
    int** matrix = new int*[rows];
    for (int** x = matrix; x != matrix + rows; x++) {
        *x = new int[cols];
        for (int* y = *x; y != *x + cols; y++) {
            std::cin >> *y;
        }
    }
    return matrix;
}

int main() {
    size_t rows, cols;
    std::cin >> rows >> cols;
    
    int** matrix = inputMatrix(rows, cols);
    task2(rows, cols, matrix);

    std::cout << "Resulting matrix:\n";
    printMatrix(rows, cols, matrix);

    for (int** x = matrix; x != matrix + rows; x++) {
        delete[] *x;
    }
    delete[] matrix;

    return 0;
}
