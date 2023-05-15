#include <iostream>
#include <cstdio>

using namespace std;
#define ll long long

const ll maxn = 4000000;
ll level[maxn];
ll res[maxn];

ll qpow(ll base, ll tim, ll mod)
{
    ll tmp = 1;
    while (tim)
    {
        if (tim & 1)
            tmp = tmp * base % mod;
        base = base * base % mod;
        tim >>= 1;
    }
    return tmp;
}

int main()
{
    ll n, p;
    scanf("%lld%lld", &n, &p);
    level[0] = 1;
    for (int i = 1; i <= n; i++)
        level[i] = i * level[i - 1] % p;
    ll levelr = qpow(level[n], p - 2, p);
    for (int i = n; i > 0; i--)
    {
        res[i] = levelr * level[i - 1] % p;
        levelr = levelr * i % p;
    }
    for (int i = 1; i <= n; i++)
        printf("%lld\n", res[i]);
    return 0;
}