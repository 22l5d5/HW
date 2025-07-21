#include <iostream>
using namespace std;

const int MAX_SIZE = 10; // 定義最大元素數量

void powerset_recursive(int set[], int n, int index, int current[], int currentSize, int result[][MAX_SIZE], int& resultCount) {
    if (index == n) {
        for (int i = 0; i < currentSize; i++) {
            result[resultCount][i] = current[i];
        }
        for (int i = currentSize; i < MAX_SIZE; i++) {
            result[resultCount][i] = 0; // 填充剩餘部分為 0
        }
        resultCount++;
        return;
    }
    // 排除當前元素
    powerset_recursive(set, n, index + 1, current, currentSize, result, resultCount);
    // 包含當前元素
    current[currentSize] = set[index];
    powerset_recursive(set, n, index + 1, current, currentSize + 1, result, resultCount);
}

void printPowerset(int result[][MAX_SIZE], int resultCount) {
    for (int i = 0; i < resultCount; i++) {
        cout << "{ ";
        bool first = true;
        for (int j = 0; j < MAX_SIZE && result[i][j] != 0; j++) {
            if (!first) cout << ", ";
            cout << result[i][j];
            first = false;
        }
        cout << " }" << endl;
    }
}

int main() {
    int n;
    cout << "請輸入集合元素數量: ";
    cin >> n;
    if (n > MAX_SIZE) {
        cout << "元素數量超過最大限制 " << MAX_SIZE << endl;
        return 1;
    }
    int set[MAX_SIZE];
    cout << "請輸入 " << n << " 個元素: ";
    for (int i = 0; i < n; i++) {
        cin >> set[i];
    }
    int current[MAX_SIZE] = {0};
    int result[MAX_SIZE * MAX_SIZE][MAX_SIZE] = {0}; // 假設最多 2^n 個子集
    int resultCount = 0;
    try {
        powerset_recursive(set, n, 0, current, 0, result, resultCount);
        printPowerset(result, resultCount);
    } catch (const char* msg) {
        cout << msg << endl;
    }
    return 0;
}
