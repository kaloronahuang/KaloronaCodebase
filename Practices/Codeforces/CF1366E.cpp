// CF1366E.cpp
#include <bits/stdc++.h>

using namespace std;

const int MAX_N = 2e5 + 200, mod = 998244353;

int n, m, ai[MAX_N], bi[MAX_N];

int main()
{
    scanf("%d%d", &n, &m);
    for (int i = 1; i <= n; i++)
        scanf("%d", &ai[i]);
    for (int i = 1; i <= m; i++)
        scanf("%d", &bi[i]);
    reverse(ai + 1, ai + 1 + n);
    reverse(bi + 1, bi + 1 + m);
    ai[n + 1] = -1;
    int min_val = ai[1], pos = 1;
    while (pos <= n && min_val > bi[1])
        pos++, min_val = min(min_val, ai[pos]);
    if (pos == n + 1 || min_val < bi[1])
        puts("0"), exit(0);
    int ans = 1, bptr = 1;
    while (true)
    {
        if (bptr == m)
        {
            if (*min_element(ai + pos, ai + n + 1) != bi[bptr])
                puts("0"), exit(0);
            break;
        }
        bool pinned = true;
        int nptr = pos;
        while (nptr <= n && min_val != bi[bptr + 1])
        {
            nptr++, min_val = min(min_val, ai[nptr]);
            if (pinned && min_val < bi[bptr])
                pinned = false, ans = 1LL * ans * (nptr - pos) % mod;
        }
        if (nptr == n + 1 || min_val != bi[bptr + 1])
            puts("0"), exit(0);
        bptr++, pos = nptr;
    }
    printf("%d\n", ans);
    return 0;
}