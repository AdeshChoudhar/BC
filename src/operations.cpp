//
// Created by adeshchoudhar on 13/12/21.
//

#include "operations.h"

void add(Number *answer, Number number1, Number number2) {
    if (number1.sign == ZERO && number2.sign == ZERO) {
        answer->insertFront(CHR(0));
        answer->sign = ZERO;
        return;
    } else if (number1.sign == ZERO) {
        duplicateNumber(answer, &number2);
        return;
    } else if (number2.sign == ZERO) {
        duplicateNumber(answer, &number1);
        return;
    }
    if (number1.sign == PLUS) {
        if (number2.sign == PLUS) {
            int cmp = compareNumber(number1, number2);
            if (cmp == -1) {
                add(answer, number2, number1);
                return;
            }
            int tmp, res, cry = 0;
            Digit *t1 = number1.tail, *t2 = number2.tail;
            while ((t1 != nullptr) && (t2 != nullptr)) {
                tmp = ORD(t1->value) + ORD(t2->value) + cry;
                res = tmp % 10;
                cry = tmp / 10;
                answer->insertFront(CHR(res));
                t1 = t1->previous;
                t2 = t2->previous;
            }
            while (t1 != nullptr) {
                tmp = ORD(t1->value) + cry;
                res = tmp % 10;
                cry = tmp / 10;
                answer->insertFront(CHR(res));
                t1 = t1->previous;
            }
            if (cry) {
                answer->insertFront(CHR(cry));
            }
            answer->sign = PLUS;
        } else {
            number2.sign = PLUS;
            subtract(answer, number1, number2);
        }
    } else {
        number1.sign = PLUS;
        if (number2.sign == PLUS) {
            subtract(answer, number2, number1);
        } else {
            number2.sign = PLUS;
            add(answer, number1, number2);
            answer->sign = MINUS;
        }
    }
}

void subtract(Number *answer, Number number1, Number number2) {
    if (number1.sign == ZERO && number2.sign == ZERO) {
        answer->insertFront(CHR(0));
        answer->sign = ZERO;
        return;
    } else if (number1.sign == ZERO) {
        duplicateNumber(answer, &number2);
        answer->sign = (answer->sign == PLUS) ? MINUS : PLUS;
        return;
    } else if (number2.sign == ZERO) {
        duplicateNumber(answer, &number1);
        return;
    }
    if (number1.sign == PLUS) {
        if (number2.sign == PLUS) {
            int cmp = compareNumber(number1, number2);
            if (cmp == 0) {
                answer->insertBack(CHR(0));
                answer->sign = ZERO;
                return;
            } else if (cmp == -1) {
                subtract(answer, number2, number1);
                answer->sign = MINUS;
                return;
            }
            int tmp, res, brw = 0;
            Digit *t1 = number1.tail, *t2 = number2.tail;
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
            while (t1 != nullptr) {
                answer->insertFront(CHR(ORD(t1->value) - brw));
                t1 = t1->previous;
                brw = 0;
            }
            removeLeadingZeroes(answer);
        } else {
            number2.sign = PLUS;
            add(answer, number1, number2);
        }
        answer->sign = PLUS;
    } else {
        number1.sign = PLUS;
        if (number2.sign == PLUS) {
            add(answer, number1, number2);
            answer->sign = MINUS;
        } else {
            number2.sign = PLUS;
            subtract(answer, number2, number1);
        }
    }
}
