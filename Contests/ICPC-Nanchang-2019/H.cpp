// H.cpp
#include <bits/stdc++.h>
#define ll long long
using namespace std;

ll quick_pow(ll bas, ll tim, ll mod)
{
    if (tim == 0)
        return 1;
    ll ans = 1;
    while (tim)
    {
        if (tim & 1)
            ans = bas * ans % mod;
        bas = bas * bas % mod;
        tim >>= 1;
    }
    return ans;
}

int main()
{
    int n;
    scanf("%d", &n);
    if (n == 0)
        printf("0"), exit(0);
    if (n == 1)
        printf("1"), exit(0);
    else
        printf("%lld", quick_pow(3, n - 2, 1000000007LL) * 4 % 1000000007LL);
    return 0;
}