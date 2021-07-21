//
// Created by adeshchoudhar on 16/07/21.
//

#include "function.h"

void copy_number(Number *number1, Number *number2) {
    if (!number1 || !number2) {
        return;
    }

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
    if (!number1 || !number2) {
        return;
    }

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
    if (!number1 || !number2) {
        return -2;
    }

    make_length_equal(number1, number2);

    int flag = 0;
    Digit *d1 = number1->head;
    Digit *d2 = number2->head;
    for (int i = 0; i < number1->length; i++, d1 = d1->next, d2 = d2->next) {
        if (d1->value < d2->value) {
            if (number2->sign == PLUS) {
                flag = -1;
            } else {
                flag = 1;
            }
            break;
        } else if (d1->value > d2->value) {
            flag = 1;
            if (number1->sign == PLUS) {
                flag = 1;
            } else {
                flag = -1;
            }
            break;
        }
    }

    return flag;
}

void increment(Number *number) {
    if (!number || !number->tail) {
        return;
    }

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

void decrement(Number *number) {
    if (!number || !number->tail) {
        return;
    }

    if (number->sign == PLUS) {
        if (number->tail->value == 0) {
            if (number->tail->prev) {
                number->tail->value = 9;
                number->tail = number->tail->prev;
                decrement(number);
                number->tail = number->tail->next;
                clean(number);
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

Number *add(Number *number1, Number *number2) {
    if (!number1 || !number2) {
        return NULL;
    }

    Number *res;

    clean(number1);
    clean(number2);

    if (is_zero(number1)) {
        res = init_number();
        copy_number(res, number2);
        return res;
    }
    if (is_zero(number2)) {
        res = init_number();
        copy_number(res, number1);
        return res;
    }

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

    clean(number1);
    clean(number2);
    clean(res);

    return res;
}

Number *subtract(Number *number1, Number *number2) {
    if (!number1 || !number2) {
        return NULL;
    }

    Number *res;

    clean(number1);
    clean(number2);

    if (is_zero(number1)) {
        res = init_number();
        copy_number(res, number2);
        return res;
    }
    if (is_zero(number2)) {
        res = init_number();
        copy_number(res, number1);
        return res;
    }

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
                insert_back(res, '0');
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

    clean(number1);
    clean(number2);
    clean(res);

    return res;
}

Number *multiply(Number *number1, Number *number2) {
    if (!number1 || !number2) {
        return NULL;
    }

    Number *res = init_number();

    clean(number1);
    clean(number2);

    if (is_zero(number1) || is_zero(number2)) {
        insert_front(res, '0');
        return res;
    }

    Number *arr[number2->length];

    Digit *t1;
    Digit *t2 = number2->tail;
    int current_value, carry;
    for (int i = 0; i < number2->length; i++, t2 = t2->prev) {
        carry = 0;
        t1 = number1->tail;

        Number *new_number = init_number();
        for (int j = 0; j < i; j++) {
            insert_back(new_number, '0');
        }
        for (int j = 0; j < number1->length; j++, t1 = t1->prev) {
            current_value = t1->value * t2->value + carry;
            carry = current_value / 10;
            insert_front(new_number, CHR(current_value % 10));
        }
        if (carry) {
            insert_front(new_number, CHR(carry));
        }
        clean(new_number);
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

    clean(number1);
    clean(number2);
    clean(res);

    return res;
}

Pair div_mod(Number *number1, Number *number2) {
    Pair pair = {.first = NULL, .second = NULL};
    if (!number1 || !number2) {
        return pair;
    }

    clean(number1);
    clean(number2);

    if (is_zero(number2)) {
        throw_error(6);
        return pair;
    }

    Number *quotient = init_number();
    Number *remainder = init_number();

    Number *arr[10];
    Number *tmp = init_number();
    insert_back(tmp, '0');
    for (int i = 0; i < 10; i++) {
        arr[i] = multiply(number2, tmp);
        tmp->head->value += 1;
    }

    Number *sub;
    Digit *tmp_head = number1->head;
    for (int i = 0; i < number1->length; i++, tmp_head = tmp_head->next) {
        clean(remainder);
        insert_back(remainder, CHR(tmp_head->value));
        if (compare_numbers(remainder, number2) == -1) {
            insert_back(quotient, '0');
        } else {
            int j = 10;
            do {
                j--;
            } while (compare_numbers(remainder, arr[j]) == -1);

            insert_back(quotient, CHR(j));
            sub = subtract(remainder, arr[j]);
            copy_number(remainder, sub);
            delete_number(sub);
        }
    }

    if (number1->sign == number2->sign) {
        quotient->sign = PLUS;
    } else {
        quotient->sign = MINUS;
    }
    remainder->sign = PLUS;

    for (int i = 0; i < 10; i++) {
        delete_number(arr[i]);
    }

    delete_number(tmp);

    clean(quotient);
    clean(remainder);

    pair.first = quotient;
    pair.second = remainder;

    return pair;
}

Number *divide(Number *number1, Number *number2) {
    if (!number1 || !number2) {
        return NULL;
    }

    if (is_zero(number2)) {
        throw_error(6);
        return NULL;
    }

    Pair pair = div_mod(number1, number2);
    delete_number(pair.second);

    Number *res = pair.first;

    return res;
}

Number *modulo(Number *number1, Number *number2) {
    if (!number1 || !number2) {
        return NULL;
    }

    if (is_zero(number2)) {
        throw_error(6);
        return NULL;
    }

    Pair pair = div_mod(number1, number2);
    delete_number(pair.first);

    Number *res = pair.second;

    return res;
}

Number *power(Number *number1, Number *number2) {
    if (!number1 || !number2) {
        return NULL;
    }

    Number *res = init_number();

    clean(number1);
    clean(number2);

    Number *zero = init_number();
    insert_back(zero, '0');
    Number *one = init_number();
    insert_back(one, '1');

    if (compare_numbers(number2, zero) == -1) {
        insert_back(res, '0');
    } else if (is_zero(number2)) {
        insert_back(res, '1');
    } else if (is_zero(number1)) {
        insert_back(res, '0');
    } else if (compare_numbers(number1, one) == 0) {
        insert_back(res, '1');
        res->sign = (number1->sign == MINUS) ? odd_even(number2) == 1 ? MINUS : PLUS : PLUS;
    } else if (compare_numbers(number2, one) == 0) {
        copy_number(res, number1);
    } else {
        insert_back(res, '1');
        Number *number2_binary, *tmp;
        number2_binary = binary(number2);
        Digit *current_digit = number2_binary->head;
        for (int i = 0; i < number2_binary->length; i++, current_digit = current_digit->next) {
            tmp = multiply(res, res);
            copy_number(res, tmp);
            delete_number(tmp);
            if (current_digit->value) {
                tmp = multiply(res, number1);
                copy_number(res, tmp);
                delete_number(tmp);
            }
        }
        delete_number(number2_binary);
    }

    delete_number(zero);
    delete_number(one);

    clean(res);

    return res;
}

Number *binary(Number *number) {
    if (!number) {
        return NULL;
    }

    Number *res = init_number();

    clean(number);

    Number *number_copy = init_number();
    copy_number(number_copy, number);
    number_copy->sign = PLUS;
    Number *two = init_number();
    insert_back(two, '2');

    Number *tmp;
    do {
        if (odd_even(number_copy) == 1) {
            insert_front(res, '1');
        } else if (odd_even(number_copy) == 0) {
            insert_front(res, '0');
        }
        tmp = divide(number_copy, two);
        copy_number(number_copy, tmp);
        delete_number(tmp);
    } while (!is_zero(number_copy));
    res->sign = number->sign;

    delete_number(two);
    delete_number(number_copy);

    clean(res);

    return res;
}

Number *decimal(Number *number) {
    if (!number || !is_binary(number)) {
        return NULL;
    }

    Number *res = init_number();
    insert_back(res, '0');

    clean(number);

    Number *base = init_number();
    insert_back(base, '1');
    Number *two = init_number();
    insert_back(two, '2');

    Number *tmp;
    Digit *current_digit = number->tail;
    while (current_digit) {
        if (current_digit->value) {
            tmp = add(res, base);
            copy_number(res, tmp);
            delete_number(tmp);
        }
        tmp = multiply(base, two);
        copy_number(base, tmp);
        delete_number(tmp);
        current_digit = current_digit->prev;
    }
    res->sign = number->sign;

    delete_number(base);
    delete_number(two);

    clean(res);

    return res;
}
