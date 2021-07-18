//
// Created by adeshchoudhar on 16/07/21.
//

#include "function.h"

void copy_number(Number *number1, Number *number2) {
    while (number1->head) {
        remove_front(number1);
    }

    Digit *current_digit = number2->head;
    while (current_digit) {
        insert_back(number1, CHR(current_digit->value));
        current_digit = current_digit->next;
    }

    number1->sign = number2->sign;
}

void make_length_equal(Number *number1, Number *number2) {
    int diff = number1->length - number2->length;
    if (diff < 0) {
        for (int i = 0; i < abs(diff); i++) {
            insert_front(number1, '0');
        }
    } else if (diff > 0) {
        for (int i = 0; i < diff; i++) {
            insert_front(number2, '0');
        }
    }
}

int compare_numbers(Number *number1, Number *number2) {
    make_length_equal(number1, number2);

    Digit *d1 = number1->head;
    Digit *d2 = number2->head;
    for (int i = 0; i < number1->length; i++, d1 = d1->next, d2 = d2->next) {
        if (d1->value < d2->value) {
            return -1;
        } else if (d1->value > d2->value) {
            return 1;
        }
    }

    return 0;
}

void increment(Number *number) {
    if (number->tail) {
        if (number->sign == PLUS) {
            if (number->tail->value == 9) {
                number->tail->value = 0;
                if (number->tail->prev) {
                    number->tail = number->tail->prev;
                    increment(number);
                    number->tail = number->tail->next;
                } else {
                    insert_front(number, '1');
                }
            } else {
                number->tail->value += 1;
            }
        } else {
            number->sign = PLUS;
            decrement(number);
            number->sign = is_zero(number) ? PLUS : MINUS;
        }
    }
}

void decrement(Number *number) {
    if (number->tail) {
        if (number->sign == PLUS) {
            if (number->tail->value == 0) {
                if (number->tail->prev) {
                    number->tail->value = 9;
                    number->tail = number->tail->prev;
                    decrement(number);
                    number->tail = number->tail->next;
                    clean_number(number);
                } else {
                    number->sign = is_zero(number) ? MINUS : PLUS;
                    number->tail->value += is_zero(number) ? 1 : -1;
                }
            } else {
                number->tail->value -= 1;
            }
        } else {
            number->sign = PLUS;
            increment(number);
            number->sign = MINUS;
        }
    }
}

Number *add(Number *number1, Number *number2) {
    Number *res;

    clean_number(number1);
    clean_number(number2);

    make_length_equal(number1, number2);

    if (number1->sign == number2->sign) {
        res = init_number();
        int current_value, carry = 0;
        Digit *t1 = number1->tail;
        Digit *t2 = number2->tail;
        for (int i = 0; i < number1->length; i++, t1 = t1->prev, t2 = t2->prev) {
            current_value = t1->value + t2->value + carry;
            carry = current_value / 10;
            insert_front(res, CHR(current_value % 10));
        }
        if (carry) {
            insert_front(res, CHR(carry));
        }
        res->sign = number1->sign;
    } else {
        if (number1->sign == PLUS) {
            number2->sign = PLUS;
            res = subtract(number1, number2);
            number2->sign = MINUS;
        } else {
            number1->sign = PLUS;
            res = subtract(number2, number1);
            number1->sign = MINUS;
        }
    }

    clean_number(number1);
    clean_number(number2);
    clean_number(res);

    return res;
}

Number *subtract(Number *number1, Number *number2) {
    Number *res;

    clean_number(number1);
    clean_number(number2);

    make_length_equal(number1, number2);

    if (number1->sign == number2->sign) {
        if (number1->sign == PLUS) {
            int current_value, tmp_value, borrow = 0;
            Digit *t1 = number1->tail;
            Digit *t2 = number2->tail;
            if (compare_numbers(number1, number2) == 1) {
                res = init_number();
                for (int i = 0; i < number1->length; i++, t1 = t1->prev, t2 = t2->prev) {
                    tmp_value = t1->value - borrow;
                    if (tmp_value >= t2->value) {
                        current_value = tmp_value - t2->value;
                        borrow = 0;
                        insert_front(res, CHR(current_value));
                    } else {
                        tmp_value += 10;
                        current_value = tmp_value - t2->value;
                        borrow = 1;
                        insert_front(res, CHR(current_value));
                    }
                }
                res->sign = PLUS;
            } else if (compare_numbers(number1, number2) == -1) {
                res = subtract(number2, number1);
                res->sign = MINUS;
            } else {
                res = init_number();
                insert_front(res, '0');
            }
        } else {
            number1->sign = PLUS;
            number2->sign = PLUS;
            res = subtract(number2, number1);
            number1->sign = MINUS;
            number2->sign = MINUS;
        }
    } else {
        if (number1->sign == PLUS) {
            number2->sign = PLUS;
            res = add(number1, number2);
            number2->sign = MINUS;
            res->sign = PLUS;
        } else {
            number1->sign = PLUS;
            res = add(number1, number2);
            number1->sign = MINUS;
            res->sign = MINUS;
        }
    }

    clean_number(number1);
    clean_number(number2);
    clean_number(res);

    return res;
}

Number *multiply(Number *number1, Number *number2) {
    Number *res = init_number();

    make_length_equal(number1, number2);

    clean_number(number1);
    clean_number(number2);

    Number *arr[number2->length];

    Digit *t1;
    Digit *t2 = number2->tail;
    int current_value, carry;
    for (int i = 0; i < number2->length; i++, t2 = t2->prev) {
        carry = 0;
        t1 = number1->tail;

        Number *new_number = init_number();
        for (int j = 0; j < i; j++) {
            insert_front(new_number, '0');
        }
        for (int j = 0; j < number1->length; j++, t1 = t1->prev) {
            current_value = t1->value * t2->value + carry;
            carry = current_value / 10;
            insert_front(new_number, CHR(current_value % 10));
        }
        if (carry) {
            insert_front(new_number, CHR(carry));
        }
        clean_number(new_number);
        arr[i] = new_number;
    }

    copy_number(res, arr[0]);
    delete_number(arr[0]);
    for (int i = 1; i < number2->length; i++) {
        Number *tmp = add(res, arr[i]);
        copy_number(res, tmp);
        delete_number(tmp);
        delete_number(arr[i]);
    }

    if (number1->sign == number2->sign) {
        res->sign = PLUS;
    } else {
        res->sign = MINUS;
    }

    clean_number(number1);
    clean_number(number2);
    clean_number(res);

    return res;
}

Number *divide(Number *number1, Number *number2) {
    Number *res;

    if (is_zero(number2)) {
        throw_error(6);
    }

    res = init_number();
    insert_front(res, '0');

    Number *tmp;
    Number *number1_copy = init_number();
    copy_number(number1_copy, number1);
    while (compare_numbers(number1_copy, number2) != -1) {
        tmp = subtract(number1_copy, number2);
        copy_number(number1_copy, tmp);
        delete_number(tmp);
        increment(res);
    }

    if (number1->sign == number2->sign) {
        res->sign = PLUS;
    } else {
        res->sign = MINUS;
    }

    return res;
}
