// P1641.cpp
#include <bits/stdc++.h>
#define ll long long
using namespace std;
const int MAX_N = 2001000, mod = 20100403;
ll level[MAX_N], inv[MAX_N];
ll inverse(ll bas)
{
    ll tim = mod - 2, ans = 1;
    while (tim)
    {
        if (tim & 1)
            ans = ans * bas % mod;
        bas = bas * bas % mod;
        tim >>= 1;
    }
    return ans;
}
int main()
{
    int n, m;
    scanf("%d%d", &n, &m);
    level[0] = inv[0] = 1;
    for (int i = 1; i < MAX_N; i++)
        level[i] = level[i - 1] * i % mod;
    inv[MAX_N - 1] = inverse(level[MAX_N - 1]);
    for (int i = MAX_N - 1; i >= 2; i--)
        inv[i - 1] = inv[i] * i % mod;
    printf("%lld", (level[n + m] * inv[n] % mod * inv[m] % mod - level[n + m] * inv[n + 1] % mod * inv[m - 1] % mod + mod) % mod);
    return 0;
}