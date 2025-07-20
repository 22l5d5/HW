#include <iostream>
using namespace std;

int a(int m, int n) {
    if (m == 0) return n + 1;
    if (n == 0) return a(m - 1, 1);
    return a(m - 1, a(m, n - 1));
}

int main() {
    int m, n;
    cout << "請輸入 m: ";
    cin >> m;
    cout << "請輸入 n: ";
    cin >> n;
    try {
        cout << "A(" << m << ", " << n << ") 遞迴結果: " << a(m, n) << endl;
    } catch (const char* msg) {
        cout << msg << endl;
    }
    return 0;
}
