//
// Created by adeshchoudhar on 30/05/22.
//

#include "gtest/gtest.h"
#include "../functions.h"

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}

string stringNumber(Number number) {
    string str;
    if (number.sign == MINUS) {
        str.push_back('-');
    }
    Digit *current = number.head;
    while (current) {
        str.push_back(current->value);
        current = current->next;
    }
    return str;
}

vector<pair<string, string>> numbers = {
        {"0", "0"}, {"0", "123"}, {"123", "0"}, {"0", "-123"}, {"-123", "0"},
        {"123", "123"}, {"123123", "123"}, {"123", "123123"},
        {"123", "-123"}, {"123123", "-123"}, {"123", "-123123"},
        {"-123", "123"}, {"-123123", "123"}, {"-123", "123123"},
        {"-123", "-123"}, {"-123123", "-123"}, {"-123", "-123123"},
};

TEST(BC_functions, BC_add) {
    vector<string> answers = {
            "0", "123", "123", "-123", "-123",
            "246", "123246", "123246",
            "0", "123000", "-123000",
            "0", "-123000", "123000",
            "-246", "-123246", "-123246"
    };
    for (uint i = 0, n = numbers.size(); i < n; i++) {
        Number number1(numbers[i].first), number2(numbers[i].second), answer;
        add(&answer, number1, number2);
        EXPECT_EQ(stringNumber(answer), answers[i]);
    }
}

TEST(BC_functions, BC_subtract) {
    vector<string> answers = {
            "0", "-123", "123", "123", "-123",
            "0", "123000", "-123000",
            "246", "123246", "123246",
            "-246", "-123246", "-123246",
            "0", "-123000", "123000"
    };
    for (uint i = 0, n = numbers.size(); i < n; i++) {
        Number number1(numbers[i].first), number2(numbers[i].second), answer;
        subtract(&answer, number1, number2);
        EXPECT_EQ(stringNumber(answer), answers[i]);
    }
}
