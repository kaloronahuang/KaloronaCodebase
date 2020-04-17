// POJ1286.cpp
#include <iostream>
#include <cstdio>
#include <algorithm>

using namespace std;

typedef unsigned long long ll;

ll fpow(int bas, int tim)
{
    ll ret = 1;
    while (tim)
    {
        if (tim & 1)
            ret *= bas;
        bas *= bas;
        tim >>= 1;
    }
    return ret;
}

int main()
{
    int n;
    while (scanf("%d", &n) && n != -1)
    {
        if (n == 0)
        {
            puts("0");
            continue;
        }
        ll ans = 0;
        for (int i = 1; i <= n; i++)
            ans += fpow(3, __gcd(i, n));
        if (n & 1)
            ans += 1LL * n * fpow(3, (n + 1) >> 1);
        else
            ans += 1LL * (n >> 1) * (fpow(3, (n >> 1) + 1) + fpow(3, n >> 1));
        printf("%llu\n", (ans / (n << 1)));
    }
    return 0;
}