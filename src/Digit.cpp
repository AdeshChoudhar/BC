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
    this->value = ((ORD(v) >= 0) && (ORD(v) <= 9)) ? v : '\0';
    this->next = nullptr;
    this->previous = nullptr;
}
