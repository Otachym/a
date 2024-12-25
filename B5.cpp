#include <iostream>
using namespace std;

class KiemTra {
    int x;
public:
    KiemTra() : x(0) {} // Hàm tạo không tham số
    KiemTra(int x) { KiemTra::x = x; } // Hàm tạo có tham số
    void HienThi() { cout << x << " "; } // Hàm hiển thị
};

int main() {
    KiemTra a, b(10); // Khởi tạo a với x=0, b với x=10
    b.HienThi(); // In ra giá trị x của b
    a.HienThi(); // In ra giá trị x của a
    return 0;
}
