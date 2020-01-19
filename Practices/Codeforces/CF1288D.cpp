// CF1288D.cpp
#include <bits/stdc++.h>

using namespace std;

const int MAX_N = 3e5 + 200;

int n, m, ai[MAX_N][10], bits[MAX_N], As, Bs, vis[300];

bool check(int mid)
{
    memset(vis, 0, sizeof(vis));
    memset(bits, 0, sizeof(bits));
    for (int i = 1; i <= n; i++)
    {
        int req = 0;
        for (int j = 1; j <= m; j++)
            if (ai[i][j] >= mid)
                bits[i] |= (1 << (j - 1));
            else
                req |= (1 << (j - 1));
        vis[bits[i]] = i;
        if (vis[req])
            return (As = vis[req], Bs = i, true);
        for (int subset = bits[i]; subset != 0; subset = (subset - 1) & (bits[i]))
            if (vis[req ^ subset])
                return (As = vis[req ^ subset], Bs = i, true);
    }
    return false;
}

int main()
{
    scanf("%d%d", &n, &m);
    int l = 1e9, r = 0;
    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= m; j++)
            scanf("%d", &ai[i][j]), l = min(l, ai[i][j]), r = max(r, ai[i][j]);
    while (l <= r)
    {
        int mid = (l + r) >> 1;
        if (check(mid))
            l = mid + 1;
        else
            r = mid - 1;
    }
    printf("%d %d\n", As, Bs);
    return 0;
}