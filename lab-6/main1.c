#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

struct Car {
    char* company;

    struct {
        char* series;
        unsigned number;
    } model;

    unsigned price;

    struct {
        unsigned year, month;
    } releaseDate;

    char* color;
    unsigned engineCapacity;
};

void debug(struct Car* c) {
    printf("Company: %s\n", c->company);
    printf("Model:\n    Series: %s\n    Number: %u\n", c->model.series, c->model.number);
    printf("Price: %u\n", c->price);
    printf("Release Date:\n    Year: %u\n    Month: %u\n", c->releaseDate.year, c->releaseDate.month);
    printf("Color: %s\n", c->color);
    printf("Engine capacity: %u\n", c->engineCapacity);
}

void inputString(char** string, char stopchar) {
    size_t size = 10, index = 0;
    *string = (char*)malloc(sizeof(char) * size);

    char c = EOF;
    while ((c = getc(stdin)) != EOF && c != stopchar) {
        (*string)[index++] = c;
        if (index == size - 1) {
            size *= 2;
            *string = realloc(*string, size);
        }
    }

    (*string)[index] = '\0';
    *string = realloc(*string, index + 1);
}

bool inputUint(unsigned* var) {
    int flag = scanf("%u[^;\n]", var);
    scanf("%*c");
    return flag == 1;
}

bool inputUchar(unsigned char* chr) {
    int flag = scanf("%hhu[^;\n]", chr);
    scanf("%*c");
    return flag == 1;
}

bool readCarInfo(struct Car* c) {
    inputString(&c->company, ';');
    inputString(&c->model.series, ';');

    if (!inputUint(&c->model.number) || !inputUint(&c->price)) {
        return false;
    }
    if (!inputUint(&c->releaseDate.year) || !inputUint(&c->releaseDate.month)) {
        return false;
    }
    inputString(&c->color, ';');
    if (!inputUint(&c->engineCapacity)) {
        return false;
    }
    return c->releaseDate.year <= 2025 && c->releaseDate.month <= 12 && c->releaseDate.month > 0;
}

int main(void) {
    unsigned n;
    if (!inputUint(&n)) {
        puts("Incorrect input");
        return 2;
    }

    struct Car* cars = (struct Car*)malloc(sizeof(struct Car) * n);    
    if (cars == NULL) {
        puts("Could not create array");
        return 3;
    }

    for (unsigned i = 0; i < n; i++) {
        if (!readCarInfo(&cars[i])) {
            puts("Incorrect input");
            return 4;
        }
        debug(&cars[i]);
    }

    unsigned maxPrice = 0;
    for (unsigned i = 0; i < n; i++) {
        maxPrice = (maxPrice >= cars[i].price ? maxPrice : cars[i].price);
    }

    for (unsigned i = 0; i < n; i++) {
        if (cars[i].price == maxPrice) {
            printf("%s\n", cars[i].color);
        }
    }

    return 0;
}
