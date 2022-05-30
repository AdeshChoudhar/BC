//
// Created by adeshchoudhar on 13/12/21.
//

#include "functions.h"

int main(int argc, char **argv) {
    if (argc > 1) {
        cout << "UsageError: ./BC" << endl;
        exit(1);
    }
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
