#include <iostream>
#include <map>
#include <utility>

std::pair<size_t, int*> task1(size_t lenA, size_t lenB, int* const a, int* const b) {
    size_t lenC = 0;
    int* c = (int*)malloc(sizeof(int) * lenB);

    std::map<int, int> cntB;
    for (int* x = b; x != b + lenB; x++) {
        cntB[*x]++;
    }
    std::map<int, int> cntA;
    for (int* x = a; x != a + lenA; x++) {
        cntA[*x]++;
    }

    for (int* x = b; x != b + lenB; x++) {
        if (cntB[*x] == 1 && *x < 0 && cntA[*x] == 0) {
            c[lenC++] = *x;
        }
    }
    
    c = (int*)realloc(c, lenC);
    return std::make_pair(lenC, c);
}

void printArray(size_t len, int* const array) {
    for (int* x = array; x != array + len; x++) {
        std::cout << *x << ' ';
    }
    std::cout << '\n';
}

int* inputArray(size_t len) {
    int* array = (int*)new int[len];
    for (int* x = array; x != array + len; x++) {
        std::cin >> *x;
    }
    return array;
}

int main() {
    size_t lenA;
    std::cin >> lenA;

    int* a = inputArray(lenA);

    size_t lenB;
    std::cin >> lenB;

    int* b = inputArray(lenB);

    std::pair<size_t, int*> res = task1(lenA, lenB, a, b);
    if (res.second == nullptr) {
        std::cout << "Resulting array is empty\n";
    } else {
        std::cout << "Resulting array:\n";
        printArray(res.first, res.second);
    }
    
    free(res.second);
    delete[] a;
    delete[] b;

    return 0;
}
