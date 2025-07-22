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
