// always.cpp
#include <bits/stdc++.h>

using namespace std;

const int MAX_N = 1e5 + 200, mod = 998244353;

int n, tot, ci[MAX_N], si[MAX_N], inv[MAX_N], ans;

void dfs(int u)
{
    if (u == tot + 1)
    {
        int last = 1, prod = 1;
        vector<int> v;
        for (int i = 1; i <= tot + 1; i++)
            if (si[i] != si[last])
            {
                v.push_back(i - last);
                last = i;
            }
        if (v.size() > 1)
        {
            if (si[1] == si[tot])
                v[0] += v.back(), v.pop_back();
            for (int i = 0, siz = v.size(); i < siz; i++)
                prod = 1LL * prod * inv[v[i]] % mod;
        }
        ans = (0LL + ans + prod) % mod;
        return;
    }
    for (int i = 1; i <= n; i++)
        if (ci[i] > 0)
            ci[i]--, si[u] = i, dfs(u + 1), ci[i]++;
}

int main()
{
    freopen("always.in", "r", stdin);
    freopen("always.out", "w", stdout);
    scanf("%d", &n);
    for (int i = 1; i <= n; i++)
        scanf("%d", &ci[i]), tot += ci[i];
    inv[0] = inv[1] = 1;
    for (int i = 2; i <= tot; i++)
        inv[i] = 1LL * (mod - mod / i) * inv[mod % i] % mod;
    dfs(1), printf("%d\n", ans);
    return 0;
}