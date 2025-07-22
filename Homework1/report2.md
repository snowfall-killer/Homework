# 41023218

作業一

## 解題說明

本題要求實現一個遞迴函式，計算冪集PowerSet (S)，如果 $S = (a,b,c)$ 。

### 解題策略

1. 冪集樹狀圖：  
()
├── 不選 a → ()
│   ├── 不選 b → ()
│   │   ├── 不選 c → ()
│   │   └── 選 c   → (c)
│   └── 選 b   → (b)
│       ├── 不選 c → (b)
│       └── 選 c   → (b, c)
└── 選 a   → (a)
    ├── 不選 b → (a)
    │   ├── 不選 c → (a)
    │   └── 選 c   → (a, c)
    └── 選 b   → (a, b)
        ├── 不選 c → (a, b)
        └── 選 c   → (a, b, c)

2. 計算子集合個數 $2^n$ ，$n^3 = 8$

3. push_back() 和 pop_back() 分別對應到資料結構「堆疊（stack）」中的操作。

## 程式實作

以下為主要程式碼：

```cpp
#include <iostream>
#include <vector>
#include <string>

using namespace std;

void generatePowerSet(const vector<string>& set, vector<string>& current, int index) {
    if (index == set.size()) {
        cout << "(";
        for (size_t i = 0; i < current.size(); ++i) {
            cout << current[i];
            if (i != current.size() - 1) cout << ",";
        }
        cout << ")" << endl;
        return;
    }

    generatePowerSet(set, current, index + 1);       // 往下遞迴跳過
    current.push_back(set[index]);                   // 加入這個元素
    generatePowerSet(set, current, index + 1);
    current.pop_back();                              // 移除剛剛加的那個元素，回到前一層狀態
}

int main() {
    vector<string> S = {"a", "b", "c"};
    vector<string> current; // 宣告一個空的current用來暫時存放「目前這條路徑中選到的元素（子集）」
    generatePowerSet(S, current, 0); // 遞迴函數(原始集合, 空的暫存子集, 起始index)
    return 0;
}
```

## 效能分析

1. 時間複雜度：程式的時間複雜度為 $O(2^n × n)$。
    子集總數：$2^n$
    每次輸出子集的花費：$O(n)$
2. 空間複雜度：空間複雜度為 $O(n)$。


## 測試與驗證

### 測試案例

| 測試案例 | 輸入集合 S         | 元素數 n | 預期子集合數量 (2ⁿ) | 實際子集合數量 |
| ---- | -------------- | ----- | ------------ | ------- |
| 測試一  | `{}`           | 0     | 1            | 1       |
| 測試二  | `{a}`          | 1     | 2            | 2       |
| 測試三  | `{a, b}`       | 2     | 4            | 4       |
| 測試四  | `{a, b, c}`    | 3     | 8            | 8       |
| 測試五  | `{a, b, c, d}` | 4     | 16           | 16      |

### 編譯與執行指令

Powerset of S = {a, b, c}:
()
(c)
(b)
(b,c)
(a)
(a,c)
(a,b)
(a,b,c)

### 結論

1.程式可以正確計算輸入集合 S ，並回傳對應實際子集合PowerSet。

## 申論及開發報告

### 選擇遞迴的原因

在本程式中，使用遞迴來計算集合的冪集（powerset）的主要原因如下：

---

### 程式邏輯簡單直觀

遞迴的寫法能夠清楚表達「將問題拆解為更小的子問題」的核心概念。

舉例來說，對於集合 S 中的每個元素，我們可以選擇「包含」或「不包含」它，這剛好對應到二元決策的樹狀結構。

冪集產生的邏輯可以遞迴地定義為：
每次呼叫都負責決定一個元素是否加入子集合中。

---

###  程式碼語意清晰，接近數學定義

遞迴的語法結構與數學中對冪集的定義非常接近，能直觀地展現冪集的生成過程。

```cpp
void generatePowerSet(const vector<string>& set, vector<string>& current, int index) {
    if (index == set.size()) {
        // 印出目前子集
        return;
    }

    generatePowerSet(set, current, index + 1);       // 不選
    current.push_back(set[index]);                   // 選
    generatePowerSet(set, current, index + 1);       // 選的情況
    current.pop_back();                              // 回溯
}


