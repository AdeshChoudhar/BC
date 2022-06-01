//
// Created by adeshchoudhar on 13/12/21.
//

#ifndef BC_NUMBER_H
#define BC_NUMBER_H

#include "Digit.h"

enum Sign {
    MINUS = -1,
    ZERO = 0,
    PLUS = 1
};


class Number {
public:
    Sign sign;
    uint length;
    Digit *head;
    Digit *tail;

    Number();
    Number(string s);

    void insertBack(char);
    void insertFront(char);
    void removeBack();
    void removeFront();
};

void removeLeadingZeroes(Number *);

int compareNumber(Number number1, Number number2);
void duplicateNumber(Number *, Number *);
void printNumber(Number number);

#endif //BC_NUMBER_H
