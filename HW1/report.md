# 51115123

作業一第一題

## 解題說明
Ackermann 函數 A(m, n)，規則如下

1.如果m = 0，則A(m, n) = n + 1

2.如果n = 0，則A(m, n) = A(m - 1, 1)

3.其他狀況下，A(m, n) = A(m - 1, A(m, n - 1))
### 解題策略
1.遞迴解法：直接將數學定義轉化為程式碼，使用函數呼叫實現。


## 程式實作

```cpp

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

```

## 效能分析

1 時間複雜度

    1.遞迴：O(1)

2 空間複雜度

    1.遞迴：O(A(m, n))

## 測試與驗證

### 測試案例

| 測試案例 | 輸入參數 $m$ |輸入參數 $n$| 預期輸出 | 實際輸出 |
|----------|--------------|----------|----------|----------|
| 測試一   | $m = 0$      | $n = 2$      | 3        | 3        |
| 測試二   | $m = 1$      | $n = 0$      | 2        | 2        |
| 測試三   | $m = 2$      | $n = 2$      | 7        | 7        |
| 測試四   | $m = 3$      | $n = 1$      |13       | 13       |


### 編譯與執行指令
$ g++ -std=c++17 -o ackermann ackermann.cpp

$ ./ackermann

請輸入 m: 2

請輸入 n: 2

A(2, 2) 遞迴結果: 7


### 結論

程式能正確計算 Ackermann 函數的遞迴結果。

測試案例涵蓋邊界情況m = 0、n = 0及一般情況，驗證了程式的正確性。

## 申論及開發報告

### 選擇遞迴的原因

選擇方法的理由

1.遞迴方法：直接反映數學定義，邏輯簡單直觀，適合展示遞迴概念。例如，A(m, n) = A(m - 1, A(m, n - 1))清楚表達子問題的分解，易於理解。

2.限制與改進：遞迴版本在 ( m ) 或 ( n ) 過大時可能失敗，建議未來使用尾遞迴優化或迭代版本。



作業一第二題

## 解題說明
若 ( S ) 為包含 ( n ) 個元素的集合，則 ( S ) 的冪集是 ( S ) 所有可能子集的集合。例如，若 ( S = {a, b, c} )，則冪集為 ( {{}, {a}, {b}, {c}, {a, b}, {a, c}, {b, c}, {a, b, c}} )。任務是撰寫一個遞迴函數計算冪集。
### 解題策略
1.使用遞迴方法，通過考慮每個元素的包含或排除構建冪集。

2.使用固定大小的陣列儲存集合和子集，基於二進制表示法生成所有可能的組合。

## 程式實作

```cpp
#include <iostream>
using namespace std;

const int MAX_SIZE = 10; 

void powerset_recursive(int set[], int n, int index, int current[], int currentSize, int result[][MAX_SIZE], int& resultCount) {
    if (index == n) {
        for (int i = 0; i < currentSize; i++) {
            result[resultCount][i] = current[i];
        }
        for (int i = currentSize; i < MAX_SIZE; i++) {
            result[resultCount][i] = 0; 
        }
        resultCount++;
        return;
    }
    
    powerset_recursive(set, n, index + 1, current, currentSize, result, resultCount);
    
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
    int result[MAX_SIZE * MAX_SIZE][MAX_SIZE] = {0};
    int resultCount = 0;
    try {
        powerset_recursive(set, n, 0, current, 0, result, resultCount);
        printPowerset(result, resultCount);
    } catch (const char* msg) {
        cout << msg << endl;
    }
    return 0;
}
```

## 效能分析

1 時間複雜度

    1.時間複雜度：O(2^n)

2 空間複雜度

    1.空間複雜度：O(n \times 2^n)

## 測試與驗證

### 測試案例

| 測試案例 | 輸入參數 \( S \)   | 預期輸出                                   | 實際輸出                                   |
|----------|--------------------|--------------------------------------------|--------------------------------------------|
| 測試一   | \( \{1\} \)        | \( \{\{\}, \{1\}\} \)                      | \( \{\{\}, \{1\}\} \)                      |
| 測試二   | \( \{1, 2\} \)     | \( \{\{\}, \{1\}, \{2\}, \{1, 2\}\} \)     | \( \{\{\}, \{1\}, \{2\}, \{1, 2\}\} \)     |
| 測試三   | \( \{1, 2, 3\} \)  | \( \{\{\}, \{1\}, \{2\}, \{3\}, \{1, 2\}, \{1, 3\}, \{2, 3\}, \{1, 2, 3\}\} \) | \( \{\{\}, \{1\}, \{2\}, \{3\}, \{1, 2\}, \{1, 3\}, \{2, 3\}, \{1, 2, 3\}\} \) |


### 編譯與執行指令
$ g++ -std=c++17 -o powerset powerset.cpp

$ ./powerset

請輸入集合元素數量: 3

請輸入 3 個元素: 1 2 3
{ }

{ 1 }

{ 2 }

{ 1 2 }

{ 3 }

{ 1 3 }

{ 2 3 }

{ 1 2 3 }

### 結論

1.程式能正確生成用戶輸入集合的冪集，使用陣列。

2.測試案例涵蓋不同元素數量的情況，驗證了遞迴實現的正確性。

## 申論及開發報告

選擇方法的理由

1.遞迴方法：通過每個元素的二元選擇（包含/排除）生成子集，邏輯簡單，符合題目要求。

2.陣列使用：使用固定大小陣列滿足不使用 vector 的限制，雖需預定義最大大小，但確保記憶體使用可控。

3.限制與改進：當 ( n ) 接近 MAX_SIZE 時，空間限制明顯，建議未來動態調整陣列大小或使用位元運算優化。




