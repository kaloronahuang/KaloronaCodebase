// LOJ3093.cpp
#include <bits/stdc++.h>

using namespace std;

const int MAX_N = 5e5 + 200, mod = 1e9 + 7;

int n, ai[MAX_N], bi[MAX_N];

int quick_pow(int bas, int tim)
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

const int inv100 = quick_pow(100, mod - 2);

int main()
{
    scanf("%d", &n);
    int P = 1, Q = 0;
    for (int i = 1; i <= n; i++)
    {
        scanf("%d%d", &ai[i], &bi[i]);
        ai[i] = 1LL * ai[i] * inv100 % mod, bi[i] = 1LL * bi[i] * inv100 % mod;
        int w = quick_pow((1 + mod - 1LL * Q * bi[i] % mod) % mod, mod - 2);
        Q = (0LL + bi[i] + 1LL * ai[i] * ai[i] % mod * Q % mod * w % mod) % mod;
        P = 1LL * P * ai[i] % mod * w % mod;
    }
    printf("%d\n", P);
    return 0;
}