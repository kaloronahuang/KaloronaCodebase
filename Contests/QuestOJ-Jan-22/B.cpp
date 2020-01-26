// B.cpp
#include <bits/stdc++.h>

using namespace std;

const int MAX_N = 310, mod = 998244353;

int n, limit, dp[MAX_N][MAX_N][MAX_N][2];

int quick_pow(int bas, int tim)
{
    int ret = 1;
    while (tim)
    {
        if (tim & 1)
            ret = 1LL * ret * bas % mod;
        bas = 1LL * bas * bas % mod;
        tim >>= 1;
    }
    return ret;
}

namespace Subtask1
{

int dep[MAX_N], fa[MAX_N], gans, diff[MAX_N];

void dfs(int pos)
{
    if (pos == n + 1)
    {
        int mx_dep = 0;
        for (int i = n; i >= 1; i--)
            mx_dep = max(mx_dep, dep[i] = dep[fa[i]] + 1);
        if (mx_dep <= limit)
            gans++;
        return;
    }
    for (int i = pos + 1; i <= n + 1; i++)
    {
        bool flag = true;
        fa[pos] = i;
        for (int j = 1; j < pos; j++)
            if (fa[pos] > fa[j] && pos < fa[j])
            {
                flag = false;
                break;
            }
        if (flag)
            dfs(pos + 1);
    }
}

void subtask1Handler()
{
    dfs(1), printf("%d\n", gans);
}

} // namespace Subtask1

int main()
{
    scanf("%d%d", &n, &limit);
    Subtask1::subtask1Handler();
    return 0;
}