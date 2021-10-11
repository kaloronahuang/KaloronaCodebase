// B.cpp
#include <bits/stdc++.h>

using namespace std;

const int mod = 1e9 + 7;

int fpow(int bas, int tim)
{
    int ret = 1;
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
    int T;
    scanf("%d", &T);
    while (T--)
    {
        int n, k;
        scanf("%d%d", &n, &k);
        int ret = 0, bas = 1;
        while (k)
        {
            ret = (0LL + ret + bas * (k & 1)) % mod;
            bas = 1LL * bas * n % mod;
            k >>= 1;
        }
        printf("%d\n", ret);
    }
    return 0;
}