#include <iostream>
#include <cstdio>
#define ll long long
using namespace std;
const int maxq = 1000200;
ll bi[maxq], reses[maxq];
ll a, p, q, k, l, m, c, cur;
ll quick_pow(ll base, ll tim, ll mod)
{
    if (base == 1)
        return 1;
    if (tim == 1)
        return base % mod;
    ll res = quick_pow(base, tim / 2, mod);
    if (base & 1)
        return (base * res % mod) * res % mod;
    return res * res % mod;
}
void solve()
{
    for (int i = 1; i <= q; i++)
    {
        ll res = quick_pow(a, bi[i], p);
        if (res % k == 0)
            reses[++cur] = res ^ reses[cur - 1];
    }
}
int main()
{
    freopen("pow.in", "r", stdin);
    freopen("pow.out", "w", stdout);
    scanf("%lld%lld%lld%lld%lld%lld%lld%lld", &a, &p, &q, &k, &bi[0], &l, &m, &c);
    for (int i = 1; i <= q; i++)
        bi[i] = (m * bi[i - 1] + c) % l;
    solve();
    for (int i = 1; i <= (int)(q / k); i++)
        printf("%lld", reses[i]);
    return 0;
}