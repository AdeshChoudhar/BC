//
// Created by adeshchoudhar on 13/12/21.
//

#include "operations.h"

void add(Number *answer, Number *number1, Number *number2) {
    Sign sign1 = number1->sign, sign2 = number2->sign;
    if (sign1 == ZERO && sign2 == ZERO) {
        answer->insertFront(CHR(0));
        answer->sign = ZERO;
        return;
    } else if (sign1 == ZERO) {
        answer->copy(*number2);
        return;
    } else if (sign2 == ZERO) {
        answer->copy(*number1);
        return;
    }

    number1->sign = PLUS, number2->sign = PLUS;
    if (sign1 == PLUS) {
        if (sign2 == PLUS) {
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
            subtract(answer, number1, number2);
        }
    } else {
        if (sign2 == PLUS) {
            subtract(answer, number2, number1);
        } else {
            add(answer, number1, number2);
            answer->sign = MINUS;
        }
    }
    number1->sign = sign1, number2->sign = sign2;
}

void subtract(Number *answer, Number *number1, Number *number2) {
    Sign sign1 = number1->sign, sign2 = number2->sign;
    if (sign1 == ZERO && sign2 == ZERO) {
        answer->insertFront(CHR(0));
        answer->sign = ZERO;
        return;
    } else if (sign1 == ZERO) {
        answer->copy(*number2);
        answer->sign = (answer->sign == PLUS) ? MINUS : PLUS;
        return;
    } else if (sign2 == ZERO) {
        answer->copy(*number1);
        return;
    }

    number1->sign = PLUS, number2->sign = PLUS;
    if (sign1 == PLUS) {
        if (sign2 == PLUS) {
            int cmp = compareNumbers(number1, number2);
            if (cmp == 0) {
                answer->insertFront(CHR(0));
                answer->sign = ZERO;
            } else if (cmp == -1) {
                subtract(answer, number2, number1);
                answer->sign = MINUS;
            } else {
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
                removeLeadingZeroes(number1);
                removeLeadingZeroes(number2);
                removeLeadingZeroes(answer);
                answer->sign = PLUS;
            }
        } else {
            add(answer, number1, number2);
            answer->sign = PLUS;
        }
    } else {
        if (sign2 == PLUS) {
            add(answer, number1, number2);
            answer->sign = MINUS;
        } else {
            subtract(answer, number2, number1);
        }
    }
    number1->sign = sign1, number2->sign = sign2;
}

void multiply(Number *answer, Number *number1, Number *number2) {
    Sign sign1 = number1->sign, sign2 = number2->sign;
    answer->insertFront(CHR(0));
    answer->sign = ZERO;
    if (sign1 == ZERO || sign2 == ZERO) {
        return;
    }

    Number *result;
    int tmp, res, cry;
    Digit *t1, *t2 = number2->tail;
    Number *results[number2->length];
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
    for (uint i = 0; i < number2->length; i++) {
        add(addition, answer, results[i]);
        answer->copy(*addition);
        addition->clear();
    }
    answer->sign = (sign1 == sign2) ? PLUS : MINUS;

    for (uint i = 0; i < number2->length; i++) {
        results[i]->clear();
        delete results[i];
    }
    delete addition;
}

void divide(Number *answer, Number *number1, Number *number2) {
    Sign sign1 = number1->sign, sign2 = number2->sign;
    if (sign2 == ZERO) {
        // TODO: ZeroDivisionError
        return;
    } else if (sign1 == ZERO) {
        answer->insertFront(CHR(0));
        answer->sign = ZERO;
        return;
    }

    Number *results[10], *remainder, *subtraction;
    results[0] = new Number();
    results[0]->insertFront(CHR(0));
    results[0]->sign = ZERO;
    number2->sign = PLUS;
    for (int i = 1; i < 10; i++) {
        results[i] = new Number();
        add(results[i], results[i - 1], number2);
    }
    remainder = new Number();
    remainder->sign = PLUS;
    subtraction = new Number();
    Digit *h1 = number1->head;
    while (h1 != nullptr) {
        remainder->insertBack(h1->value);
        if (compareNumbers(remainder, number2) == -1) {
            answer->insertBack(CHR(0));
        } else {
            int j = 10;
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
    number2->sign = sign2;
    answer->sign = (sign1 == sign2) ? PLUS : MINUS;
    removeLeadingZeroes(answer);

    for (Number *number: results) {
        number->clear();
        delete number;
    }
    remainder->clear();
    delete remainder;
    delete subtraction;
}
