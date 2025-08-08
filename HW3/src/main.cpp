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
        if (x.header == nullptr || x.header->link == x.header) {
            os << "0" << std::endl;
            return os;
        }
        bool first = true;
        Node* current = x.header->link;
        while (current != x.header) {
            if (current->coef == 0) {
                current = current->link;
                continue;
            }
            if (!first && current->coef > 0) os << " + ";
            if (current->exp == 0) {
                os << current->coef;
            } else if (current->exp == 1) {
                if (current->coef == 1) os << "x";
                else if (current->coef == -1) os << "-x";
                else os << current->coef << "x";
            } else if (current->exp > 0) {
                os << current->coef << "x^" << current->exp;
            } else { // 負指數
                os << current->coef << "/x^" << -current->exp;
            }
            first = false;
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

int main() {
    Polynomial p;
    std::cout << "輸入項數 (或直接輸入係數和指數直到 EOF):" << std::endl;
    std::cin >> p;
    std::cout << "多項式: " << p;
    Polynomial q;
    std::cin >> q;
    std::cout << "另一個多項式: " << q;
    Polynomial sum = p + q;
    std::cout << "加法結果: " << sum;
    Polynomial product = p * q;
    std::cout << "乘法結果: " << product;
    std::cout << "在 x = 2 時的評估值: " << p.Evaluate(2) << std::endl;
    return 0;
}
