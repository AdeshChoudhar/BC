//
// Created by adeshchoudhar on 13/12/21.
//

#include "Number.h"

Number::Number() {
    this->sign = ZERO;
    this->length = 0;
    this->head = nullptr;
    this->tail = nullptr;
}

Number::Number(string s) {
    bool isNegative = (s[0] == '-');
    if (isNegative) {
        s = s.substr(1);
    }
    this->length = 0;
    this->head = nullptr;
    this->tail = nullptr;
    for (char c: s) {
        insertBack(c);
    }
    if (this->length != 0) {
        this->sign = isNegative ? MINUS : PLUS;
    }
    removeLeadingZeroes(this);
}

void Number::insertBack(char v) {
    Digit *digit = new Digit(v);
    if (digit->value == '\0') {
        return;
    }
    if (this->length == 0) {
        this->head = digit;
        this->tail = digit;
    } else {
        digit->previous = this->tail;
        this->tail->next = digit;
        this->tail = digit;
    }
    this->length += 1;
}

void Number::insertFront(char v) {
    Digit *digit = new Digit(v);
    if (digit->value == '\0') {
        return;
    }
    if (this->length == 0) {
        this->head = digit;
        this->tail = digit;
    } else {
        digit->next = this->head;
        this->head->previous = digit;
        this->head = digit;
    }
    this->length += 1;
}

void Number::removeBack() {
    if (this->length == 0) {
        return;
    }
    Digit *tmp = this->tail;
    if (this->length == 1) {
        this->head = nullptr;
        this->tail = nullptr;
    } else {
        this->tail = tmp->previous;
        this->tail->next = nullptr;
        tmp->previous = nullptr;
    }
    this->length -= 1;
    delete tmp;
}

void Number::removeFront() {
    if (this->length == 0) {
        return;
    }
    Digit *tmp = this->head;
    if (this->length == 1) {
        this->head = nullptr;
        this->tail = nullptr;
    } else {
        this->head = tmp->next;
        this->head->previous = nullptr;
        tmp->next = nullptr;
    }
    this->length -= 1;
    delete tmp;
}

void removeLeadingZeroes(Number *number) {
    if (number->length == 0) {
        return;
    }
    while ((number->head->next != nullptr) && (number->head->value == CHR(0))) {
        number->removeFront();
    }
    if ((number->length == 1) && (number->head->value == CHR(0))) {
        number->sign = ZERO;
    }
}

void printNumber(Number number) {
    if (number.sign == MINUS) {
        cout << "-";
    }
    Digit *current = number.head;
    while (current) {
        cout << current->value;
        current = current->next;
    }
    cout << endl;
}
