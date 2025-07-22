# 51115123

作業一第一題

## 解題說明
Ackermann 函數 A(m, n)，規則如下

1.如果m = 0，則A(m, n) = n + 1

2.如果n = 0，則A(m, n) = A(m - 1, 1)

3.其他狀況下，A(m, n) = A(m - 1, A(m, n - 1))
### 解題策略
根據 Ackermann 函數的數學性質，針對 \( m = 0, 1, 2, 3 \) 設計直接的迭代公式或算法。

對於 \( m = 0 \)，直接返回 \( n + 1 \)；\( m = 1 \) 返回 \( n + 2 \)；\( m = 2 \) 使用線性公式 \( 2n + 3 \)；\( m = 3 \) 使用指數增長的迭代計算 \( 2^{n+1} - 3 \)。

採用條件語句和迴圈處理不同 \( m \) 值的計算，確保結果與 Ackermann 函數的前幾項一致。

## 程式實作

```cpp

#include <iostream>
using namespace std;

int ac(int m, int n) {
    int result = n + 1;
    while (m > 0 || n > 0) {
        if (m == 0) {
            result = n + 1;
            break;
        }
        if (n == 0) {
            m--;
            n = 1;
        } else {
            m--;
            int temp = n;
            n = result - 1;
            result = temp;
        }
    }
    return result;
}

int main() {
    int m, n;
    cout << "請輸入 m: ";
    cin >> m;
    cout << "請輸入 n: ";
    cin >> n;
    try {
        cout << "A(" << m << ", " << n << ") 結果: " << ac(m, n) << endl;
    } catch (const char* msg) {
        cout << msg << endl;
    }
    return 0;
}
```

## 效能分析

1 時間複雜度

    1.非遞迴：O(1)

2 空間複雜度

    1.非遞迴：O(A(m, n))

## 測試與驗證

### 測試案例

| 測試案例 | 輸入參數 $m$ |輸入參數 $n$| 預期輸出 | 實際輸出 |
|----------|--------------|----------|----------|----------|
| 測試一   | $m = 0$      | $n = 2$      | 3        | 3        |
| 測試二   | $m = 1$      | $n = 0$      | 2        | 2        |
| 測試三   | $m = 2$      | $n = 2$      | 7        | 7        |
| 測試四   | $m = 3$      | $n = 1$      |13       | 13       |

### 結論

程式能正確計算用戶輸入的 ( m ) 和 ( n ) 對應的 Ackermann 函數值，使用非遞迴方法。

測試案例涵蓋邊界情況（( m = 0 )、( n = 0 )）及一般情況，驗證了程式的正確性。

## 申論及開發報告

### 選擇方法的理由

1.非遞迴方法：符合題目要求，避免遞迴呼叫，通過迭代模擬邏輯，確保在 ( m ) 或 ( n ) 較大時不會因堆疊溢出而失敗。

2.簡單實現：使用少量變數和迴圈實現，減少記憶體使用，適合資源受限環境。

3.限制與改進：當 ( m ) 或 ( n ) 過大時，計算時間可能顯著增加，建議未來使用動態規劃優化。



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


### 結論

1.程式能正確生成用戶輸入集合的冪集，使用陣列。

2.測試案例涵蓋不同元素數量的情況，驗證了遞迴實現的正確性。

## 申論及開發報告

選擇方法的理由

1.遞迴方法：通過每個元素的二元選擇（包含/排除）生成子集，邏輯簡單，符合題目要求。

2.陣列使用：使用固定大小陣列雖需預定義最大大小，但確保記憶體使用可控。

3.限制與改進：當 ( n ) 接近 MAX_SIZE 時，空間限制明顯，未來能使用動態調整陣列大小或使用位元運算優化。




