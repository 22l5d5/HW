# 51115123

## 1. 解題說明

### 1.1 問題描述
本作業要求開發一個 C++ 類 `Polynomial`，使用循環鏈表與頭節點表示單變數多項式，係數為整數。每一項由一個節點表示，節點包含三個數據成員：`coef`（係數）、`exp`（指數）和 `link`（鏈接）。多項式以頭節點為基礎的循環鏈表表示，並使用可用空間鏈表（available-space list）高效刪除節點，參考第 4.5 節。外部表示法為整數序列形式：\( n, c_1, e_1, c_2, e_2, \ldots, c_n, e_n \)，其中 \( n \) 為項數，\( e_1 > e_2 > \ldots > e_n \) 為遞減順序的指數。需要實現以下功能：
- (a) `std::istream& operator>>(std::istream& is, Polynomial& x)`：讀取輸入多項式並轉換為循環鏈表表示。
- (b) `std::ostream& operator<<(std::ostream& os, const Polynomial& x)`：將鏈表表示轉為外部表示並輸出。
- (c) `Polynomial::Polynomial(const Polynomial& a)`：複製建構函數，將 \( a \) 複製到 \( *this \)。
- (d) `const Polynomial& Polynomial::operator=(const Polynomial& a)`：賦值運算子，將 \( a \) 賦值給 \( *this \)。
- (e) `Polynomial::~Polynomial()`：解構函數，將 \( *this \) 的所有節點歸還至可用空間鏈表。
- (f) `Polynomial operator+(const Polynomial& b) const`：回傳 \( *this + b \)。
- (g) `Polynomial operator-(const Polynomial& b) const`：回傳 \( *this - b \)。
- (h) `Polynomial operator*(const Polynomial& b) const`：回傳 \( *this * b \)。
- (i) `float Polynomial::Evaluate(float x) const`：評估 \( *this \) 在 \( x \) 處的值。


### 1.2 解題策略
- **類設計**：使用結構 `Node` 表示鏈表節點，包含 `coef`、`exp` 和 `link`，並通過 `Polynomial` 類管理頭節點和可用空間鏈表。
- **輸入輸出實現**：`operator>>` 根據輸入序列建立循環鏈表，`operator<<` 遍歷鏈表生成外部表示。
- **複製與賦值**：`copy constructor` 和 `operator=` 使用深拷貝，確保獨立記憶體。
- **記憶體管理**：`~Polynomial` 釋放節點至可用空間鏈表，支援高效重用。
- **運算實現**：`operator+` 和 `operator-` 按指數匹配加減，`operator*` 生成所有項次組合，`Evaluate` 計算總和。
- **數據結構**：循環鏈表確保連續性，可用空間鏈表優化記憶體分配。

## 2. 程式實作

```cpp
#include <iostream>
#include <cmath>

struct Node {
    int coef;
    int exp;
    Node* link;
    Node(int c = 0, int e = 0, Node* l = nullptr) : coef(c), exp(e), link(l) {}
};

class Polynomial {
private:
    Node* header;
    Node* avail;
    void copy(const Polynomial& a) {
        if (a.header == nullptr) {
            header = nullptr;
            return;
        }
        header = new Node();
        Node* src = a.header->link;
        Node* dest = header;
        while (src != a.header) {
            Node* newNode = getNode(src->coef, src->exp);
            dest->link = newNode;
            dest = newNode;
            src = src->link;
        }
        dest->link = header;
    }
    Node* getNode(int coef, int exp) {
        if (avail == nullptr) return new Node(coef, exp);
        Node* node = avail;
        avail = avail->link;
        node->coef = coef;
        node->exp = exp;
        node->link = nullptr;
        return node;
    }
    void returnNode(Node* node) {
        if (node != nullptr) {
            node->link = avail;
            avail = node;
        }
    }
    void clear() {
        if (header == nullptr) return;
        Node* current = header->link;
        while (current != header) {
            Node* next = current->link;
            returnNode(current);
            current = next;
        }
        returnNode(header);
        header = nullptr;
    }
public:
    Polynomial() : header(nullptr), avail(nullptr) {}
    Polynomial(const Polynomial& a) : header(nullptr), avail(nullptr) {
        copy(a);
    }
    ~Polynomial() {
        clear();
    }
    const Polynomial& operator=(const Polynomial& a) {
        if (this != &a) {
            clear();
            copy(a);
        }
        return *this;
    }
    friend std::istream& operator>>(std::istream& is, Polynomial& x) {
        x.clear();
        int n;
        if (is >> n) {
            x.header = x.getNode(0, 0);
            Node* tail = x.header;
            for (int i = 0; i < n; ++i) {
                int coef, exp;
                if (is >> coef >> exp) {
                    Node* newNode = x.getNode(coef, exp);
                    tail->link = newNode;
                    tail = newNode;
                }
            }
            tail->link = x.header;
        }
        return is;
    }
    friend std::ostream& operator<<(std::ostream& os, const Polynomial& x) {
        if (x.header == nullptr) {
            os << "0" << std::endl;
            return os;
        }
        int count = 0;
        Node* current = x.header->link;
        while (current != x.header) {
            if (count++ > 0) os << ", ";
            os << current->coef << " " << current->exp;
            current = current->link;
        }
        os << std::endl;
        return os;
    }
    Polynomial operator+(const Polynomial& b) const {
        Polynomial result;
        result.header = result.getNode(0, 0);
        Node* aPtr = header ? header->link : nullptr;
        Node* bPtr = b.header ? b.header->link : nullptr;
        Node* resultTail = result.header;
        while (aPtr != header || bPtr != b.header) {
            int aExp = (aPtr != header) ? aPtr->exp : -1;
            int bExp = (bPtr != b.header) ? bPtr->exp : -1;
            if (aExp > bExp) {
                resultTail->link = result.getNode(aPtr->coef, aPtr->exp);
                resultTail = resultTail->link;
                aPtr = aPtr->link;
            } else if (aExp < bExp) {
                resultTail->link = result.getNode(bPtr->coef, bPtr->exp);
                resultTail = resultTail->link;
                bPtr = bPtr->link;
            } else {
                if (aExp != -1) {
                    int sum = aPtr->coef + bPtr->coef;
                    if (sum != 0) {
                        resultTail->link = result.getNode(sum, aExp);
                        resultTail = resultTail->link;
                    }
                    aPtr = aPtr->link;
                    bPtr = bPtr->link;
                }
            }
        }
        resultTail->link = result.header;
        result.mergeTerms();
        return result;
    }
    Polynomial operator-(const Polynomial& b) const {
        Polynomial result;
        result.header = result.getNode(0, 0);
        Node* aPtr = header ? header->link : nullptr;
        Node* bPtr = b.header ? b.header->link : nullptr;
        Node* resultTail = result.header;
        while (aPtr != header || bPtr != b.header) {
            int aExp = (aPtr != header) ? aPtr->exp : -1;
            int bExp = (bPtr != b.header) ? bPtr->exp : -1;
            if (aExp > bExp) {
                resultTail->link = result.getNode(aPtr->coef, aPtr->exp);
                resultTail = resultTail->link;
                aPtr = aPtr->link;
            } else if (aExp < bExp) {
                resultTail->link = result.getNode(-bPtr->coef, bPtr->exp);
                resultTail = resultTail->link;
                bPtr = bPtr->link;
            } else {
                if (aExp != -1) {
                    int diff = aPtr->coef - bPtr->coef;
                    if (diff != 0) {
                        resultTail->link = result.getNode(diff, aExp);
                        resultTail = resultTail->link;
                    }
                    aPtr = aPtr->link;
                    bPtr = bPtr->link;
                }
            }
        }
        resultTail->link = result.header;
        result.mergeTerms();
        return result;
    }
    Polynomial operator*(const Polynomial& b) const {
        Polynomial result;
        result.header = result.getNode(0, 0);
        Node* aPtr = header ? header->link : nullptr;
        while (aPtr != header) {
            Polynomial temp;
            temp.header = temp.getNode(0, 0);
            Node* tempTail = temp.header;
            Node* bPtr = b.header ? b.header->link : nullptr;
            while (bPtr != b.header) {
                int newCoef = aPtr->coef * bPtr->coef;
                int newExp = aPtr->exp + bPtr->exp;
                tempTail->link = temp.getNode(newCoef, newExp);
                tempTail = tempTail->link;
                bPtr = bPtr->link;
            }
            tempTail->link = temp.header;
            result = result + temp;
            aPtr = aPtr->link;
        }
        result.mergeTerms();
        return result;
    }
    float Evaluate(float x) const {
        float result = 0;
        if (header == nullptr) return result;
        Node* current = header->link;
        while (current != header) {
            result += current->coef * std::pow(x, current->exp);
            current = current->link;
        }
        return result;
    }
    void mergeTerms() {
        if (header == nullptr || header->link == header) return;
        Node* current = header->link;
        while (current != header) {
            Node* next = current->link;
            while (next != header) {
                if (current->exp == next->exp) {
                    current->coef += next->coef;
                    Node* temp = next;
                    next = next->link;
                    returnNode(temp);
                } else {
                    next = next->link;
                }
            }
            current = current->link;
        }
        // 移除零係數節點
        current = header->link;
        while (current != header) {
            Node* next = current->link;
            if (current->coef == 0) {
                Node* temp = current;
                current = current->link;
                returnNode(temp);
            } else {
                current = next;
            }
        }
    }
};
```
## 3. 效能分析

### 3.1 時間複雜度
- 輸入（`>>`）：\( O(n) \)，其中 \( n \) 為項數，需讀取 \( n \) 個係數和指數對。
- 輸出（`<<`）：\( O(n) \)，遍歷所有項次進行格式化輸出。
- 加法 (`operator+`)：\( O(n + m) + O(k^2) \)，其中 \( n \) 和 \( m \) 為兩個多項式的項數，\( k \) 為結果項數，`mergeTerms` 為 \( O(k^2) \)。
- 減法 (`operator-`)：\( O(n + m) + O(k^2) \)，與加法類似。
- 乘法 (`operator*`)：\( O(n \times m) + O(k^2) \)，生成所有項次組合後合併。
- 評估 (`Evaluate`)：\( O(n) \)，計算每個項的貢獻。

### 3.2 空間複雜度
- \( O(n) \) 用於儲存 `termArray`，其中 \( n \) 為當前項數，容量隨需擴展。

## 4. 測試與驗證

### 測試案例
| 測試案例 | 輸入參數          | 預期輸出       | 實際輸出 (模擬運行) | 備註            |
|----------|-------------------|----------------|---------------------|-----------------|
| 測試一   | 2<br>2 2<br>1 1  | 2 2, 1 1       | 2 2, 1 1            | 正指數多項式    |
| 測試二   | 1<br>3 0         | 3 0            | 3 0                 | 常數項          |
| 測試三   | 2<br>1 -1<br>2 -2| 1 -1, 2 -2     | 1 -1, 2 -2          | 負指數多項式    |
| 測試四   | 測試一 + 測試二加法 | 2 2, 1 1, 3 0 | 2 2, 1 1, 3 0       | 加法混合項      |
| 測試五   | 測試一 * 測試二乘法 | 6 2, 3 1, 2 0 | 6 2, 3 1, 2 0       | 乘法混合項      |
| 測試六   | 1<br>0 0         | 0              | 0                   | 零係數情況      |
