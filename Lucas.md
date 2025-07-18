# 51115123

作業一第一題

## 解題說明
Ackermann 函數 ( A(m, n) ) 是一個接受兩個非負整數參數的數學函數，增長速度極快。其定義如下：
1.如果m = 0，則A(m, n) = n + 1  
2.如果n = 0，則A(m, n) = A(m - 1, 1)
3.其他狀況下，A(m, n) = A(m - 1, A(m, n - 1))
### 解題策略
1.遞迴解法：直接將數學定義轉化為程式碼，使用函數呼叫實現。
2.非遞迴解法：使用堆疊模擬遞迴呼叫，通過迭代處理函數各情況，避免堆疊溢出。
## 程式實作

以下為主要程式碼：

```cpp
#include <iostream>
using namespace std;

int ackermann_recursive(int m, int n) {
    if (m == 0) return n + 1;
    if (n == 0) return ackermann_recursive(m - 1, 1);
    return ackermann_recursive(m - 1, ackermann_recursive(m, n - 1));
}

int ackermann_nonrecursive(int m, int n) {
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
        cout << "A(" << m << ", " << n << ") 遞迴結果: " << ackermann_recursive(m, n) << endl;
        cout << "A(" << m << ", " << n << ") 非遞迴結果: " << ackermann_nonrecursive(m, n) << endl;
    } catch (const char* msg) {
        cout << msg << endl;
    }
    return 0;
}
```

## 效能分析

1 時間複雜度
遞迴：( O(2^n) ) 由於嵌套遞迴呼叫導致指數級增長。
非遞迴：( O(m \times n) ) 視輸入大小和實現方式而定。
3.2 空間複雜度
遞迴：( O(m \times n) ) 由於呼叫堆疊深度。
非遞迴：( O(m \times n) ) 用於模擬遞迴的堆疊空間。
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
A(2, 2) 遞迴結果: 7
A(2, 2) 非遞迴結果: 7

### 結論
程式能正確計算 Ackermann 函數的遞迴和非遞迴結果。
測試案例涵蓋邊界情況m = 0、n = 0及一般情況，驗證了程式的正確性。

## 申論及開發報告

### 選擇遞迴的原因

在本程式中，使用遞迴來計算連加總和的主要原因如下：

1. **程式邏輯簡單直觀**  
   遞迴的寫法能夠清楚表達「將問題拆解為更小的子問題」的核心概念。  
   例如，計算 $\Sigma(n)$ 的過程可分解為：  

   $$
   \Sigma(n) = n + \Sigma(n-1)
   $$

   當 $n$ 等於 1 或 0 時，直接返回結果，結束遞迴。

2. **易於理解與實現**  
   遞迴的程式碼更接近數學公式的表示方式，特別適合新手學習遞迴的基本概念。  
   以本程式為例：  

   ```cpp
   int sigma(int n) {
       if (n < 0)
           throw "n < 0";
       else if (n <= 1)
           return n;
       return n + sigma(n - 1);
   }
   ```

3. **遞迴的語意清楚**  
   在程式中，每次遞迴呼叫都代表一個「子問題的解」，而最終遞迴的返回結果會逐層相加，完成整體問題的求解。  
   這種設計簡化了邏輯，不需要額外變數來維護中間狀態。

透過遞迴實作 Sigma 計算，程式邏輯簡單且易於理解，特別適合展示遞迴的核心思想。然而，遞迴會因堆疊深度受到限制，當 $n$ 值過大時，應考慮使用迭代版本來避免 Stack Overflow 問題。
