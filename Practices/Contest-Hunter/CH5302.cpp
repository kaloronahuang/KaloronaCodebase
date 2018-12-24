// CH5302.cpp
#include <iostream>
#include <cstdio>
#define ll long long
using namespace std;
const int Mod = 1e9;
string str;
ll dp[310][310];
int main()
{
    cin >> str;
    str = ' ' + str;
    int siz = str.size() - 1;
    for (int i = 1; i <= siz; i++)
        dp[i][i] = 1;
    for (int len = 2; len <= siz; len++)
        for (int i = 1; i + len - 1 <= siz; i++)
        {
            int j = i + len - 1;
            ll val = 0;
            dp[i][j] = dp[i + 1][j - 1];
            if (str[i] == str[j])
                for (int k = i + 2; k <= j - 2; k++)
                    dp[i][j] = (dp[i][j] + dp[i + 1][k - 1] * dp[k][j]) % Mod;
            else
                dp[i][j] = 0;
        }
    printf("%lld", dp[1][siz]);
    return 0;
}