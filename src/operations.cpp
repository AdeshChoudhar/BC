//
// Created by adeshchoudhar on 13/12/21.
//

#include "operations.h"

void add(Number *answer, Number *number1, Number *number2) {
    if (number1->sign == ZERO && number2->sign == ZERO) {
        answer->insertFront(CHR(0));
        answer->sign = ZERO;
        return;
    } else if (number1->sign == ZERO) {
        answer->copy(*number2);
        return;
    } else if (number2->sign == ZERO) {
        answer->copy(*number1);
        return;
    }
    if (number1->sign == PLUS) {
        if (number2->sign == PLUS) {
            int tmp, res, cry = 0;
            makeLengthEqual(number1, number2);
            Digit *t1 = number1->tail, *t2 = number2->tail;
            while ((t1 != nullptr) && (t2 != nullptr)) {
                tmp = ORD(t1->value) + ORD(t2->value) + cry;
                res = tmp % 10;
                cry = tmp / 10;
                answer->insertFront(CHR(res));
                t1 = t1->previous;
                t2 = t2->previous;
            }
            if (cry) {
                answer->insertFront(CHR(cry));
            }
            removeLeadingZeroes(number1);
            removeLeadingZeroes(number2);
            answer->sign = PLUS;
        } else {
            number2->sign = PLUS;
            subtract(answer, number1, number2);
        }
    } else {
        number1->sign = PLUS;
        if (number2->sign == PLUS) {
            subtract(answer, number2, number1);
        } else {
            number2->sign = PLUS;
            add(answer, number1, number2);
            answer->sign = MINUS;
        }
    }
}

void subtract(Number *answer, Number *number1, Number *number2) {
    if (number1->sign == ZERO && number2->sign == ZERO) {
        answer->insertFront(CHR(0));
        answer->sign = ZERO;
        return;
    } else if (number1->sign == ZERO) {
        answer->copy(*number2);
        answer->sign = (answer->sign == PLUS) ? MINUS : PLUS;
        return;
    } else if (number2->sign == ZERO) {
        answer->copy(*number1);
        return;
    }
    if (number1->sign == PLUS) {
        if (number2->sign == PLUS) {
            int cmp = compareNumbers(number1, number2);
            if (cmp == 0) {
                answer->insertFront(CHR(0));
                answer->sign = ZERO;
                return;
            } else if (cmp == -1) {
                subtract(answer, number2, number1);
                answer->sign = MINUS;
                return;
            }
            int tmp, res, brw = 0;
            makeLengthEqual(number1, number2);
            Digit *t1 = number1->tail, *t2 = number2->tail;
            while (t1 != nullptr && t2 != nullptr) {
                tmp = ORD(t1->value) - brw;
                if (tmp >= ORD(t2->value)) {
                    brw = 0;
                } else {
                    tmp += 10;
                    brw = 1;
                }
                res = tmp - ORD(t2->value);
                answer->insertFront(CHR(res));
                t1 = t1->previous;
                t2 = t2->previous;
            }
            removeLeadingZeroes(answer);
        } else {
            number2->sign = PLUS;
            add(answer, number1, number2);
        }
        answer->sign = PLUS;
    } else {
        number1->sign = PLUS;
        if (number2->sign == PLUS) {
            add(answer, number1, number2);
            answer->sign = MINUS;
        } else {
            number2->sign = PLUS;
            subtract(answer, number2, number1);
        }
    }
}

void multiply(Number *answer, Number *number1, Number *number2) {
    answer->insertFront(CHR(0));
    answer->sign = ZERO;
    if (number1->sign == ZERO || number2->sign == ZERO) {
        return;
    }
    Number *result;
    int tmp, res, cry;
    Digit *t1, *t2 = number2->tail;
    vector<Number *> results(number2->length, nullptr);
    for (uint i = 0, n = number2->length; i < n; i++, t2 = t2->previous) {
        result = new Number();
        for (uint j = 0; j < i; j++) {
            result->insertFront(CHR(0));
        }
        cry = 0;
        t1 = number1->tail;
        while (t1 != nullptr) {
            tmp = ORD(t1->value) * ORD(t2->value) + cry;
            res = tmp % 10;
            cry = tmp / 10;
            result->insertFront(CHR(res));
            t1 = t1->previous;
        }
        if (cry) {
            result->insertFront(CHR(cry));
        }
        result->sign = PLUS;
        results[i] = result;
    }
    Number *addition = new Number();
    for (Number *number: results) {
        add(addition, answer, number);
        answer->copy(*addition);
        addition->clear();
    }
    answer->sign = (number1->sign == number2->sign) ? PLUS : MINUS;
    for (Number *number: results) {
        number->clear();
        delete number;
    }
    delete addition;
}

void divide(Number *answer, Number *number1, Number *number2) {
    if (number2->sign == ZERO) {
        // TODO: ZeroDivisionError
        return;
    } else if (number1->sign == ZERO) {
        answer->insertFront(CHR(0));
        answer->sign = ZERO;
        return;
    }
    answer->sign = (number1->sign == number2->sign) ? PLUS : MINUS;
    number1->sign = PLUS;
    number2->sign = PLUS;
    vector<Number *>results(10, nullptr);
    results[0] = new Number();
    results[0]->insertFront(CHR(0));
    results[0]->sign = ZERO;
    for (int i = 1; i < 10; i++) {
        results[i] = new Number();
        add(results[i], results[i - 1], number2);
    }
    int j;
    Number *remainder = new Number(), *subtraction = new Number();
    remainder->sign = PLUS;
    Digit *h1 = number1->head;
    while (h1 != nullptr) {
        remainder->insertBack(h1->value);
        if (compareNumbers(remainder, number2) == -1) {
            answer->insertBack(CHR(0));
        } else {
            j = 10;
            do {
                j -= 1;
            } while (compareNumbers(remainder, results[j]) == -1);
            answer->insertBack(CHR(j));
            subtract(subtraction, remainder, results[j]);
            remainder->copy(*subtraction);
        }
        h1 = h1->next;
        subtraction->clear();
    }
    removeLeadingZeroes(answer);
    for (Number *number: results) {
        number->clear();
        delete number;
    }
    remainder->clear();
    delete remainder;
    delete subtraction;
}
