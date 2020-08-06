// game.cpp
#include <bits/stdc++.h>

using namespace std;

const int MAX_N = 5050, mod = 998244353;

int n, p, ai[MAX_N], trans[MAX_N];

int fpow(int bas, int tim, int cmod)
{
    int ret = 1;
    while (tim)
    {
        if (tim & 1)
            ret = 1LL * ret * bas % cmod;
        bas = 1LL * bas * bas % cmod;
        tim >>= 1;
    }
    return ret;
}

int main()
{
    freopen("game.in", "r", stdin);
    freopen("game.out", "w", stdout);
    scanf("%d%d", &n, &p);
    for (int i = 1; i <= n; i++)
        scanf("%d", &ai[i]);
    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= n; j++)
            for (int k = 1; k <= p; k++)
                if (fpow(ai[i], k, p) == ai[j])
                {
                    trans[i] |= (1 << (j - 1));
                    break;
                }
                else if (k != 1 && fpow(ai[i], k, p) == ai[i])
                    break;
    int ans = 0;
    for (int stat = 1; stat < (1 << n); stat++)
    {
        int gans = 0x3f3f3f3f;
        for (int sub = stat; sub; sub = (sub - 1) & stat)
        {
            int pans = 0, cnt = 0;
            for (int i = 1; i <= n; i++)
                if (sub & (1 << (i - 1)))
                    pans |= trans[i], cnt++;
            if ((pans & stat) == stat)
                gans = min(gans, cnt);
        }
        ans = (0LL + ans + gans) % mod;
    }
    printf("%d\n", ans);
    return 0;
}