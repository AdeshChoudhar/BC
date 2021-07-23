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
        default: {
            fprintf(stderr, "Unknown Error: IDK!\n");
            break;
        }
    }
}

bool is_valid_operator(const char *operator) {
    char *valid_characters[] = {"++", "--", "+", "-", "*", "/", "%", "**", "<<", ">>"};
    int n = sizeof(valid_characters) / sizeof(valid_characters[0]);
    for (int i = 0; i < n; i++) {
        if (strcmp(operator, valid_characters[i]) == 0) {
            return true;
        }
    }

    return false;
}

int max(int m, int n) {
    return (m > n ? m : n);
}
