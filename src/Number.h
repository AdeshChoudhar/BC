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
    ~Number();

    void insertBack(char);
    void insertFront(char);
    void removeBack();
    void removeFront();
};

void removeLeadingZeroes(Number *);

int compareNumber(Number *, Number *);
void copyNumber(Number *, Number *);
void makeLengthEqual(Number *, Number *);
void printNumber(Number *);

#endif //BC_NUMBER_H
