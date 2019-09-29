// C.cpp
#include <bits/stdc++.h>
#define ll long long

ll gs, p[100005];
using namespace std;

const long long mod = 1e9 + 7;

int quick_pow(ll bas, ll tim)
{
    int ans = 1;
    bas %= mod, tim %= (mod - 1);
    while (tim)
    {
        if (tim & 1)
            ans = 1LL * ans * bas % mod;
        bas = 1LL * bas * bas % mod;
        tim >>= 1;
    }
    return ans;
}

ll fact_pow(ll q, ll k)
{
    ll res = 0;
    while (q)
        q /= k, res += q;
    return res;
}

void getPrime(long long k)
{
    for (int i = 2; 1LL * i * i <= k; i++)
        if (k % i == 0)
        {
            p[++gs] = i;
            while (k % i == 0)
                k /= i;
        }
    if (k > 1)
        p[++gs] = k;
}

long long ans = 1;

signed main()
{
    long long x, n;
    scanf("%lld%lld", &x, &n);
    getPrime(x);
    for (int i = 1; i <= gs; i++)
        ans = ans * (quick_pow(p[i], fact_pow(n, p[i]))) % mod;
    printf("%lld", ans % mod);
    return 0;
}