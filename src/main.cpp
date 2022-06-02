//
// Created by adeshchoudhar on 13/12/21.
//

#include <cstring>

#include "operations.h"

void evaluateExpression(Number *, string &);

int main() {
    while (true) {
        cout << "> ";
        string expression;
        getline(cin, expression);
        if (!expression.empty()) {
            if (expression == "quit") {
                break;
            } else {
                Number answer;
                evaluateExpression(&answer, expression);
                if (answer.length != 0) {
                    cout << "= ";
                    printNumber(answer);
                } else {
                    // TODO: SyntaxError
                }
            }
        }
    }
    return 0;
}

void evaluateExpression(Number *answer, string &expression) {
    size_t idx = expression.find(' '), ridx = expression.rfind(' ');
    string n1 = expression.substr(0, idx);
    string op = expression.substr(idx + 1, 1);
    string n2 = expression.substr(ridx + 1);
    Number number1(n1);
    Number number2(n2);
    if (op == "+") {
        add(answer, number1, number2);
    } else if (op == "-") {
        subtract(answer, number1, number2);
    } else if (op == "*") {
        multiply(answer, number1, number2);
    } else if (op == "/") {
        divide(answer, number1, number2);
    }
}
