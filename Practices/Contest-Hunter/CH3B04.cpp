// CH3B04.cpp
#include <bits/stdc++.h>
#define ll long long
using namespace std;
const int MAX_N = 12;
ll n, ai[MAX_N], bi[MAX_N], tprod = 1;
ll quick_pow(ll bas, ll tim, ll mod)
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
ll exgcd(ll a, ll b, ll &x, ll &y)
{
    if (b == 0)
    {
        x = 1, y = 0;
        return a;
    }
    ll d = exgcd(b, a % b, x, y);
    ll z = x;
    x = y, y = z - (a / b) * y;
    return d;
}
int main()
{
    scanf("%lld", &n);
    for (int i = 1; i <= n; i++)
        scanf("%lld%lld", &ai[i], &bi[i]), tprod *= ai[i];
    ll ans = 0;
    for (int i = 1; i <= n; i++)
    {
        ll m = tprod / ai[i], m_1, y;
        ll d = exgcd(m, ai[i], m_1, y);
        m_1 = m_1 / d;
        while (m_1 < 0)
            m_1 += ai[i];
        m_1 %= ai[i];
        ll res_part = m * m_1;
        ans = (ans + res_part * bi[i] % tprod) % tprod;
    }
    printf("%lld", ans);
    return 0;
}