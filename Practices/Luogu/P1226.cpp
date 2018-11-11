// P1226.cpp
#include <cstdio>
#define ll long long
ll qpow(ll a, ll b, ll mod)
{
    ll ans = 1 % mod;
    for (; b; b >>= 1)
    {
        if (b & 1)
            ans = ans * a % mod;
        a = a * a % mod;
    }
    return ans;
}
int main()
{
    ll b, p, k;
    scanf("%lld%lld%lld", &b, &p, &k);
    printf("%lld^%lld mod %lld=%lld", b, p, k, qpow(b, p, k));
    return 0;
}