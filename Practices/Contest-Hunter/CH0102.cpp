// CH0102.cpp
#include <cstdio>
#define ll long long
int main()
{
    ll a, b, p;
    scanf("%lld%lld%lld", &a, &b, &p);
    ll ans = 0;
    for (; b; b >>= 1)
    {
        if (b & 1)
            ans = (a + ans) % p;
        a = a * 2 % p;
    }
    printf("%lld", ans);
    return 0;
}