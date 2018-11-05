#include <cstdio>
#include <iostream>
using namespace std;
typedef long long int ll;
const int MAXN = 1e5 + 5;
int T, n, m, p;
ll fac[MAXN], inv[MAXN];
ll quick_mi(ll base, ll index, ll mod)
{
    ll temp = 1;
    while (index)
    {
        if (index & 1)
            temp = temp * base % mod;
        base = base * base % mod;
        index >>= 1;
    }
    return temp;
}
ll lucas(ll kn, ll km, ll mod)
{
    if (kn < km)
        return 0;
    if (kn < mod)
        return fac[kn] * inv[km] % mod * inv[kn - km] % p;
    return lucas(kn % mod, km % mod, mod) * lucas(kn / mod, km / mod, mod) % p;
}
void init()
{
    fac[0] = 1;
    inv[0] = 1;
    for (int i = 1; i <= p; ++i)
        fac[i] = fac[i - 1] * i % p;
    inv[p - 1] = quick_mi(fac[p - 1], p - 2, p);
    for (int i = p - 2; i >= 1; --i)
        inv[i] = inv[i + 1] * (i + 1) % p;
}
int main()
{
    scanf("%d", &T);
    while (T--)
    {
        scanf("%d%d%d", &n, &m, &p);
        init();
        printf("%lld\n", lucas(n + m, m, p));
    }
}