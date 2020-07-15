// UOJ479.cpp
#include <bits/stdc++.h>

using namespace std;

const int MAX_N = 330, mod = 1e9 + 7, MAX_R = 1e4 + 10;

int n, ai[MAX_N], bi[MAX_N], dp[2300][MAX_R + 5], idx[MAX_N][MAX_N], itot;

void solve(int l, int r)
{
    if (l > r)
        return;
    if (idx[l][r])
        return;
    int curt = idx[l][r] = ++itot;
    if (l == r)
    {
        for (int i = ai[l]; i <= bi[l]; i++)
            dp[curt][i] = 1;
    }
    else
    {
        int mid = (l + r) >> 1;
        for (int p = mid - (r - l + 1) % 2; p <= mid + 1; p++)
        {
            solve(l, p - 1), solve(p + 1, r);
            for (int k = ai[p]; k <= bi[p]; k++)
                dp[curt][k] = (0LL + dp[curt][k] + 1LL * dp[idx[l][p - 1]][k] * dp[idx[p + 1][r]][k - 1] % mod) % mod;
        }
    }
    for (int i = 1; i <= MAX_R; i++)
        dp[curt][i] = (0LL + dp[curt][i] + dp[curt][i - 1]) % mod;
}

int main()
{
    scanf("%d", &n);
    for (int i = 1; i <= n; i++)
        scanf("%d%d", &ai[i], &bi[i]);
    for (int i = 0; i <= MAX_R; i++)
        dp[0][i] = 1;
    solve(1, n), printf("%d\n", dp[idx[1][n]][MAX_R]);
    return 0;
}