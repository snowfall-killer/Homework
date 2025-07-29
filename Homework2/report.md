# 41023218

作業二

## 解題說明

本題要求實現陣列函式，存取多項式的值。

### 解題策略

1. 使用 `Polynomial` 類別搭配動態陣列 (`Term* termArray`) 儲存非零係數與其對應指數，以節省空間並加速操作。

2. 利用重載運算子 `>>` 與 `<<` 提供友善的輸入與輸出介面，讓使用者能輕鬆輸入與顯示多項式。

3. 每次插入項時會先檢查指數是否已存在，若存在則合併係數；若係數為 0 則移除該項，維持非零項結構。

4. 當陣列容量不足時，會透過 `Resize()` 自動擴充陣列大小。

## 程式實作

```cpp
#include <iostream>

class Polynomial;  // 前向宣告

class Term {
    friend class Polynomial;
private:
    float coef;  // 係數 a_i
    int exp;     // 指數 e_i
};

class Polynomial {
private:
    Term* termArray;  // 儲存非零項的陣列
    int capacity;      // termArray 的容量
    int terms;         // 當前項數

    void Resize(int newCapacity) {
        Term* newArray = new Term[newCapacity];
        for (int i = 0; i < terms; ++i)
            newArray[i] = termArray[i];
        delete[] termArray;
        termArray = newArray;
        capacity = newCapacity;
    }

public:
    Polynomial(int cap = 10) {
        capacity = cap;
        terms = 0;
        termArray = new Term[capacity];
    }

    ~Polynomial() {
        delete[] termArray;
    }

    void AddTerm(float c, int e) {
        if (c == 0 || e < 0) return; 

        for (int i = 0; i < terms; ++i) {
            if (termArray[i].exp == e) {
                termArray[i].coef += c;
                if (termArray[i].coef == 0) {
                    for (int j = i; j < terms - 1; ++j)
                        termArray[j] = termArray[j + 1];
                    --terms;
                }
                return;
            }
        }

        if (terms == capacity)
            Resize(2 * capacity);

        termArray[terms].coef = c;
        termArray[terms].exp = e;
        ++terms;
    }

    // 2. 以下是運算子重載部分
    friend std::istream& operator>>(std::istream& in, Polynomial& poly);
    friend std::ostream& operator<<(std::ostream& out, const Polynomial& poly);
};

// 輸入運算子：輸入多項式的每一項
std::istream& operator>>(std::istream& in, Polynomial& poly) {
    int n;
    std::cout << "Enter number of terms: ";
    in >> n;

    for (int i = 0; i < n; ++i) {
        float coef;
        int exp;
        std::cout << "Enter coefficient and exponent (a e): ";
        in >> coef >> exp;
        poly.AddTerm(coef, exp);
    }
    return in;
}

// 輸出運算子：格式化輸出多項式
std::ostream& operator<<(std::ostream& out, const Polynomial& poly) {
    for (int i = 0; i < poly.terms; ++i) {
        if (i > 0 && poly.termArray[i].coef > 0)
            out << " + ";
        else if (i > 0 && poly.termArray[i].coef < 0)
            out << " - ";
        else if (i == 0 && poly.termArray[i].coef < 0)
            out << "-";

        float absCoef = std::abs(poly.termArray[i].coef);

        if (poly.termArray[i].exp == 0)
            out << absCoef;
        else if (poly.termArray[i].exp == 1)
            out << absCoef << "x";
        else
            out << absCoef << "x^" << poly.termArray[i].exp;
    }
    return out;
}

int main() {
    Polynomial p;
    std::cin >> p;

    std::cout << "You entered: " << p << std::endl;

    return 0;
}
```

## 測試與驗證

### 測試案例（Polynomial 輸入與輸出）

| 測試案例 | 輸入參數 terms | 輸入係數 ai, 指數 ei      | 預期輸出                 |
| ---- | ---------- | ------------------- | -------------------- |
| 測試一  | 1          | 3, 0                | 3                    |
| 測試二  | 2          | 3, 1；2, 0           | 3x + 2               |
| 測試三  | 3          | -1, 3；2, 2；1, 1     | -1x^3 + 2x^2 + 1x    |
| 測試四  | 4          | 3, 3；2, 2；1, 1；4, 0 | 3x^3 + 2x^2 + 1x + 4 |
| 測試五  | 2          | 1, -1；2, 0（應拒絕負指數）  | 僅顯示 2                |

### 編譯與執行範例

```
Enter number of terms: 4
Enter coefficient and exponent (a e): 3 3
Enter coefficient and exponent (a e): 2 2
Enter coefficient and exponent (a e): 1 1
Enter coefficient and exponent (a e): 4 0
You entered: 3x^3 + 2x^2 + 1x + 4
```

## 效能分析

1. 時間複雜度：每次插入項需 $O(n)$ 時間尋找對應指數合併或插入，總體插入 n 項為 O(n²)。

2. 空間複雜度：空間依賴 termArray 的大小，為 $O(n)$ 。若超過容量，`Resize()` 將花費 O(n) 進行複製，但整體 amortized 為 O(n)。

## 申論及開發報告

### 設計選擇

* 使用動態記憶體 (`new[]` 和 `Resize`) 方便彈性擴展多項式大小。
* 指數與係數以成對方式儲存於 `Term` 類別中，使資料結構清楚且易於維護。
* 以 OOP 思維封裝多項式行為，並友善介面輸入輸出。

### 輸入合法性與彈性

* 若使用者輸入係數為 0 或指數 < 0，系統將忽略該項，避免無效資料進入多項式。
* 支援常數項 (exp = 0)，讓表達式完整。
