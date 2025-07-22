#include <iostream>
using namespace std;

int ac(int m, int n) {
    if (m == 0) {
        return n + 1;
    } else if (m == 1) {
        return n + 2;
    } else if (m == 2) {
        return 2 * n + 3;
    } else if (m == 3) {
        int result = 2;
        for (int i = 0; i <= n; i++) {
            result = 2 * result;
        }
        return result - 3;
    } 
}

int main() {
    int m, n;
    cout << "請輸入 m: ";
    cin >> m;
    cout << "請輸入 n: ";
    cin >> n;

    int result = ac(m, n);
   
    cout << "A(" << m << ", " << n << ") = " << result << endl;

    return 0;
} 
