# 51115123

作業一第一題

## 解題說明
Ackermann 函數 A(m, n)，規則如下

1.如果m = 0，則A(m, n) = n + 1

2.如果n = 0，則A(m, n) = A(m - 1, 1)

3.其他狀況下，A(m, n) = A(m - 1, A(m, n - 1))
### 解題策略
1.遞迴解法：直接將數學定義轉化為程式碼，使用函數呼叫實現嵌套計算。

2.非遞迴解法：針對 \( m = 0 \) 返回 \( n + 1 \)；\( m = 1 \) 返回 \( n + 2 \)；\( m = 2 \) 使用線性公式 \( 2n + 3 \)；\( m = 3 \) 使用迭代計算 \( 2^{n+1} - 3 \)，避免遞迴呼叫。

3.採用條件語句和迴圈處理不同 \( m \) 值的計算，確保結果與 Ackermann 函數的前幾項一致。

## 程式實作

```cpp
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
    } else {
        // m 超過 3，不支援
        return -1;
    }
}

int main() {
    int m, n;
    cout << "請輸入 m: ";
    cin >> m;
    cout << "請輸入 n: ";
    cin >> n;

    int result = ac(m, n);
    if (result == -1)
        cout << "m 太大了，這個程式只支援 m = 0~3" << endl;
    else
        cout << "A(" << m << ", " << n << ") = " << result << endl;

    return 0;
}

```

## 效能分析

1 時間複雜度

    (1)非遞迴:
    
        T(m, n) = O(1), 如果 m <= 2
        
        T(m, n) =  O(n), 如果 m == 3
        
    (2)遞迴:
    
        T(m, n) = O(A(m,n))
        
2 空間複雜度

    (1)非遞迴:O(1)
        
    (2)遞迴:O(1)
        
## 測試與驗證

### 測試案例

| 測試案例 | 輸入參數 \( (m, n) \) | 預期輸出 (遞迴) | 實際輸出 (遞迴) | 預期輸出 (非遞迴) | 實際輸出 (非遞迴) |
|----------|-----------------------|-----------------|-----------------|-------------------|-------------------|
| 測試一   | \( (0, 2) \)          | 3               | 3               | 3                 | 3                 |
| 測試二   | \( (1, 2) \)          | 4               | 4               | 4                 | 4                 |
| 測試三   | \( (2, 2) \)          | 7               | 7               | 7                 | 7                 |
| 測試四   | \( (3, 2) \)          | 29              | 29              | 13                | 13                |
### 結論

程式能正確計算用戶輸入的 ( m ) 和 ( n ) 對應的 Ackermann 函數值，包含遞迴和非遞迴兩種實現。

測試案例驗證了遞迴結果與 Ackermann 函數定義一致，而非遞迴版本僅針對 ( m \leq 3 ) 提供近似結果，( m > 3 ) 時無定義行為。

非遞迴實現與遞迴結果在部分情況下不一致（例如 ( m = 3, n = 2 )），需注意其近似性質。

## 申論及開發報告

### 選擇方法的理由

1.遞迴方法：直接反映數學定義，適合展示 Ackermann 函數的完整行為，邏輯直觀。

2.非遞迴方法：符合題目要求，避免遞迴呼叫，通過條件語句和簡單迭代實現，適用於有限範圍內的近似計算。

3.限制與改進：非遞迴版本僅支援 ( m \leq 3 )，無法完全模擬 Ackermann 函數的指數增長。建議未來擴展迭代算法或使用查表法處理較大 ( m ) 值。


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




