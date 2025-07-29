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

