#include <iostream>
#include <string>
#include <map>
#include <stack>
#include <stdexcept>

// Hàm tính giá trị của phép toán logic
bool applyOperator(bool a, bool b, char op) {
    switch (op) {
        case '^': return a && b; // AND
        case '|': return a || b; // OR
        case '-': return !a || b; // IMPLIES
        default: throw std::invalid_argument("Invalid operator");
    }
}

// Hàm tính giá trị logic của biểu thức
bool evaluateExpression(const std::string& expr, const std::map<char, bool>& values) {
    std::stack<bool> operands;
    std::stack<char> operators;

    for (char ch : expr) {
        if (isspace(ch)) continue;

        if (isalnum(ch)) {
            if (values.find(ch) == values.end()) {
                throw std::invalid_argument("Variable value not provided.");
            }
            operands.push(values.at(ch));
        } else if (ch == '!') {
            if (!operands.empty()) {
                bool top = operands.top();
                operands.pop();
                operands.push(!top);
            } else {
                throw std::invalid_argument("Invalid use of NOT operator.");
            }
        } else if (ch == '^' || ch == '|' || ch == '-') {
            operators.push(ch);
        }
    }

    while (!operators.empty() && operands.size() >= 2) {
        char op = operators.top();
        operators.pop();
        bool b = operands.top();
        operands.pop();
        bool a = operands.top();
        operands.pop();
        operands.push(applyOperator(a, b, op));
    }

    return operands.top();
}

int main() {
    std::string expression;
    std::cout << "Nhap bieu thuc logic: ";
    std::getline(std::cin, expression);

    std::map<char, bool> values;
    int numVariables;
    std::cout << "Nhap so luong cac bien: ";
    std::cin >> numVariables;

    for (int i = 0; i < numVariables; ++i) {
        char variable;
        bool value;
        std::cout << "Nhap cac bien va gia tri cua chung (1:True va 0:False): ";
        std::cin >> variable >> value;
        values[variable] = value;
    }

    try {
        bool result = evaluateExpression(expression, values);
        std::cout << "Ket qua: " << (result ? "True" : "False") << std::endl;
    } catch (const std::exception& ex) {
        std::cerr << "Error: " << ex.what() << std::endl;
        return 1;
    }

    return 0;
}
