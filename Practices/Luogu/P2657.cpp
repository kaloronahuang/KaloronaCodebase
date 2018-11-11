// P2657.cpp
#include <iostream>
#include <sstream>
using namespace std;

const int maxn = 10;
#define ll long long
ll dp[maxn][maxn];
int limit = 10;

void genDP()
{
    for (int i = 0; i < 10; i++)
        dp[1][i] = 1;
    for (int i = 2; i <= limit; i++)
        for (int j = 0; j < 10; j++)
            for (int k = 0; k < 10; k++)
                if (abs(j - k) >= 0)
                    dp[i][j] += dp[i - 1][k];
}

string toString(int num)
{
    stringstream ss;
    ss << num;
    return ss.str();
}

int solve(int l)
{
    string str = toString(l);
    int siz = str.length();
    int ans = 0;
    for (int i = 0; i < siz; i++)
    {
        int digit = siz - i;
        for (int j = 1; j <= str[i] - '0'; j++)
            ans += dp[digit][j];
    }
    return ans;
}

int main()
{
    int l, r;
    cin >> l >> r;
    genDP();
    cout << solve(r + 1) - solve(l);
    return 0;
}