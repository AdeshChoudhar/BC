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

void Number::clear() {
    for (uint i = 0, n = this->length; i < n; i++) {
        this->removeFront();
    }
}

void Number::copy(Number number) {
    this->clear();
    Digit *head = number.head;
    while (head != nullptr) {
        this->insertBack(head->value);
        head = head->next;
    }
    this->sign = number.sign;
}

void Number::print() {
    if (this->sign == MINUS) {
        cout << "-";
    }
    Digit *current = this->head;
    while (current) {
        cout << current->value;
        current = current->next;
    }
    cout << endl;
}

int compareNumbers(Number *number1, Number *number2) {
    makeLengthEqual(number1, number2);
    Digit *h1 = number1->head, *h2 = number2->head;
    while ((h1 != nullptr) && (h2 != nullptr)) {
        if (h1->value < h2->value) {
            return (number2->sign == PLUS) ? -1 : 1;
        } else if (h1->value > h2->value) {
            return (number1->sign == PLUS) ? 1 : -1;
        }
        h1 = h1->next;
        h2 = h2->next;
    }
    removeLeadingZeroes(number1);
    removeLeadingZeroes(number2);
    return 0;
}

void makeLengthEqual(Number *number1, Number *number2) {
    if (number1->length < number2->length) {
        while (number1->length != number2->length) {
            number1->insertFront(CHR(0));
        }
    } else {
        while (number1->length != number2->length) {
            number2->insertFront(CHR(0));
        }
    }
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
