// P1816.cpp
#include <iostream>
#include <algorithm>
#include <cmath>

using namespace std;

const int maxn = 100010;
int seq[maxn];
int dp[20][maxn];
int n, m;

void init()
{
    cin >> n >> m;
    for (int i = 1; i <= n; i++)
        cin >> seq[i];
}

void dp_func()
{
    for (int i = 1; i <= n; i++)
        dp[0][i] = seq[i];
    for (int i = 1; i <= log2(n); i++)
        for (int l = 1; l + (1 << i) - 1 <= n; l++)
            dp[i][l] = min(dp[i - 1][l], dp[i - 1][l + (1 << (i - 1))]);
}

int quiry(int l, int r)
{
    int i = (int)(log2(r - l + 1));
    return min(dp[i][l], dp[i][r - (1 << i) + 1]);
}

int main()
{
    init();
    dp_func();
    int l, r;
    for (int i = 0; i < m; i++)
        cin >> l >> r, cout << quiry(l, r) << " ";
    return 0;
}