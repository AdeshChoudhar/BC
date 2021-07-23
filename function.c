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

    Number *n1 = init_number();
    copy_number(n1, number1);

    Number *n2 = init_number();
    copy_number(n2, number2);

    clean_numbers(2, n1, n2);
    make_length_equal(n1, n2);

    int flag = 0;
    Digit *d1 = n1->head;
    Digit *d2 = n2->head;
    for (int i = 0; i < n1->length; i++, d1 = d1->next, d2 = d2->next) {
        if (d1->value < d2->value) {
            if (n2->sign == PLUS) {
                flag = -1;
            } else {
                flag = 1;
            }
            break;
        } else if (d1->value > d2->value) {
            if (n1->sign == PLUS) {
                flag = 1;
            } else {
                flag = -1;
            }
            break;
        }
    }

    delete_numbers(2, n1, n2);

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

Number *add(Number *number1, Number *number2) {
    if (!number1 || !number2) {
        return NULL;
    }

    Number *res;

    Number *n1 = init_number();
    copy_number(n1, number1);

    Number *n2 = init_number();
    copy_number(n2, number2);

    clean_numbers(2, n1, n2);

    if (is_zero(n1)) {
        res = init_number();
        copy_number(res, n2);
        delete_numbers(2, n1, n2);
        return res;
    }
    if (is_zero(n2)) {
        res = init_number();
        copy_number(res, n1);
        delete_numbers(2, n1, n2);
        return res;
    }

    make_length_equal(n1, n2);

    if (n1->sign == n2->sign) {
        res = init_number();
        int current_value, carry = 0;
        Digit *t1 = n1->tail;
        Digit *t2 = n2->tail;
        for (int i = 0; i < n1->length; i++, t1 = t1->prev, t2 = t2->prev) {
            current_value = t1->value + t2->value + carry;
            carry = current_value / 10;
            insert_front(res, CHR(current_value % 10));
        }
        if (carry) {
            insert_front(res, CHR(carry));
        }
        res->sign = n1->sign;
    } else {
        if (n1->sign == PLUS) {
            n2->sign = PLUS;
            res = subtract(n1, n2);
            n2->sign = MINUS;
        } else {
            n1->sign = PLUS;
            res = subtract(n2, n1);
            n1->sign = MINUS;
        }
    }

    delete_numbers(2, n1, n2);

    clean_number(res);

    return res;
}

Number *subtract(Number *number1, Number *number2) {
    if (!number1 || !number2) {
        return NULL;
    }

    Number *res;

    Number *n1 = init_number();
    copy_number(n1, number1);

    Number *n2 = init_number();
    copy_number(n2, number2);

    clean_numbers(2, n1, n2);

    if (is_zero(n1)) {
        res = init_number();
        copy_number(res, n2);
        delete_numbers(2, n1, n2);
        return res;
    }
    if (is_zero(n2)) {
        res = init_number();
        copy_number(res, n1);
        delete_numbers(2, n1, n2);
        return res;
    }

    make_length_equal(n1, n2);

    if (n1->sign == n2->sign) {
        if (n1->sign == PLUS) {
            int current_value, tmp_value, borrow = 0;
            Digit *t1 = n1->tail;
            Digit *t2 = n2->tail;
            if (compare_numbers(n1, n2) == 1) {
                res = init_number();
                for (int i = 0; i < n1->length; i++, t1 = t1->prev, t2 = t2->prev) {
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
            } else if (compare_numbers(n1, n2) == -1) {
                res = subtract(n2, n1);
                res->sign = MINUS;
            } else {
                res = init_number();
                insert_back(res, '0');
            }
        } else {
            n1->sign = PLUS;
            n2->sign = PLUS;
            res = subtract(n2, n1);
            n1->sign = MINUS;
            n2->sign = MINUS;
        }
    } else {
        if (n1->sign == PLUS) {
            n2->sign = PLUS;
            res = add(n1, n2);
            n2->sign = MINUS;
            res->sign = PLUS;
        } else {
            n1->sign = PLUS;
            res = add(n1, n2);
            n1->sign = MINUS;
            res->sign = MINUS;
        }
    }

    delete_numbers(2, n1, n2);

    clean_number(res);

    return res;
}

Number *multiply(Number *number1, Number *number2) {
    if (!number1 || !number2) {
        return NULL;
    }

    Number *res = init_number();

    Number *n1 = init_number();
    copy_number(n1, number1);

    Number *n2 = init_number();
    copy_number(n2, number2);

    clean_numbers(2, n1, n2);

    if (is_zero(n1) || is_zero(n2)) {
        insert_front(res, '0');
        delete_numbers(2, n1, n2);
        return res;
    }

    Number *arr[n2->length];

    Digit *t1;
    Digit *t2 = n2->tail;
    int current_value, carry;
    for (int i = 0; i < n2->length; i++, t2 = t2->prev) {
        carry = 0;
        t1 = n1->tail;

        Number *new_number = init_number();
        for (int j = 0; j < i; j++) {
            insert_back(new_number, '0');
        }
        for (int j = 0; j < n1->length; j++, t1 = t1->prev) {
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
    for (int i = 1; i < n2->length; i++) {
        Number *tmp = add(res, arr[i]);
        copy_number(res, tmp);
        delete_numbers(2, tmp, arr[i]);
    }

    if (n1->sign == n2->sign) {
        res->sign = PLUS;
    } else {
        res->sign = MINUS;
    }

    delete_numbers(2, n1, n2);

    clean_number(res);

    return res;
}

Pair div_mod(Number *number1, Number *number2) {
    Pair pair = {.first = NULL, .second = NULL};
    if (!number1 || !number2) {
        return pair;
    }

    Number *n1 = init_number();
    copy_number(n1, number1);

    Number *n2 = init_number();
    copy_number(n2, number2);

    clean_numbers(2, n1, n2);

    if (is_zero(n2)) {
        throw_error(6);
        delete_numbers(2, n1, n2);
        return pair;
    }

    Number *quotient = init_number();
    Number *remainder = init_number();

    Number *arr[10];
    Number *tmp = init_number();
    insert_back(tmp, '0');
    tmp->sign = n2->sign;
    for (int i = 0; i < 10; i++) {
        arr[i] = multiply(n2, tmp);
        tmp->head->value += 1;
    }

    Number *sub;
    Digit *tmp_head = n1->head;
    for (int i = 0; i < n1->length; i++, tmp_head = tmp_head->next) {
        clean_number(remainder);
        insert_back(remainder, CHR(tmp_head->value));
        if (compare_numbers(remainder, n2) == -1) {
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

    if (n1->sign == n2->sign) {
        quotient->sign = PLUS;
    } else {
        quotient->sign = MINUS;
    }
    remainder->sign = PLUS;

    for (int i = 0; i < 10; i++) {
        delete_number(arr[i]);
    }

    delete_numbers(3, n1, n2, tmp);

    clean_numbers(2, quotient, remainder);

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

    Number *n1 = init_number();
    copy_number(n1, number1);

    Number *n2 = init_number();
    copy_number(n2, number2);

    clean_numbers(2, n1, n2);

    Number *zero = init_number();
    insert_back(zero, '0');

    Number *one = init_number();
    insert_back(one, '1');

    if (compare_numbers(n2, zero) == -1) {
        insert_back(res, '0');
    } else if (is_zero(n2)) {
        insert_back(res, '1');
    } else if (is_zero(n1)) {
        insert_back(res, '0');
    } else if (compare_numbers(n1, one) == 0) {
        insert_back(res, '1');
        res->sign = (n1->sign == MINUS) ? odd_even(n2) == 1 ? MINUS : PLUS : PLUS;
    } else if (compare_numbers(n2, one) == 0) {
        copy_number(res, n1);
    } else {
        insert_back(res, '1');
        Number *number2_binary, *tmp;
        number2_binary = binary(n2);
        Digit *current_digit = number2_binary->head;
        for (int i = 0; i < number2_binary->length; i++, current_digit = current_digit->next) {
            tmp = multiply(res, res);
            copy_number(res, tmp);
            delete_number(tmp);
            if (current_digit->value) {
                tmp = multiply(res, n1);
                copy_number(res, tmp);
                delete_number(tmp);
            }
        }
        delete_number(number2_binary);
    }

    delete_numbers(4, n1, n2, zero, one);

    clean_number(res);

    return res;
}

Number *binary(Number *number) {
    if (!number) {
        return NULL;
    }

    Number *res = init_number();

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

    delete_numbers(2, two, number_copy);

    clean_number(res);

    return res;
}

Number *decimal(Number *number) {
    if (!number || !is_binary(number)) {
        return NULL;
    }

    Number *res = init_number();
    insert_back(res, '0');

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

    delete_numbers(2, base, two);

    clean_number(res);

    return res;
}

Number *shift_left(Number *number1, Number *number2) {
    if (!number1 || !number2) {
        return NULL;
    }

    if (number2->sign == MINUS) {
        throw_error(7);
        return NULL;
    }

    Number *res = init_number();

    Number *cnt = init_number();
    copy_number(cnt, number2);

    Number *one = init_number();
    insert_back(one, '1');

    Number *tmp1;
    Number *tmp2 = init_number();
    copy_number(tmp2, number1);
    while (!is_zero(cnt)) {
        tmp1 = binary(tmp2);
        insert_back(tmp1, '0');
        copy_number(tmp2, tmp1);
        delete_number(tmp1);

        tmp1 = decimal(tmp2);
        copy_number(tmp2, tmp1);
        delete_number(tmp1);

        tmp1 = subtract(cnt, one);
        copy_number(cnt, tmp1);
        delete_number(tmp1);
    }
    copy_number(res, tmp2);

    delete_numbers(3, cnt, one, tmp2);

    return res;
}

Number *shift_right(Number *number1, Number *number2) {
    if (!number1 || !number2) {
        return NULL;
    }

    if (number2->sign == MINUS) {
        throw_error(7);
        return NULL;
    }

    Number *res = init_number();

    Number *cnt = init_number();
    copy_number(cnt, number2);

    Number *one = init_number();
    insert_back(one, '1');

    Number *tmp1;
    Number *tmp2 = init_number();
    copy_number(tmp2, number1);
    while (!is_zero(cnt)) {
        tmp1 = binary(tmp2);
        remove_back(tmp1);
        copy_number(tmp2, tmp1);
        delete_number(tmp1);

        tmp1 = decimal(tmp2);
        copy_number(tmp2, tmp1);
        delete_number(tmp1);

        tmp1 = subtract(cnt, one);
        copy_number(cnt, tmp1);
        delete_number(tmp1);
    }
    copy_number(res, tmp2);

    delete_numbers(3, cnt, one, tmp2);

    return res;
}
