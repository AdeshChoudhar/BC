//
// Created by adeshchoudhar on 16/07/21.
//

#ifndef BC_FUNCTION_H
#define BC_FUNCTION_H

#include "stack.h"

typedef struct Pair {
    Number *first;
    Number *second;
} Pair;

void copy_number(Number *, Number *);
void make_length_equal(Number *, Number *);
int compare_numbers(Number *, Number *);

void increment(Number *);
void decrement(Number *);

Number *add(Number *, Number *);
Number *subtract(Number *, Number *);
Number *multiply(Number *, Number *);
Pair div_mod(Number *, Number *);
Number *divide(Number *, Number *);
Number *modulo(Number *, Number *);

#endif //BC_FUNCTION_H
