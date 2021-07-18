//
// Created by adeshchoudhar on 16/07/21.
//

#ifndef BC_STACK_H
#define BC_STACK_H

#include "number.h"

// Stack for Numbers
typedef struct node_N {
    Number *number;
    struct node_N *next;
} node_N;

typedef node_N *stack_N;

node_N *init_node_N(Number *);
bool is_empty_N(stack_N *);
void push_N(stack_N *, Number *);
void pop_N(stack_N *);

// Stack for char
typedef struct node_C {
    char character;
    struct node_C *next;
} node_C;

typedef node_C *stack_C;

node_C *init_node_C(char);
bool is_empty_C(stack_C *);
void push_C(stack_C *, char);
void pop_C(stack_C *);

#endif //BC_STACK_H
