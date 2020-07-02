// C.cpp
#include <bits/stdc++.h>

using namespace std;

const int MAX_N = 1e5 + 200, mod = 998244353;

typedef long long ll;

int n, m[3], base, vis[MAX_N], sg[MAX_N];
vector<int> G[MAX_N], sum[3];

int fpow(int bas, int tim)
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

int main()
{
    scanf("%d", &n), base = fpow(ll(1e18) % mod, mod - 2);
    for (int rd = 0; rd < 3; rd++)
    {
        scanf("%d", &m[rd]);
        for (int i = 1; i <= n; i++)
            G[i].clear();
        for (int i = 1, u, v; i <= m[rd]; i++)
        {
            scanf("%d%d", &u, &v);
            if (u > v)
                swap(u, v);
            G[u].push_back(v);
        }
        memset(sg, 0, sizeof(sg)), memset(vis, -1, sizeof(vis));
        int cbase = fpow(10, 18 * n);
        for (int i = n; i >= 1; i--)
        {
            for (int v : G[i])
                vis[sg[v]] = i;
            while (vis[sg[i]] == i)
                sg[i]++;
            while (sum[rd].size() <= sg[i])
                sum[rd].push_back(0);
            sum[rd][sg[i]] = (0LL + sum[rd][sg[i]] + cbase) % mod, cbase = 1LL * cbase * base % mod;
        }
    }
    int ans = 0;
    for (int i = 0, siz1 = sum[0].size(); i < siz1; i++)
        for (int j = 0, siz2 = sum[1].size(); j < siz2; j++)
        {
            int k = i ^ j;
            if (k < sum[2].size())
                ans = (0LL + ans + 1LL * sum[0][i] * sum[1][j] % mod * sum[2][k] % mod) % mod;
        }
    printf("%d\n", ans);
    return 0;
}