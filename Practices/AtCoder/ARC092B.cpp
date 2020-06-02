// ARC092B.cpp
#include <bits/stdc++.h>

using namespace std;

const int MAX_N = 2e5 + 200;

int n, ai[MAX_N], bi[MAX_N], ta[MAX_N], tb[MAX_N];

int main()
{
    scanf("%d", &n);
    for (int i = 1; i <= n; i++)
        scanf("%d", &ai[i]);
    for (int i = 1; i <= n; i++)
        scanf("%d", &bi[i]);
    int ans = 0;
    for (int b = 0; b < 29; b++)
    {
        int T = 1 << b, mod = T << 1;
        for (int i = 1; i <= n; i++)
            ta[i] = ai[i] % mod, tb[i] = bi[i] % mod;
        sort(tb + 1, tb + 1 + n);
        int pans = 0;
        for (int i = 1; i <= n; i++)
        {
            int l = lower_bound(tb + 1, tb + 1 + n, T - ta[i]) - tb;
            int r = lower_bound(tb + 1, tb + 1 + n, mod - ta[i]) - tb;
            pans ^= (r - l) & 1;
            l = lower_bound(tb + 1, tb + 1 + n, T * 3 - ta[i]) - tb;
            r = lower_bound(tb + 1, tb + 1 + n, (mod << 1) - ta[i]) - tb;
            pans ^= (r - l) & 1;
        }
        ans += (pans << b);
    }
    printf("%d\n", ans);
    return 0;
}