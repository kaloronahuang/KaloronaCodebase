// YBT-OJ1681.cpp
#include <bits/stdc++.h>

using namespace std;

const int MAX_N = 40, gmod = 1e9 + 7;

int n, p, c, seq[MAX_N];
map<int, int> mp;

int quick_pow(int bas, int tim, int mod)
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
    scanf("%d%d%d", &n, &p, &c);
    for (int i = 1; i <= n; i++)
        scanf("%d", &seq[i]);
    int fore = (n >> 1), back = n - fore;
    if (c >= p)
        puts("0"), exit(0);
    for (int stat = 0; stat < (1 << fore); stat++)
    {
        int tmp = 1;
        for (int i = 1; i <= fore; i++)
            if (stat & (1 << (i - 1)))
                tmp = 1LL * tmp * seq[i] % p;
        mp[tmp]++;
    }
    int ans = mp[c];
    for (int stat = 1; stat < (1 << back); stat++)
    {
        int tmp = 1;
        for (int i = fore + 1; i <= n; i++)
            if (stat & (1 << (i - fore - 1)))
                tmp = 1LL * tmp * seq[i] % p;
        ans = (1LL * ans + mp[1LL * c * quick_pow(tmp, p - 2, p) % p]) % gmod;
    }
    if (c == 1)
        ans = (1LL * ans + gmod - 1) % gmod;
    printf("%d\n", ans);
    return 0;
}