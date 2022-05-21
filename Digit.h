//
// Created by adeshchoudhar on 13/12/21.
//

#ifndef BC_DIGIT_H
#define BC_DIGIT_H

#include <iostream>

using namespace std;

#define ORD(x) ((x) - '0')
#define CHR(x) ((x) + '0')

class Digit {
public:
    char value;
    Digit *next;
    Digit *previous;

    Digit();
    Digit(char);

    bool isValidDigit(char);
};

#endif //BC_DIGIT_H
