// BZ4035.cpp
#include <bits/stdc++.h>

using namespace std;

const int MAX_N = 1e5 + 200;

int T, n, block, w, sg[2][MAX_N], vis[MAX_N];

int nxt(int x, int y) { return (x == y) ? y + 1 : y / (y / (x + 1)); }

int read(int x) { return x <= block ? sg[0][x] : sg[1][n / x]; }

void sieve()
{
    int rd = 0;
    sg[0][1] = 1;
    for (int i = 2, curt; i <= n; i = nxt(i, n))
    {
        rd++, vis[curt = 0] = rd;
        for (int j = 2, gx; j <= i; j = gx + 1)
        {
            gx = i / (i / j);
            vis[curt ^ read(i / j)] = vis[curt] = rd;
            if ((gx - j + 1) & 1)
                curt ^= read(i / j);
        }
        int ans = 1;
        while (vis[ans] == rd)
            ans++;
        if (i <= block)
            sg[0][i] = ans;
        else
            sg[1][n / i] = ans;
    }
}

int main()
{
    scanf("%d%d", &n, &T), block = sqrt(n);
    sieve();
    while (T--)
    {
        scanf("%d", &w);
        int sum = 0;
        for (int i = 1, v; i <= w; i++)
            scanf("%d", &v), sum ^= read(n / v);
        if (sum)
            puts("Yes");
        else
            puts("No");
    }
    return 0;
}