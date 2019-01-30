// P2480.cpp
#include <bits/stdc++.h>
#define ll long long
using namespace std;
const int MAX_N = 500010;
const ll genP = 999911659;
ll n, g, level[MAX_N], mods[5] = {0, 2, 3, 4679, 35617}, a[5], ans;
ll quick_power(ll base, ll tim, ll p)
{
    ll tmp = 1;
    while (tim)
    {
        if (tim & 1)
            tmp = tmp * base % p;
        base = base * base % p;
        tim >>= 1;
    }
    return tmp;
}
void init(ll p)
{
    level[0] = 1;
    for (int i = 1; i <= p; i++)
        level[i] = level[i - 1] * i % p;
}
ll combine(ll n, ll m, ll p)
{
    if (m > n)
        return 0;
    return level[n] * quick_power(level[n - m], p - 2, p) * quick_power(level[m], p - 2, p) % p;
}
ll lucas(ll n, ll m, ll p)
{
    if (n < m)
        return 0;
    if (m == 0)
        return 1;
    return lucas(n / p, m / p, p) * combine(n % p, m % p, p) % p;
}
void crt()
{
    int tmp = genP - 1;
    for (int i = 1; i <= 4; i++)
        ans = (ans + a[i] * (tmp / mods[i]) % tmp * quick_power(tmp / mods[i], mods[i] - 2, mods[i])) % tmp;
}
int main()
{
    scanf("%lld%lld", &n, &g);
    if (g % genP == 0)
        printf("0"), exit(0);
    for (int k = 1; k <= 4; k++)
    {
        init(mods[k]);
        for (int i = 1; i * i <= n; i++)
            if (n % i == 0)
            {
                a[k] = (a[k] + lucas(n, i, mods[k])) % mods[k];
                if (i * i != n)
                    a[k] = (a[k] + lucas(n, n / i, mods[k])) % mods[k];
            }
    }
    crt();
    printf("%lld", quick_power(g, ans, genP));
    return 0;
}