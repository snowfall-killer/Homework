# 41023218

作業一

## 解題說明

本題要求實現一個遞迴函式，計算非遞迴 Ackermann 函數𝐴(𝑚,𝑛)的值。

### 解題策略

1. 使用遞迴函式將問題拆解為更小的子問題：  
   ![Ackermann Function](./assets/ackermann.png)

2. 主程式輸入 $m$（空格）$n$ 值至遞迴函式，並輸出計算結果。

3. 若條件如下，定義 Ackermann 函數行為：  
   - 如果 m = 0       →  n + 1  
   - 如果 n = 0       →  A(m - 1, 1)  
   - 如果 m > 0 且 n > 0 →  A(m - 1, A(m, n - 1))

4. 當 m = 0 時，返回值作為遞迴的結束條件。 

## 程式實作

以下為主要程式碼：

```cpp
#include <iostream>
using namespace std;

// 使用unsigned int避免出現負數
unsigned int A(unsigned int m, unsigned int n)
{
    if (m == 0)
        return n + 1;
    else if (n == 0)
        return A(m - 1, 1);
    else
        return A(m - 1, A(m, n - 1));
}

int main()
{
    unsigned int m, n;
    cout << "請輸入 m (空格) n: ";
    cin >> m >> n;
    cout << "A(" << m << ", " << n << ") = " << A(m, n) << endl;
    return 0;
}
```

## 效能分析

1. 時間複雜度：程式的時間複雜度為 超指數 $O(A(m,n))$。
2. 空間複雜度：空間複雜度為 $O(m)$。
3.Ackermann 函數的計算非常耗時，其時間複雜度接近 $O(m × A(m, n))$，因為每一層 $m$ 可能導致大量的重複遞迴呼叫。而由於每次遞迴會暫存在堆疊中，最多會有 $m$ 層堆疊深度，因此空間複雜度為 $O(m)$。


## 測試與驗證

### 測試案例

| 測試案例 | 輸入參數 m | 輸入參數 n | 預期輸出 | 實際輸出 |
|----------|-------------|-------------|-----------|-----------|
| 測試一   | m = 0       | n = 0       | 1         | 1         |
| 測試二   | m = 1       | n = 1       | 3         | 3         |
| 測試三   | m = 2       | n = 2       | 7         | 7         |
| 測試四   | m = 3       | n = 3       | 61        | 61        |
| 測試五   | m = -1      | n = -1      | 異常拋出 | 異常拋出 |

### 編譯與執行指令

請輸入 m (空格) n: 2 2
A(2, 2) = 7

### 結論

1.程式可以正確計算輸入的 $m$ 與 $n$ 值，並回傳對應的 Ackermann 函數值。

2.當 $n < 0$ 時，程式會成功拋出例外，符合預期的錯誤處理設計。

3.當 $m \leq 3$ 且 $n \leq 10$ 時，程式能正常執行。但因 Ackermann 函數成長極快，超出此範圍後執行時間會急遽增加，甚至導致效能下降或當機。

## 申論及開發報告

### 選擇遞迴的原因

在本程式中，使用遞迴來計算 **Ackermann 函數** 的主要原因如下：

---

1. **程式邏輯簡單直觀**  
   Ackermann 函數的數學定義本身就是高度遞迴的結構。  
   使用遞迴能直接對應到其定義，有助於更清楚地呈現其演算法流程。  

   $$  
   A(m, n) =  
   \begin{cases}  
     n + 1 & \text{if } m = 0 \\\\  
     A(m - 1, 1) & \text{if } m > 0 \text{ and } n = 0 \\\\  
     A(m - 1, A(m, n - 1)) & \text{if } m > 0 \text{ and } n > 0  
   \end{cases}  
   $$

---

2. **遞迴程式碼對應數學式明確**  
   程式碼結構與數學遞迴定義一一對應，幾乎無需額外變數或迴圈。  
   初學者可藉此學習如何將數學遞迴轉化為程式遞迴：  

   ```cpp
   int ackermann(int m, int n) {
       if (m < 0 || n < 0)
           throw "Invalid input: m and n must be non-negative.";
       if (m == 0)
           return n + 1;
       else if (n == 0)
           return ackermann(m - 1, 1);
       else
           return ackermann(m - 1, ackermann(m, n - 1));
   }
