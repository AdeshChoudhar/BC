//
// Created by adeshchoudhar on 16/07/21.
//

#include "error.h"

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
        default: {
            fprintf(stderr, "Unknown Error: IDK.\n");
        }
    }
}