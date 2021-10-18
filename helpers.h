//
// Created by adeshchoudhar on 16/07/21.
//

#ifndef BC_HELPERS_H
#define BC_HELPERS_H

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <stdarg.h>

void throw_error(int);
bool is_valid_value(int);
bool is_valid_character(char);
bool is_valid_operator(const char *);

#endif //BC_HELPERS_H
