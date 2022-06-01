//
// Created by adeshchoudhar on 13/12/21.
//

#include "Digit.h"

Digit::Digit() {
    this->value = '\0';
    this->next = nullptr;
    this->previous = nullptr;
}

Digit::Digit(char v) {
    this->value = isValidDigit(v) ? v : '\0';
    this->next = nullptr;
    this->previous = nullptr;
}

bool Digit::isValidDigit(char v) {
    return ((ORD(v) >= 0) && (ORD(v) <= 9));
}
