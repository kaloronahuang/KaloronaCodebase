// P4071.cpp
#include <iostream>
#include <cstdio>
#define ll long long
using namespace std;
const int MOD = 1e9 + 7, MX_N = 1000020;
ll D[MX_N], rev[MX_N], level[MX_N];
ll quick_power(ll base, ll tim)
{
    ll tmp = 1;
    while (tim)
    {
        if (tim & 1)
            tmp = tmp * base % MOD;
        base = base * base % MOD;
        tim >>= 1;
    }
    return tmp;
}
int main()
{
    D[1] = 0, D[2] = 1, D[3] = 2, D[4] = 9;
    for (int i = 5; i < MX_N; i++)
        D[i] = ((i - 1) * (D[i - 1] + D[i - 2]) % MOD) % MOD;
    level[0] = 1;
    int tot = MX_N - 1;
    for (int i = 1; i < MX_N; i++)
        level[i] = level[i - 1] * i % MOD, rev[i] = quick_power(level[i], MOD - 2);
    int T;
    scanf("%d", &T);
    while (T--)
    {
        ll n, m;
        scanf("%lld%lld", &n, &m);
        if (n - m == 1)
            printf("%d\n", 0);
        else if (n == m)
            printf("%d\n", 1);
        else if (m == 0)
            printf("%lld\n", D[n]);
        else
        {
            ll res = level[n] % MOD * rev[m] % MOD * rev[n - m] % MOD * D[n - m] % MOD;
            printf("%lld\n", res);
        }
    }
    return 0;
}