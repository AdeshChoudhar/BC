//
// Created by adeshchoudhar on 16/07/21.
//

#include "helpers.h"

void throw_error(int error_number) {
    switch (error_number) {
        case 1: {
            fprintf(stderr, "Value Error: Digit value was not between 0 to 9.\n");
            break;
        }
        case 2: {
            fprintf(stderr, "Memory Error: Digit memory allocation failed.\n");
            break;
        }
        case 3: {
            fprintf(stderr, "Memory Error: Number memory allocation failed.\n");
            break;
        }
        case 4: {
            fprintf(stderr, "Memory Error: node_N memory allocation failed.\n");
            break;
        }
        case 5: {
            fprintf(stderr, "Memory Error: node_C memory allocation failed.\n");
            break;
        }
        case 6: {
            fprintf(stderr, "Division Error: Divisor cannot be 0.\n");
            break;
        }
        case 7: {
            fprintf(stderr, "Value Error: Negative shift count.\n");
            break;
        }
        case 8: {
            fprintf(stderr, "Memory Error: Expression memory allocation failed.\n");
            break;
        }
        case 9: {
            fprintf(stderr, "Operation Error: Invalid operator.\n");
            break;
        }
        case 10: {
            fprintf(stderr, "Parse Error: Invalid expression.\n");
            break;
        }
        default: {
            fprintf(stderr, "Unknown Error: IDK!\n");
            break;
        }
    }
}

bool is_valid_value(int value) {
    return (0 <= value && value <= 9);
}

bool is_valid_character(char c) {
    char valid_characters[] = {'+', '-', '*', '/', '%', '<', '>'};
    int n = sizeof(valid_characters) / sizeof(valid_characters[0]);
    for (int i = 0; i < n; i++) {
        if (c == valid_characters[i]) {
            return true;
        }
    }
    return false;
}

bool is_valid_operator(const char *operator) {
    char *valid_operators[] = {/*"++", "--",*/ "+", "-", "*", "/", "%", "**", "<<", ">>"};
    int n = sizeof(valid_operators) / sizeof(valid_operators[0]);
    for (int i = 0; i < n; i++) {
        if (strcmp(operator, valid_operators[i]) == 0) {
            return true;
        }
    }
    return false;
}

int max(int m, int n) {
    return (m > n ? m : n);
}
