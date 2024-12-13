#include <stdio.h>
#include <assert.h>

int main() {
    FILE *istream = fopen("numbers.csv", "r");
    assert((istream != NULL) && "numbers.csv not found");

    int cnt = 0, flag = 0;
    float sum = 0, number = 0;

    do {
        flag = fscanf(istream, "%f[^;\n]", &number);
        flag = fscanf(istream, "%*c");

        if (number > 0) {
            sum += number;
            cnt++;
        }
    } while (flag != EOF);

    if (cnt == 0) {
        puts("No positive integers found.");
    } else {
        printf("Mean value: %f\n", sum / cnt);
    }

    return 0;
}
