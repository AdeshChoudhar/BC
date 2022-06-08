//
// Created by adeshchoudhar on 30/05/22.
//

#include "gtest/gtest.h"
#include "../src/operations.h"

int main() {
    ::testing::InitGoogleTest();
    return RUN_ALL_TESTS();
}

vector<pair<string, string>> numbers = {
        {"0",       "0"},
        {"0",       "123"},
        {"123",     "0"},
        {"0",       "-123"},
        {"-123",    "0"},
        {"123",     "123"},
        {"123123",  "123"},
        {"123",     "123123"},
        {"123",     "-123"},
        {"123123",  "-123"},
        {"123",     "-123123"},
        {"-123",    "123"},
        {"-123123", "123"},
        {"-123",    "123123"},
        {"-123",    "-123"},
        {"-123123", "-123"},
        {"-123",    "-123123"},
};

TEST(BC_functions, Add) {
    vector<pair<string, Sign>> answers = {
            {"0",       ZERO},
            {"123",     PLUS},
            {"123",     PLUS},
            {"-123",    MINUS},
            {"-123",    MINUS},
            {"246",     PLUS},
            {"123246",  PLUS},
            {"123246",  PLUS},
            {"0",       ZERO},
            {"123000",  PLUS},
            {"-123000", MINUS},
            {"0",       ZERO},
            {"-123000", MINUS},
            {"123000",  PLUS},
            {"-246",    MINUS},
            {"-123246", MINUS},
            {"-123246", MINUS}
    };
    Number answer, number1, number2;
    Sign sign1, sign2;
    for (uint i = 0, n = numbers.size(); i < n; i++) {
        number1 = Number(numbers[i].first), number2 = Number(numbers[i].second);
        sign1 = number1.sign, sign2 = number2.sign;
        add(&answer, &number1, &number2);
        EXPECT_EQ(answer.str(), answers[i].first);
        EXPECT_EQ(answer.sign, answers[i].second);
        EXPECT_EQ(number1.sign, sign1);
        EXPECT_EQ(number2.sign, sign2);
        answer.clear();
        number1.clear();
        number2.clear();
    }
}

TEST(BC_functions, Subtract) {
    vector<pair<string, Sign>> answers = {
            {"0",       ZERO},
            {"-123",    MINUS},
            {"123",     PLUS},
            {"123",     PLUS},
            {"-123",    MINUS},
            {"0",       ZERO},
            {"123000",  PLUS},
            {"-123000", MINUS},
            {"246",     PLUS},
            {"123246",  PLUS},
            {"123246",  PLUS},
            {"-246",    MINUS},
            {"-123246", MINUS},
            {"-123246", MINUS},
            {"0",       ZERO},
            {"-123000", MINUS},
            {"123000",  PLUS}
    };
    Number answer, number1, number2;
    Sign sign1, sign2;
    for (uint i = 0, n = numbers.size(); i < n; i++) {
        number1 = Number(numbers[i].first), number2 = Number(numbers[i].second);
        sign1 = number1.sign, sign2 = number2.sign;
        subtract(&answer, &number1, &number2);
        EXPECT_EQ(answer.str(), answers[i].first);
        EXPECT_EQ(answer.sign, answers[i].second);
        EXPECT_EQ(number1.sign, sign1);
        EXPECT_EQ(number2.sign, sign2);
        answer.clear();
        number1.clear();
        number2.clear();
    }
}

TEST(BC_functions, Multiply) {
    vector<pair<string, Sign>> answers = {
            {"0",         ZERO},
            {"0",         ZERO},
            {"0",         ZERO},
            {"0",         ZERO},
            {"0",         ZERO},
            {"15129",     PLUS},
            {"15144129",  PLUS},
            {"15144129",  PLUS},
            {"-15129",    MINUS},
            {"-15144129", MINUS},
            {"-15144129", MINUS},
            {"-15129",    MINUS},
            {"-15144129", MINUS},
            {"-15144129", MINUS},
            {"15129",     PLUS},
            {"15144129",  PLUS},
            {"15144129",  PLUS}
    };
    Number answer, number1, number2;
    Sign sign1, sign2;
    for (uint i = 0, n = numbers.size(); i < n; i++) {
        number1 = Number(numbers[i].first), number2 = Number(numbers[i].second);
        sign1 = number1.sign, sign2 = number2.sign;
        multiply(&answer, &number1, &number2);
        EXPECT_EQ(answer.str(), answers[i].first);
        EXPECT_EQ(answer.sign, answers[i].second);
        EXPECT_EQ(number1.sign, sign1);
        EXPECT_EQ(number2.sign, sign2);
        answer.clear();
        number1.clear();
        number2.clear();
    }
}

TEST(BC_functions, Divide) {
    vector<pair<string, Sign>> answers = {
            {"",      ZERO},
            {"0",     ZERO},
            {"",      ZERO},
            {"0",     ZERO},
            {"",      ZERO},
            {"1",     PLUS},
            {"1001",  PLUS},
            {"0",     ZERO},
            {"-1",    MINUS},
            {"-1001", MINUS},
            {"0",     ZERO},
            {"-1",    MINUS},
            {"-1001", MINUS},
            {"0",     ZERO},
            {"1",     PLUS},
            {"1001",  PLUS},
            {"0",     ZERO}
    };
    Number answer, number1, number2;
    Sign sign1, sign2;
    for (uint i = 0, n = numbers.size(); i < n; i++) {
        number1 = Number(numbers[i].first), number2 = Number(numbers[i].second);
        sign1 = number1.sign, sign2 = number2.sign;
        divide(&answer, &number1, &number2);
        EXPECT_EQ(answer.str(), answers[i].first);
        EXPECT_EQ(answer.sign, answers[i].second);
        EXPECT_EQ(number1.sign, sign1);
        EXPECT_EQ(number2.sign, sign2);
        answer.clear();
        number1.clear();
        number2.clear();
    }
}
