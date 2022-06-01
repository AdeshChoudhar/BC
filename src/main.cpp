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
                    printNumber(answer);
                } else {
                    // TODO
                    cout << "EvaluationError: Message" << endl;
                }
            }
        }
    }
    return 0;
}

void evaluateExpression(Number *answer, string &expression) {
    size_t idx = expression.find(' ');
    string n1 = expression.substr(0, idx);
    string n2 = expression.substr(idx + 1);
    Number number1(n1);
    Number number2(n2);
    add(answer, number1, number2);
}
