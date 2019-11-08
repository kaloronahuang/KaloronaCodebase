// A.cpp
#include <bits/stdc++.h>

using namespace std;

const int mod = 998244353;

int quick_pow(int bas, int tim)
{
    int ret = 1;
    bas %= mod;
    while (tim)
    {
        if (tim & 1)
            ret = 1LL * ret * bas % mod;
        bas = 1LL * bas * bas % mod;
        tim >>= 1;
    }
    return ret;
}

int main()
{
    int n;
    scanf("%d", &n), printf("%d", quick_pow(2, n));
    return 0;
}