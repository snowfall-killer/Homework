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