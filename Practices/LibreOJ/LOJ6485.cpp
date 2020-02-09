// LOJ6485.cpp
#include <bits/stdc++.h>

using namespace std;

const int mod = 998244353, g = 3;

typedef long long ll;

int T, s, ai[4];
ll n;

int quick_pow(int bas, ll tim)
{
    int ret = 1;
    while (tim)
    {
        if (tim & 1LL)
            ret = 1LL * ret * bas % mod;
        bas = 1LL * bas * bas % mod;
        tim >>= 1;
    }
    return ret;
}

const int inv4 = quick_pow(4, mod - 2), wn = quick_pow(g, (mod - 1) / 4);

int wns[4], ans[4];

int main()
{
    scanf("%d", &T), wns[0] = 1;
    for (int i = 1; i < 4; i++)
        wns[i] = 1LL * wns[i - 1] * wn % mod;
    while (T--)
    {
        scanf("%lld%d%d%d%d%d", &n, &s, &ai[0], &ai[1], &ai[2], &ai[3]);
        for (int i = 0; i < 4; i++)
            ans[i] = 0;
        for (int idx = 0; idx < 4; idx++)
        {
            for (int i = 0; i < 4; i++)
                ans[idx] = (1LL * ans[idx] + 1LL * quick_pow(wns[i], 4 - idx) * quick_pow((1LL * wns[i] * s % mod + 1) % mod, n) % mod) % mod;
            ans[idx] = 1LL * ans[idx] * ai[idx] % mod * inv4 % mod;
        }
        /*
        // a0;
        for (int i = 0; i < 3; i++)
            ans[0] = (1LL * ans[0] + quick_pow((1LL * wns[i] * s % mod + 1) % mod, 1LL * n % (mod - 1))) % mod;
        ans[0] = 1LL * ans[0] * ai[0] % mod * inv4 % mod;
        // a1;
        for (int i = 0; i < 3; i++)
            ans[1] = (1LL * ans[1] + 1LL * pow3(wns[i]) * quick_pow((1LL * s * wns[i] % mod + 1) % mod, 1LL * n % (mod - 1)) % mod) % mod;
        ans[1] = 1LL * ans[1] * ai[1] % mod * inv4 % mod;
        // a2;
        for (int i = 0; i < 3; i++)
            ans[2] = (1LL * ans[2] + 1LL * pow2(wns[i]) * quick_pow((1LL * s * wns[i] % mod + 1) % mod, 1LL * n % (mod - 1)) % mod) % mod;
        ans[2] = 1LL * ans[2] * ai[2] % mod * inv4 % mod;
        // a3;
        for (int i = 0; i < 3; i++)
            ans[3] = (1LL * ans[3] + 1LL * wns[i] * quick_pow((1LL * s * wns[i] % mod + 1) % mod, 1LL * n % (mod - 1)) % mod) % mod;
        ans[3] = 1LL * ans[3] * ai[3] % mod * inv4 % mod;
        */
        int gans = 0;
        for (int i = 0; i < 4; i++)
            gans = (0LL + gans + ans[i]) % mod;
        printf("%d\n", gans);
    }
    return 0;
}