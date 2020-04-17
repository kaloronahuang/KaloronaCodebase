// P5204.cpp
#include <bits/stdc++.h>

using namespace std;

const int MAX_N = 1e5 + 200, mod = 1e9 + 7;

int n, seg, ci[MAX_N], dp[MAX_N];

int fpow(int bas, int tim)
{
    int ret = 1;
    for (; tim; tim >>= 1, bas = 1LL * bas * bas % mod)
        if (tim & 1)
            ret = 1LL * ret * bas % mod;
    return ret;
}

int solve(int len, int val)
{
    int x = 1e9 - val, xseg = fpow(x, seg);
    dp[0] = dp[1] = 1;
    for (int i = 2; i <= len + 1; i++)
    {
        dp[i] = 1LL * (x + 1) * dp[i - 1] % mod;
        if (i - seg - 1 >= 0)
            dp[i] = (0LL + dp[i] + mod - 1LL * xseg * dp[i - seg - 1] % mod) % mod;
    }
    return dp[len + 1];
}

int main()
{
    scanf("%d%d", &n, &seg);
    for (int i = 1; i <= n - seg + 1; i++)
        scanf("%d", &ci[i]);
    int ans = 1;
    for (int i = 1, gx, len; i <= n - seg + 1; i = gx + 1)
    {
        gx = i;
        while (ci[gx + 1] == ci[i])
            gx++;
        len = gx - i + seg;
        if (i != 1 && ci[i - 1] > ci[i])
            len -= seg;
        if (gx != n - seg + 1 && ci[gx + 1] > ci[i])
            len -= seg;
        if (len > 0)
            ans = 1LL * ans * solve(len, ci[i]) % mod;
    }
    printf("%d\n", ans);
    return 0;
}