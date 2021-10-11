// E1.cpp
#include <bits/stdc++.h>

using namespace std;

const int mod = 1e9 + 7;

int fpow(int bas, int tim, int modulo)
{
    int ret = 1;
    while (tim)
    {
        if (tim & 1)
            ret = 1LL * ret * bas % modulo;
        bas = 1LL * bas * bas % modulo;
        tim >>= 1;
    }
    return ret;
}

int main()
{
    int k;
    scanf("%d", &k), printf("%lld\n", 6LL * fpow(4, (fpow(2, k, mod - 1) + mod - 1 - 2) % (mod - 1), mod) % mod);
    return 0;
}