//
// Created by adeshchoudhar on 16/07/21.
//

#ifndef BC_STACK_H
#define BC_STACK_H

#include "number.h"

// Numbers
typedef struct node_N {
    Number *number;
    struct node_N *next;
} node_N;

typedef node_N *stack_N;

node_N *init_node_N(Number *);
bool is_empty_N(stack_N *);
void push_N(stack_N *, Number *);
void pop_N(stack_N *);

// Operators
typedef struct node_C {
    char *operator;
    struct node_C *next;
} node_C;

typedef node_C *stack_C;

bool is_valid_operator(const char *);

node_C *init_node_C(char *);
bool is_empty_C(stack_C *);
void push_C(stack_C *, char *);
void pop_C(stack_C *);

#endif //BC_STACK_H
