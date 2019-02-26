// BZ2242.cpp
#include <bits/stdc++.h>
#define ll long long
using namespace std;
int T, K;
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
ll BSGS(ll bas, ll target, ll p)
{
    if (bas == 0 && target == 0)
        return 1;
    if (bas == 0 && target != 0)
        return -1;
    map<ll, ll> hashTable;
    ll m = ceil(sqrt(p));
    for (int j = 0, x = 1; j <= m; j++, x = bas * x % p)
        hashTable[x * target % p] = j;
    ll unit = quick_pow(bas, m, p);
    for (int i = 1, x = unit; i <= m; i++, x = x * unit % p)
        if (hashTable.count(x))
            return (i * m - hashTable[x]);
    return -1;
}
int main()
{
    scanf("%d%d", &T, &K);
    while (T--)
    {
        ll y, z, p;
        scanf("%lld%lld%lld", &y, &z, &p);
        if (K == 1)
            printf("%lld\n", quick_pow(y % p, z, p));
        else if (K == 2)
        {
            ll a = y, b = z, x, another;
            ll d = exgcd(a, p, x, another);
            if (b % d != 0)
                printf("Orz, I cannot find x!\n");
            else
            {
                ll pmod = p / d;
                ll ans = ((x * b / d) % pmod + pmod) % pmod;
                printf("%lld\n", ans);
            }
        }
        else
        {
            ll ans = BSGS(y % p, z % p, p);
            if (ans == -1)
                printf("Orz, I cannot find x!\n");
            else
                printf("%lld\n", ans);
        }
    }
    return 0;
}