// Beginner 114 B.cpp
#include <iostream>
#include <cmath>
using namespace std;
string str;
int getNum(string part)
{
    int bit = 100, ans = 0;
    for (int i = 0; i < part.length(); i++)
        ans += (part[i] - '0') * bit, bit /= 10;
    return ans;
}
int main()
{
    cin >> str;
    int ans = 2e9;
    for (int i = str.length() - 1; i >= 2; i--)
        ans = min(ans, abs(getNum(str.substr(i - 2, 3)) - 753));
    cout << ans;
    return 0;
}