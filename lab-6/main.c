#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

FILE* istream;

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

    struct {
        unsigned char r, g, b;
    } color;

    unsigned engineCapacity;
};

void debug(struct Car* c) {
    printf("Company: %s\n", c->company);
    printf("Model:\n    Series: %s\n    Number: %d\n", c->model.series, c->model.number);
    printf("Price: %d\n", c->price);
    printf("Release Date:\n    Year: %d\n    Month: %d\n", c->releaseDate.year, c->releaseDate.month);
    printf("Color: (%hhu, %hhu, %hhu)\n", c->color.r, c->color.g, c->color.b);
    printf("Engine capacity: %d\n", c->engineCapacity);
}

void inputString(char** string, char stopchar) {
    size_t size = 10, index = 0;
    *string = (char*)malloc(sizeof(char) * size);

    char c = EOF;
    while ((c = fgetc(istream)) != EOF && c != stopchar) {
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
    int flag = fscanf(istream, "%u[^;\n]", var);
    fscanf(istream, "%*c");
    return flag == 1;
}

bool inputUchar(unsigned char* chr) {
    int flag = fscanf(istream, "%hhu[^;\n]", chr);
    fscanf(istream, "%*c");
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
    if (!inputUchar(&c->color.r) || !inputUchar(&c->color.g) || !inputUchar(&c->color.b)) {
        return false;
    }
    if (!inputUint(&c->engineCapacity)) {
        return false;
    }
    return c->releaseDate.year <= 2025 && c->releaseDate.month <= 12;
}

int main(void) {
    char inputFileName[101] = "input.csv";
    // scanf("%s", inputFileName);

    if ((istream = fopen(inputFileName, "r")) == NULL) {
        puts("No such file");
        return 1;
    }
    
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

    for (int i = 0; i < n; i++) {
        if (!readCarInfo(&cars[i])) {
            puts("Incorrect input");
            return 4;
        }
    }

    unsigned maxPrice = 0;
    for (int i = 0; i < n; i++) {
        maxPrice = (maxPrice >= cars[i].price ? maxPrice : cars[i].price);
    }

    for (int i = 0; i < n; i++) {
        if (cars[i].price == maxPrice) {
            printf("(%hhu, %hhu, %hhu)\n", cars[i].color.r, cars[i].color.g, cars[i].color.b);
        }
    }

    return 0;
}

