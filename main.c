#include <stdio.h>

#include "function.h"

#define MAX 1024

int main() {
    printf("BC\n");
    printf("Author: Adesh Choudhar\n\n");

    Number *number1 = init_number();
    Number *number2 = init_number();

    char expr[MAX + 1];
    printf("Enter Number1: ");
    scanf("%s", expr);

    for (int i = 0; expr[i] != '\0'; i++) {
        insert_back(number1, expr[i]);
    }

//    printf("Enter Number2: ");
//    scanf("%s", expr);
//
//    for (int i = 0; expr[i] != '\0'; i++) {
//        insert_back(number2, expr[i]);
//    }

    number1->sign = MINUS;
//    number2->sign = PLUS;

//    Number *tmp = power(number1, number2);

    Number *tmp = decimal(number1);
    printf("\nResult: ");
    show_number(tmp);
    if (tmp) {
        printf("Sign: %s\n", tmp->sign == 1 ? "PLUS" : "MINUS");
    }

    delete_number(number1);
    delete_number(number2);
    delete_number(tmp);

    return 0;
}
