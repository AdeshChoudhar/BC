//
// Created by adeshchoudhar on 16/07/21.
//

#ifndef BC_NUMBER_H
#define BC_NUMBER_H

#include "helpers.h"

#define PLUS 1
#define MINUS -1

#define ORD(x) x - '0'
#define CHR(x) x + '0'

typedef struct Digit {
    int value;
    struct Digit *next;
    struct Digit *prev;
} Digit;

typedef struct Number {
    int sign;
    int length;
    Digit *head;
    Digit *tail;
} Number;

Digit *init_digit(int);
Number *init_number();

void insert_back(Number *, char);
void insert_front(Number *, char);
void remove_back(Number *);
void remove_front(Number *);

bool is_zero(Number *);
int odd_even(Number *);
bool is_binary(Number *);

void clean(Number *);

void show_number(Number *);
void delete_number(Number *);

#endif //BC_NUMBER_H
