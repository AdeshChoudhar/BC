//
// Created by adeshchoudhar on 16/07/21.
//

#include "number.h"

Digit *init_digit(int value) {
    if (value < 0 || value > 9) {
        throw_error(1);
        return NULL;
    }

    Digit *new_digit = (Digit *) malloc(sizeof(Digit));
    if (!new_digit) {
        throw_error(2);
        return NULL;
    }

    new_digit->value = value;
    new_digit->next = NULL;
    new_digit->prev = NULL;

    return new_digit;
}

Number *init_number() {
    Number *new_number = (Number *) malloc(sizeof(Number));
    if (!new_number) {
        throw_error(3);
        return NULL;
    }

    new_number->sign = PLUS;
    new_number->length = 0;
    new_number->head = NULL;
    new_number->tail = NULL;

    return new_number;
}

void insert_back(Number *number, char value) {
    if (!number) {
        return;
    }

    Digit *new_digit = init_digit(ORD(value));
    if (number->head == NULL) {
        number->head = new_digit;
        number->tail = new_digit;
    } else {
        new_digit->prev = number->tail;
        number->tail->next = new_digit;
        number->tail = new_digit;
    }
    number->length += 1;
}

void insert_front(Number *number, char value) {
    if (!number) {
        return;
    }

    Digit *new_digit = init_digit(ORD(value));
    if (number->head == NULL) {
        number->head = new_digit;
        number->tail = new_digit;
    } else {
        new_digit->next = number->head;
        number->head->prev = new_digit;
        number->head = new_digit;
    }
    number->length += 1;
}

void remove_back(Number *number) {
    if (!number || !number->tail) {
        return;
    }

    Digit *tmp = number->tail;
    if (tmp->prev) {
        number->tail = tmp->prev;
        number->tail->next = NULL;
        tmp->prev = NULL;
    } else {
        number->tail = NULL;
        number->head = NULL;
    }
    free(tmp);
    number->length -= 1;

}

void remove_front(Number *number) {
    if (!number || !number->head) {
        return;
    }

    Digit *tmp = number->head;
    if (tmp->next) {
        number->head = tmp->next;
        number->head->prev = NULL;
        tmp->next = NULL;
    } else {
        number->head = NULL;
        number->tail = NULL;
    }
    free(tmp);
    number->length -= 1;
}

bool is_valid_character(char character) {
    char valid_characters[] = {'+', '-', '*', '/'};
    int n = sizeof(valid_characters) / sizeof(valid_characters[0]);
    for (int i = 0; i < n; i++) {
        if (character == valid_characters[i]) {
            return true;
        }
    }
    return false;
}

bool is_zero(Number *number) {
    return (number && number->length == 1 && number->head->value == 0);
}

void clean_number(Number *number) {
    // Removing leading zeroes
    while (number && number->head && (number->head->value == 0) && number->length > 1) {
        remove_front(number);
    }
}

void show_number(Number *number) {
    if (!number) {
        return;
    }

    Digit *current_digit = number->head;
    while (current_digit) {
        printf("%d", current_digit->value);
        current_digit = current_digit->next;
    }
    printf("\n");
}

void delete_number(Number *number) {
    if (!number) {
        return;
    }

    Digit *current_digit = number->head;
    while (current_digit) {
        remove_front(number);
        current_digit = number->head;
    }
    number->head = NULL;
    number->tail = NULL;
    free(number);
}
