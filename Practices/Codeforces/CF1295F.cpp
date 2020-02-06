// CF1295F.cpp
#include <bits/stdc++.h>

using namespace std;

const int MAX_N = 110, mod = 998244353;

int n, li[MAX_N], ri[MAX_N], upper, dp[MAX_N], inv[MAX_N], choose[MAX_N];
vector<int> mp;

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

int ripe(int x) { return lower_bound(mp.begin(), mp.end(), x) - mp.begin() + 1; }

int raw(int x) { return mp[x - 1]; }

int main()
{
    scanf("%d", &n);
    for (int i = 1; i <= n; i++)
        scanf("%d%d", &li[i], &ri[i]), mp.push_back(li[i]), mp.push_back(ri[i] + 1);
    sort(mp.begin(), mp.end()), mp.erase(unique(mp.begin(), mp.end()), mp.end());
    upper = mp.size();
    for (int i = 1; i <= n; i++)
        li[i] = ripe(li[i]), ri[i] = ripe(ri[i] + 1);
    dp[0] = inv[0] = 1;
    for (int i = 1; i <= n; i++)
        inv[i] = quick_pow(i, mod - 2);
    for (int j = upper - 1; j >= 1; j--)
    {
        int len = raw(j + 1) - raw(j);
        // process the binomials;
        choose[0] = 1;
        for (int i = 1; i <= n; i++)
            choose[i] = 1LL * choose[i - 1] * (i + len - 1) % mod * inv[i] % mod;
        for (int i = n; i >= 1; i--)
            if (li[i] <= j && j < ri[i])
                for (int c = 1, k = i - 1; k >= 0; k--, c++)
                {
                    dp[i] = (1LL * dp[i] + 1LL * choose[c] * dp[k] % mod) % mod;
                    if (li[k] > j || j >= ri[k])
                        break;
                }
    }
    int ans = dp[n];
    for (int i = 1; i <= n; i++)
        ans = 1LL * ans * quick_pow(raw(ri[i]) - raw(li[i]), mod - 2) % mod;
    printf("%d\n", ans);
    return 0;
}