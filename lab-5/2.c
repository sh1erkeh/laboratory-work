#include <stdio.h>
#include <assert.h>
#include <stdlib.h>
#include <stdbool.h>

bool is_digit(char c) {
    return '0' <= c && c <= '9';
}

char replacement_char(char c) {
    return 'A' + c - '0';
}

int main() {
    FILE *istream = fopen("input.txt", "r+");
    assert((istream != NULL) && "input.txt not found");

    int character;
    while ((character = fgetc(istream)) != EOF) {
        if (is_digit(character)) {
            fseek(istream, -1, SEEK_CUR);
            fputc(replacement_char(character), istream);
            fseek(istream, 0, SEEK_CUR);
        }
    } 

    return 0;
}
