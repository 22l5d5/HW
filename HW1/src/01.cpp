#include <iostream>
using namespace std;

// 遞迴版本的阿克曼函數
int ack(int m, int n) {
    if (m < 0 || n < 0) throw "輸入值不能為負數";
    if (m == 0) return n + 1;
    if (n == 0) return ack(m - 1, 1);
    return ack(m - 1, ack(m, n - 1));
}

// 非遞迴版本的阿克曼函數
int ac(int m, int n) {
    if (m < 0 || n < 0) throw "輸入值不能為負數";
    if (m == 0) return n + 1;
    else if (m == 1) return n + 2;
    else if (m == 2) return 2 * n + 3;
    else if (m == 3) {
        int result = 2;
        for (int i = 0; i <= n; i++) {
            result *= 2;
        }
        return result - 3;
    }
    throw "m > 3 不支援非遞迴計算";
}

int main() {
    int m, n;
    

    cout << "請輸入 m: ";
    if (!(cin >> m) || m < 0) {
        cout << "無效的 m 值，必須為非負整數" << endl;
        return 1;
    }
    cout << "請輸入 n: ";
    if (!(cin >> n) || n < 0) {
        cout << "無效的 n 值，必須為非負整數" << endl;
        return 1;
    }

    // 限制輸入範圍以避免堆疊溢出
    if (m > 3 || n > 10) {
        cout << "輸入值過大，可能導致堆疊溢出" << endl;
        return 1;
    }

    try {
        cout << "A(" << m << ", " << n << ") 遞迴結果: " << ack(m, n) << endl;
        cout << "A(" << m << ", " << n << ") 非遞迴結果: " << ac(m, n) << endl;
    } catch (const char* msg) {
        cout << "錯誤: " << msg << endl;
    }

    return 0;
}
