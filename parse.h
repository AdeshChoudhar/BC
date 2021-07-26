//
// Created by adeshchoudhar on 23/07/21.
//

#ifndef BC_PARSE_H
#define BC_PARSE_H

#include "function.h"

#define MAX 1024
#define STR 0
#define NUM 1
#define OPR 2
#define STP 3
#define ERR 4
#define IDK 5

typedef struct token {
    int type;
    Number *number;
    char *operator;
} token;

enum state {
    START, NUMBER, OPERATOR, STOP, ERROR
};

char *read();
void menu();
token get_token(const char *expr);
int precedence(const char *operator);
Number *result(char *);

#endif //BC_PARSE_H
