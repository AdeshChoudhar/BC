//
// Created by adeshchoudhar on 13/12/21.
//

#ifndef BC_FUNCTIONS_H
#define BC_FUNCTIONS_H

#include <cstring>

#include "Number.h"

void evaluateExpression(Number *, string &);

int compareNumber(Number number1, Number number2);
void duplicateNumber(Number *, Number *);

void add(Number *, Number, Number);
void subtract(Number *, Number, Number);

#endif //BC_FUNCTIONS_H
