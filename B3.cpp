#include <iostream>
#include <vector>
#include <functional>
#include <string>
#include <algorithm>
#include <stdexcept>

// Hàm kiểm tra tính đúng/sai của một công thức logic vị từ
bool evaluateFormula(const std::string& formula, const std::vector<int>& domain,
                     const std::function<bool(int)>& P, const std::function<bool(int)>& Q) {
    if (formula == "forall x (P(x) -> Q(x)) and exists y (P(y))") {
        // Kiểm tra forall x (P(x) -> Q(x))
        for (int x : domain) {
            if (P(x) && !Q(x)) {
                return false; // Có một giá trị không thỏa mãn P(x) -> Q(x)
            }
        }

        // Kiểm tra exists y (P(y))
        for (int y : domain) {
            if (P(y)) {
                return true; // Tồn tại ít nhất một giá trị thỏa mãn P(y)
            }
        }

        return false; // Nếu không tìm thấy y nào thỏa mãn P(y)
    }

    throw std::invalid_argument("Invalid formula. Please use 'forall x (P(x) -> Q(x)) and exists y (P(y))'.");
}

int main() {
    // Miền giá trị (domain)
    std::vector<int> domain = {1, 2, 3}; // Miền giá trị các biến

    // Định nghĩa các hàm predicate P(x) và Q(x)
    std::function<bool(int)> P = [](int x) { return x > 1; };       // Ví dụ: P(x) = x > 1
    std::function<bool(int)> Q = [](int x) { return x % 2 == 0; };  // Ví dụ: Q(x) = x % 2 == 0

    // Nhập công thức từ người dùng
    std::string formula;
    std::cout << "Nhap cong thuc (VD: forall x (P(x) -> Q(x)) and exists y (P(y))): ";
    std::getline(std::cin, formula);

    try {
        // Đánh giá công thức
        bool result = evaluateFormula(formula, domain, P, Q);
        std::cout << "Ket qua: " << (result ? "TRUE" : "FALSE") << "." << std::endl;
    } catch (const std::exception& ex) {
        std::cerr << "LOI: " << ex.what() << std::endl;
    }

    return 0;
}
