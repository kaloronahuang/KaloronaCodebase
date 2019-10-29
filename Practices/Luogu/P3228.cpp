// P3228.cpp
#include <bits/stdc++.h>
typedef long long ll;

using namespace std;

int quick_pow(int bas, int tim, int mod)
{
    int ans = 1;
    bas %= mod;
    while (tim)
    {
        if (tim & 1)
            ans = 1LL * ans * bas % mod;
        bas = 1LL * bas * bas % mod;
        tim >>= 1;
    }
    return ans;
}

int main()
{
    ll n;
    int k, m, p;
    scanf("%lld%d%d%d", &n, &k, &m, &p);
    int ans = 1LL * n % p * quick_pow(m, k - 1, p) % p;
    int comp1 = 1LL * (k - 1) * quick_pow(m, k - 2, p) % p * ((1LL * m * (m + 1) >> 1) % p) % p;
    ans -= comp1;
    while (ans < 0)
        ans += p;
    ans %= p;
    printf("%d", ans);
    return 0;
}