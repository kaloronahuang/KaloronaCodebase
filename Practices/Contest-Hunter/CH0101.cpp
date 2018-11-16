// CH0101.cpp
#include <cstdio>
#define ll long long
ll quickPow(ll base, ll tim, ll mod)
{
    ll ans = 1;
    for (; tim; tim >>= 1)
    {
        if (tim & 1)
            ans = ans * base % mod;
        base = base * base % mod;
    }
    return ans % mod;
}
int main()
{
    ll a, b, p;
    scanf("%lld%lld%lld", &a, &b, &p);
    printf("%lld", quickPow(a, b, p));
    return 0;
}