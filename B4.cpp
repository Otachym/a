#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

// Hàm kiểm tra xem một mệnh đề có tồn tại trong tập hợp không
bool contains(const std::vector<std::string>& clauses, const std::string& clause) {
    return std::find(clauses.begin(), clauses.end(), clause) != clauses.end();
}

// Hàm phủ định một mệnh đề
std::string negate(const std::string& clause) {
    if (clause[0] == '!')
        return clause.substr(1); // Bỏ '!' nếu đã phủ định
    else
        return "!" + clause; // Thêm '!' để phủ định
}

// Hàm thực hiện chứng minh bằng phương pháp dẫn chứng phản chứng
bool resolution(std::vector<std::string> premises, const std::string& conclusion) {
    premises.push_back(negate(conclusion)); // Thêm phủ định của kết luận vào tập mệnh đề
    std::vector<std::string> new_clauses;

    while (true) {
        for (size_t i = 0; i < premises.size(); ++i) {
            for (size_t j = i + 1; j < premises.size(); ++j) {
                // Nếu hai mệnh đề là phủ định của nhau
                if (negate(premises[i]) == premises[j]) {
                    return true; // Mâu thuẫn, kết luận đúng
                }
                // Hợp hai mệnh đề nếu có thể
                std::string resolvent = premises[i] + " ∨ " + premises[j];
                if (!contains(new_clauses, resolvent)) {
                    new_clauses.push_back(resolvent);
                }
            }
        }

        // Nếu không tìm thấy mâu thuẫn và không có mệnh đề mới
        if (new_clauses.empty()) {
            return false; // Kết luận sai
        }

        // Thêm mệnh đề mới vào tập mệnh đề
        for (const auto& clause : new_clauses) {
            if (!contains(premises, clause)) {
                premises.push_back(clause);
            }
        }
        new_clauses.clear();
    }
}

int main() {
    std::vector<std::string> premises = {"P→Q", "Q→R"}; // Tập mệnh đề
    std::string conclusion = "P→R"; // Kết luận

    // Kiểm tra kết quả chứng minh
    if (resolution(premises, conclusion)) {
        std::cout << "Kết luận ĐÚNG.\n";
    } else {
        std::cout << "Kết luận SAI.\n";
    }

    return 0;
}
