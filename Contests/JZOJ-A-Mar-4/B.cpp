// B.cpp
#include <bits/stdc++.h>
#define ll long long
using namespace std;
const int MAX_N = 1e5 + 200, mod = 1e9 + 7;
int n, k, sumS[MAX_N], sumW[MAX_N], tmpx;
ll f[MAX_N], level[MAX_N], inv[MAX_N];
bool flag = true;
ll quick_pow(ll bas, ll tim)
{
    ll ans = 1;
    while (tim)
    {
        if (tim & 1)
            ans = ans * bas % mod;
        bas = bas * bas % mod;
        tim >>= 1;
    }
    return ans;
}
ll C(int a, int b) { return level[a] * inv[a - b] % mod * inv[b] % mod; }
int main()
{
    scanf("%d%d", &n, &k);
    level[0] = inv[0] = 1;
    for (int i = 1; i <= n; i++)
    {
        scanf("%d", &tmpx), level[i] = level[i - 1] * i % mod;
        if (tmpx == 1)
            sumW[i] = 1, flag = false;
        else
            sumS[i] = 1;
        sumW[i] += sumW[i - 1], sumS[i] += sumS[i - 1];
    }
    if (k == 0)
    {
        inv[n] = quick_pow(level[n], mod - 2);
        for (int i = n; i >= 2; i--)
            inv[i - 1] = inv[i] * i % mod;
        ll ans = 0;
        for (int i = 0; i <= n - 1; i++)
            ans = (ans + C(n - 1, i)) % mod;
        printf("%lld", ans);
        return 0;
    }
    f[0] = 1;
    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= i; j++)
            if (abs(sumS[i] - sumS[j - 1] - (sumW[i] - sumW[j - 1])) <= k)
                f[i] = (f[i] + f[j - 1]) % mod;
    printf("%lld", f[n]);
    return 0;
}