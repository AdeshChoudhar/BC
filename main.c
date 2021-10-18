#include <stdio.h>

#include "parse.h"

int main() {
    printf("BC\n");
    printf("Author: Adesh Choudhar\n");

    while (true) {
        printf("> ");
        char *expr = read();

        if (strcmp(expr, "help") == 0) {
            menu();
        } else if (strcmp(expr, "exit") == 0) {
            printf("Bye!\n");
            break;
        } else if (expr[0] == '\0') {
            continue;
        } else if (is_valid_character(expr[0]) || is_valid_value(ORD(expr[0]))) {
            Number *res = result(expr);
            if (!res) {
                throw_error(10);
                continue;
            }
            printf("= ");
            show_number(res);
            delete_number(res);
        } else {
            throw_error(10);
        }
        free(expr);
    }

    return 0;
}
