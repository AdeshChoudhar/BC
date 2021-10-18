//
// Created by adeshchoudhar on 23/07/21.
//

#include "parse.h"

char *read() {
    char *expr = (char *) malloc(sizeof(char) * MAX);
    if (!expr) {
        throw_error(8);
        return NULL;
    }

    int i = 0;
    while (i < MAX - 1) {
        char c = (char) getchar();
        if (c != ' ') {
            if (c == '\n') {
                expr[i++] = '\0';
                break;
            } else {
                expr[i++] = c;
            }
        }
    }
    expr[i] = '\0';

    return expr;
}

void menu() {
    system("figlet BC\n");
    printf("An arbitrary precision calculator.\n");
    printf("Author: Adesh Choudhar.\n\n");

    printf("Inspired by GNU's bc which is an arbitrary precision numeric processing language.\n\n");

    printf("\u2022 VALID OPERATIONS:\n");
//    printf("\t1. '++': increment\n");
//    printf("\t2. '--': decrement\n");
    printf("\t1. '+': add\n");
    printf("\t2. '-': subtract\n");
    printf("\t3. '*': multiply\n");
    printf("\t4. '/': divide\n");
    printf("\t5. '%%': modulo\n");
    printf("\t6. '**': power\n");
    printf("\t7. '<<': shift_left\n");
    printf("\t8. '>>': shift_right\n");
}

int ind = 0;
enum state current_state = START;

token get_token(const char *expr) {
    token t;
    int type = STR;
    Number *number = init_number();
    char *operator = "";

    char current_char;
    while (true) {
        current_char = expr[ind];
        switch (current_state) {
            case START: {
                if (is_valid_value(ORD(current_char))) {
                    insert_front(number, current_char);
                    current_state = NUMBER;
                    ind += 1;
                } else if (is_valid_character(current_char)) {
                    operator = "";
                    operator += current_char;
                    current_state = OPERATOR;
                    ind += 1;
                } else if (current_char == '\0') {
                    t.type = STR;
                    current_state = STOP;
                    return t;
                } else {
                    t.type = ERR;
                    current_state = ERROR;
                    return t;
                }
                break;
            }
            case NUMBER: {
                if (is_valid_value(ORD(current_char))) {
                    insert_front(number, current_char);
                    current_state = NUMBER;
                    ind += 1;
                } else if (is_valid_character(current_char)) {
                    t.type = NUM;
                    t.number = number;
                    operator = "";
                    operator += current_char;
                    current_state = OPERATOR;
                    ind += 1;
                    return t;
                } else if (current_char == '\0') {
                    t.type = NUM;
                    t.number = number;
                    current_state = STP;
                    return t;
                } else {
                    t.type = ERR;
                    current_state = ERROR;
                    return t;
                }
                break;
            }
            case OPERATOR: {
                if (is_valid_value(ORD(current_char))) {
                    if (is_valid_operator(operator)) {
                        t.type = OPR;
                        t.operator = operator;
                        current_state = NUMBER;
                        ind += 1;
                        return t;
                    } else {
                        t.type = ERR;
                        current_state = ERROR;
                        return t;
                    }
                } else if (is_valid_character(current_char)) {
                    operator += current_char;
                    if (is_valid_operator(operator)) {
                        current_state = OPERATOR;
                        ind += 1;
                    } else {
                        t.type = ERR;
                        current_state = ERROR;
                        return t;
                    }
                } else if (current_char == '\0') {
                    if (is_valid_operator(operator)) {
                        t.type = OPR;
                        t.operator = operator;
                        current_state = STP;
                        return t;
                    } else {
                        t.type = ERR;
                        current_state = ERROR;
                        return t;
                    }
                } else {
                    t.type = ERR;
                    current_state = ERROR;
                    return t;
                }
                break;
            }
            case STOP: {
                t.type = STP;
                return t;
            }
            case ERROR: {
                t.type = ERR;
                return t;
            }
            default: {
                t.type = IDK;
                return t;
            }
        }
    }
}

//L-R: (), ++(postfix), --(postfix)
//R-L: ++(prefix), --(prefix), +(unary), -(unary), ~
//R-L: **
//L-R: *, /, %
//L-R: +, -
//L-R: <<, >>
//L-R: <, <=, >, >=
//L-R: &
//L-R: ^
//L-R: |

Number *result(char *expr) {
    Number *number1 = init_number();
    char operator[3] = {'\0', '\0', '\0'};
    Number *number2 = init_number();

    Number *res = NULL;

    int i = 0;
    if (expr[i] == '-') {
        number1->sign = MINUS;
        i += 1;
    }
    while (i < MAX && expr[i] != '\0' && is_valid_value(ORD(expr[i]))) {
        insert_back(number1, expr[i]);
        i += 1;
    }
    if (expr[i] == '\0') {
        res = init_number();
        copy_number(res, number1);
        delete_numbers(2, number1, number2);
        return res;
    }

    int tmp = 0;
    while (i < MAX && expr[i] != '\0' && is_valid_character(expr[i]) && tmp < 2) {
        operator[tmp] = expr[i];
        tmp += 1;
        i += 1;
    }
    if (!is_valid_operator(operator)) {
        throw_error(9);
        return res;
    }

    if (expr[i] == '-') {
        number2->sign = MINUS;
        i += 1;
    }
    while (i < MAX && expr[i] != '\0' && is_valid_value(ORD(expr[i]))) {
        insert_back(number2, expr[i]);
        i += 1;
    }

    if (is_zero(number1)) {
        number1->sign = PLUS;
    }
    if (is_zero(number2)) {
        number2->sign = PLUS;
    }

    if (strcmp(operator, "+") == 0) {
        res = add(number1, number2);
    } else if (strcmp(operator, "-") == 0) {
        res = subtract(number1, number2);
    } else if (strcmp(operator, "*") == 0) {
        res = multiply(number1, number2);
    } else if (strcmp(operator, "/") == 0) {
        res = divide(number1, number2);
    } else if (strcmp(operator, "%") == 0) {
        res = modulo(number1, number2);
    } else if (strcmp(operator, "**") == 0) {
        res = power(number1, number2);
    } else if (strcmp(operator, "<<") == 0) {
        res = shift_left(number1, number2);
    } else if (strcmp(operator, ">>") == 0) {
        res = shift_right(number1, number2);
    } else {
        res = NULL;
    }

    delete_numbers(2, number1, number2);

    return res;
}
