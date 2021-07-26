//
// Created by adeshchoudhar on 16/07/21.
//

#include "stack.h"

node_N *init_node_N(Number *number) {
    if (!number) {
        return NULL;
    }

    node_N *new_node_N = (node_N *) malloc(sizeof(node_N));
    if (!new_node_N) {
        throw_error(4);
        return NULL;
    }

    new_node_N->number = number;
    new_node_N->next = NULL;

    return new_node_N;
}

bool is_empty_N(stack_N *stack) {
    return (*stack == NULL);
}

void push_N(stack_N *stack, Number *number) {
    node_N *new_node_N = init_node_N(number);
    if (!new_node_N) {
        return;
    }

    new_node_N->next = *stack;
    *stack = new_node_N;
}

Number *pop_N(stack_N *stack) {
    if (is_empty_N(stack)) {
        return NULL;
    }

    node_N *tmp = *stack;
    *stack = (*stack)->next;

    Number *number = init_number();
    copy_number(number, tmp->number);
    tmp->next = NULL;
    free(tmp);
    return number;
}

Number *top_N(stack_N *stack) {
    return is_empty_N(stack) ? NULL : (*stack)->number;
}

node_C *init_node_C(char *operator) {
    if (!is_valid_operator(operator)) {
        return NULL;
    }

    node_C *new_node_C = (node_C *) malloc(sizeof(node_C));
    if (!new_node_C) {
        throw_error(5);
        return NULL;
    }

    new_node_C->operator = operator;
    new_node_C->next = NULL;

    return new_node_C;
}

bool is_empty_C(stack_C *stack) {
    return (*stack == NULL);
}

void push_C(stack_C *stack, char *operator) {
    node_C *new_node_C = init_node_C(operator);
    if (!new_node_C) {
        return;
    }

    new_node_C->next = *stack;
    *stack = new_node_C;
}

char *pop_C(stack_C *stack) {
    if (is_empty_C(stack)) {
        return "";
    }

    node_C *tmp = *stack;
    *stack = (*stack)->next;

    char *operator = tmp->operator;
    tmp->next = NULL;
    free(tmp);
    return operator;
}

char *top_C(stack_C *stack) {
    return is_empty_C(stack) ? "" : (*stack)->operator;
}
