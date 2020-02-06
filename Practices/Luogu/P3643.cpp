// P3643.cpp
#include <bits/stdc++.h>

using namespace std;

const int MAX_N = 1010, mod = 1e9 + 7;

int n, li[MAX_N], ri[MAX_N], inv[MAX_N], fac[MAX_N], dp[MAX_N][MAX_N], pre[MAX_N], limit[MAX_N];
vector<int> mp;

int getRipe(int x) { return lower_bound(mp.begin(), mp.end(), x) - mp.begin() + 1; }

int getRaw(int x) { return mp[x - 1]; }

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

int main()
{
    scanf("%d", &n);
    for (int i = 1; i <= n; i++)
        scanf("%d%d", &li[i], &ri[i]), mp.push_back(li[i]), mp.push_back(ri[i] + 1);
    sort(mp.begin(), mp.end()), mp.erase(unique(mp.begin(), mp.end()), mp.end());
    for (int i = 1; i <= n; i++)
        li[i] = getRipe(li[i]), ri[i] = getRipe(ri[i] + 1);
    fac[0] = inv[0] = 1;
    for (int i = 1; i < MAX_N; i++)
        fac[i] = 1LL * fac[i - 1] * i % mod;
    int bas = quick_pow(fac[MAX_N - 1], mod - 2), upper = mp.size();
    for (int i = MAX_N - 1; i >= 1; i--)
        inv[i] = 1LL * bas * fac[i - 1] % mod, bas = 1LL * bas * i % mod;
    dp[0][0] = 1;
    for (int i = 0; i < upper; i++)
        pre[i] = 1;
    for (int i = 1; i <= n; i++)
    {
        for (int j = li[i]; j <= ri[i] - 1; j++)
        {
            limit[j]++;
            for (int k = limit[j]; k >= 2; k--)
                dp[j][k] = (1LL * dp[j][k] + 1LL * dp[j][k - 1] * ((getRaw(j + 1) - getRaw(j) - k + 1) % mod) % mod * inv[k] % mod) % mod;
            dp[j][1] = (1LL * dp[j][1] + 1LL * (getRaw(j + 1) - getRaw(j)) * pre[j - 1] % mod) % mod;
        }
        for (int j = 1; j < upper; j++)
        {
            pre[j] = pre[j - 1];
            for (int k = 1; k <= limit[j]; k++)
                pre[j] = (0LL + pre[j] + dp[j][k]) % mod;
        }
    }
    printf("%lld\n", (0LL + pre[upper - 1] + mod - 1) % mod);
    return 0;
}