//
// Created by adeshchoudhar on 16/07/21.
//

#include "error.h"

void throw_error(int error_number) {
    switch (error_number) {
        case 1: {
            fprintf(stderr, "Value Error: Digit value was not between 0 to 9.");
            break;
        }
        case 2: {
            fprintf(stderr, "Memory Error: Digit memory allocation failed.");
            break;
        }
        case 3: {
            fprintf(stderr, "Memory Error: Number memory allocation failed.");
            break;
        }
        case 4: {
            fprintf(stderr, "Memory Error: node_N memory allocation failed.");
            break;
        }
        case 5: {
            fprintf(stderr, "Memory Error: node_C memory allocation failed.");
            break;
        }
        case 6: {
            fprintf(stderr, "Division Error: Divisor cannot be 0.");
            break;
        }
        default: {
            fprintf(stderr, "Unknown Error: IDK.");
        }
    }

    printf("\nBye!\n");
    exit(EXIT_FAILURE);
}