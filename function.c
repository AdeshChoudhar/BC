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
        return 0;
    }

    make_length_equal(number1, number2);

    int flag = 0;
    Digit *d1 = number1->head;
    Digit *d2 = number2->head;
    for (int i = 0; i < number1->length; i++, d1 = d1->next, d2 = d2->next) {
        if (d1->value < d2->value) {
            flag = -1;
            break;
        } else if (d1->value > d2->value) {
            flag = 1;
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

    clean(number1);
    clean(number2);
    make_length_equal(number1, number2);

    Number *res;
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

    clean(number1);
    clean(number2);
    make_length_equal(number1, number2);

    Number *res;
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

    clean(number1);
    clean(number2);
    clean(res);

    return res;
}

Number *multiply(Number *number1, Number *number2) {
    if (!number1 || !number2) {
        return NULL;
    }

    make_length_equal(number1, number2);
    clean(number1);
    clean(number2);

    Number *res = init_number();
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
        clean(new_number);
        arr[i] = new_number;
    }

    if (number1->sign == number2->sign) {
        res->sign = PLUS;
    } else {
        res->sign = MINUS;
    }

    copy_number(res, arr[0]);
    delete_number(arr[0]);
    for (int i = 1; i < number2->length; i++) {
        Number *tmp = add(res, arr[i]);
        copy_number(res, tmp);
        delete_number(tmp);
        delete_number(arr[i]);
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

    if (is_zero(number2)) {
        throw_error(6);
        return pair;
    }

    Number *div = init_number();
    Number *mod = init_number();

    Number *arr[10];
    Number *tmp = init_number();
    insert_front(tmp, '0');
    for (int i = 0; i < 10; i++) {
        arr[i] = multiply(number2, tmp);
        tmp->head->value += 1;
    }

    Number *sub;
    Digit *tmp_head = number1->head;
    for (int i = 0; i < number1->length; i++, tmp_head = tmp_head->next) {
        clean(mod);
        insert_back(mod, CHR(tmp_head->value));
        if (compare_numbers(mod, number2) == -1) {
            insert_back(div, '0');
        } else {
            int j = 10;
            do {
                j--;
            } while (compare_numbers(mod, arr[j]) == -1);

            insert_back(div, CHR(j));
            sub = subtract(mod, arr[j]);
            copy_number(mod, sub);
            delete_number(sub);
        }
    }

    if (number1->sign == number2->sign) {
        div->sign = PLUS;
    } else {
        div->sign = MINUS;
    }
    mod->sign = PLUS;

    for (int i = 0; i < 10; i++) {
        delete_number(arr[i]);
    }

    delete_number(tmp);

    clean(div);
    clean(mod);

    pair.first = div;
    pair.second = mod;

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
