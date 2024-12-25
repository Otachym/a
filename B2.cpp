#include <iostream>
#include <string>
#include <map>
#include <vector>
#include <cmath>
#include <stack>

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
        } else if (ch == '&' || ch == '|' || ch == '-') {
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

// Hàm tạo bảng chân trị
void generateTruthTable(const std::string& expression, const std::vector<char>& variables) {
    int numVariables = variables.size();
    int numRows = std::pow(2, numVariables);

    // In tiêu đề bảng
    for (char var : variables) {
        std::cout << var << " ";
    }
    std::cout << "| Result" << std::endl;

    // Duyệt qua tất cả các tổ hợp giá trị của các biến
    for (int i = 0; i < numRows; ++i) {
        std::map<char, bool> values;

        // Gán giá trị True/False cho từng biến
        for (int j = 0; j < numVariables; ++j) {
            values[variables[j]] = (i & (1 << (numVariables - j - 1))) != 0;
        }

        // In giá trị các biến
        for (char var : variables) {
            std::cout << (values[var] ? "T " : "F ");
        }

        // Tính giá trị biểu thức
        try {
            bool result = evaluateExpression(expression, values);
            std::cout << "| " << (result ? "T" : "F") << std::endl;
        } catch (const std::exception& ex) {
            std::cerr << "Error: " << ex.what() << std::endl;
            return;
        }
    }
}

int main() {
    std::string expression;
    std::cout << "Enter a logical expression: ";
    std::getline(std::cin, expression);

    int numVariables;
    std::cout << "Enter the number of variables: ";
    std::cin >> numVariables;

    std::vector<char> variables(numVariables);
    std::cout << "Enter the variables (e.g., A B C): ";
    for (int i = 0; i < numVariables; ++i) {
        std::cin >> variables[i];
    }

    generateTruthTable(expression, variables);

    return 0;
}
