// QOJ2017.cpp
#include <bits/stdc++.h>

using namespace std;

const int MAX_N = 2e5 + 200, INF = 0x3f3f3f3f;

int m, n, min_val[MAX_N], nxt[20][MAX_N];

struct segment
{
    int l, r, id;
    bool operator<(const segment &rhs) const { return r < rhs.r || (r == rhs.r && l < rhs.l); }
} segs[MAX_N], xsegs[MAX_N];

bool compareByX(const segment &a, const segment &b) { return a.l < b.l || (a.l == b.l && a.r < b.r); }

int main()
{
    scanf("%d%d", &m, &n);
    for (int i = 1; i <= n; i++)
    {
        scanf("%d%d", &segs[i].l, &segs[i].r);
        if (segs[i].l > segs[i].r)
            segs[i].r += m;
        segs[i + n] = segs[i];
        segs[i + n].l += m, segs[i + n].r += m;
    }
    sort(segs + 1, segs + n + n + 1);
    for (int i = 1; i <= (2 * n); i++)
        xsegs[i] = segs[i], xsegs[i].id = i;
    sort(xsegs + 1, xsegs + 1 + n + n, compareByX);
    segs[0].r = xsegs[2 * n + 1].r = INF, min_val[2 * n + 1] = (2 * n + 1);
    for (int i = (2 * n); i >= 1; i--)
        min_val[i] = ((xsegs[i].r < xsegs[min_val[i + 1]].r) ? i : min_val[i + 1]);
    for (int i = 1, pos = 1; i <= (2 * n); i++)
    {
        while (segs[i].r > xsegs[min_val[pos]].l && pos <= (2 * n))
            pos++;
        nxt[0][i] = xsegs[min_val[pos]].id;
    }
    for (int i = 1; i < 20; i++)
        for (int j = 1; j <= (2 * n); j++)
            nxt[i][j] = nxt[i - 1][nxt[i - 1][j]];
    int ans = 1;
    for (int i = 1; i <= n; i++)
    {
        int pos = i, sum = 0;
        for (int j = 19; j >= 0; j--)
            if (segs[nxt[j][pos]].r <= m + segs[i].l)
                pos = nxt[j][pos], sum += (1 << j);
        ans = max(ans, sum);
    }
    printf("%d\n", ans + 1);
    return 0;
}