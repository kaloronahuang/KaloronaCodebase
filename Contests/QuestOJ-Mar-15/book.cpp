// book.cpp
#include <bits/stdc++.h>

using namespace std;

const int MAX_N = 2010, mod = 1e9 + 7;

int n, ai[MAX_N], bi[MAX_N], pi[MAX_N];

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
    scanf("%d", &n);
    for (int i = 1; i <= n; i++)
        scanf("%d%d", &ai[i], &bi[i]), pi[i] = 1LL * ai[i] * fpow(bi[i], mod - 2) % mod;
    int gans = 0;
    for (int i = 1; i <= n; i++)
    {
        int pans = 1;
        for (int j = 1; j <= n; j++)
            if (i != j)
                pans = (0LL + pans + 1LL * pi[j] * fpow((0LL + pi[i] + pi[j]) % mod, mod - 2) % mod) % mod;
        gans = (0LL + gans + 1LL * pi[i] * pans % mod) % mod;
    }
    printf("%d\n", gans);
    return 0;
}