#include <stdio.h>
#include <assert.h>

unsigned long long factorial(unsigned x) {
    unsigned long long result = 1;
    for (int i = 2; i <= x; i++) {
        result *= i;
    }
    assert((result != 0) && "n! is too large");
    return result;
}

void input(unsigned* n, unsigned* m) {
    while(scanf("%u %u", n, m) != 2 || *n == 0 || *m == 0 || *n > *m) {
        puts("Wrong input format. Try again");
    }
}

int main() {
    puts("Task 1");
    puts("Input two positive integers: n m");
        
    unsigned n, m;
    input(&n, &m);

    unsigned long long numerator = 1;
    for (int i = m - n + 1; i <= m; i++) {
        numerator *= i;
    }
    assert((numerator != 0) && "Numerator is too large");

    printf("Result: %llu", numerator / factorial(n));
}
