#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

// Stack implementation
typedef struct Node {
    int value;
    struct Node* next;
} Node;

Node* push(Node* head, int value) {
    Node* temp = (Node*)malloc(sizeof(Node));
    temp->value = value;
    temp->next = head;
    head = temp;
    return head;
}

Node* pop(Node* head) {
    if (head == NULL) {
        return NULL;
    }
    Node* temp = head;
    head = head->next;
    free(temp);
    return head;
}

void printContents(FILE* ostream, Node* head) {
    for (Node* i = head; i != NULL; i = i->next) {
        fprintf(ostream, "%d ", i->value);
    }
    fprintf(ostream, "\n");
}

// Deletes interval [left, right)
void deleteInterval(Node* left, Node* right) {
    for (Node* i = left; i != right;) {
        Node* temp = i;
        i = i->next;
        free(temp);
    }
}

// Utility functions
void inputString(char** string, char stopchar) {
    size_t size = 1, index = 0;
    *string = (char*)malloc(sizeof(char));

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

void inputStack(FILE* istream, Node** stack) {
    int value;
    while (fscanf(istream, "%d[^;\n]", &value) == 1) {
        fscanf(istream, "%*c");
        *stack = push(*stack, value);
    }
}

// Task 2
Node* deleteAllEven(Node* head) {
    Node* cur = head;
    Node* prev = NULL;
    while (cur != NULL) {
        if (cur->value % 2 == 0) {
            Node* temp = cur;
            cur = cur->next;
            free(temp);
        } else {
            if (prev == NULL) {
                head = cur;
            } else {
                prev->next = cur;
            }
            prev = cur;
            cur = cur->next;
        }
    }
    if (prev != NULL) {
        prev->next = NULL;
        return head;
    } else {
        return NULL;
    }
}

// Task 3
Node* deleteAllBetweenFirstMaxAndLastMin(Node* head) {
    Node* max = head;
    Node* min = head;
    bool minIsBigger = true;
    for (Node* i = head; i != NULL; i = i->next) {
        if (i->value > max->value) {
            max = i;
            minIsBigger = false;
        }
        if (i->value <= min->value) {
            min = i;
            minIsBigger = true;
        }
    }
    if (max != min) {
        if (minIsBigger) {
            deleteInterval(max->next, min);
            max->next = min;
        } else {
            deleteInterval(min->next, max);
            min->next = max;
        }
    }
    return head;
}

int main(void) {
    char* inputFileName;
    char outputFileName[] = "output.txt";
    inputString(&inputFileName, '\n');
    
    FILE* istream = fopen(inputFileName, "r");
    FILE* ostream = fopen(outputFileName, "w");

    if (istream == NULL) {
        fprintf(ostream, "No file called '%s'", inputFileName);        
        return 1;
    }

    Node* stack = NULL;
    inputStack(istream, &stack);
    
    fputs("Input:\n", ostream);
    printContents(ostream, stack);
    
    stack = deleteAllEven(stack);
    if (stack == NULL) {
        fputs("Stack became empty after all even elements were deleted\n", ostream);
        return 0;
    }
    
    fputs("Result of task 2:\n", ostream);
    printContents(ostream, stack);
    
    stack = deleteAllBetweenFirstMaxAndLastMin(stack);
    fputs("Result of task 3:\n", ostream);
    printContents(ostream, stack);
    
    deleteInterval(stack, NULL);
    fclose(istream);
    fclose(ostream);

    return 0;    
}
