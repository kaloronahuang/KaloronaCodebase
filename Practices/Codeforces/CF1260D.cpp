// CF1260D.cpp
#include <bits/stdc++.h>

using namespace std;

const int MAX_N = 5e5 + 2000;

int m, n, k, t, ai[MAX_N], li[MAX_N], ri[MAX_N], di[MAX_N];

struct level
{
    int l, r, d;
    bool operator<(const level &rhs) const { return l < rhs.l; }
} levels[MAX_N];

bool check(int mid)
{
    int lowest = ai[m - mid + 1], tot = 0;
    for (int i = 1; i <= k; i++)
        if (di[i] > lowest)
            levels[++tot] = level{li[i], ri[i], di[i]};
    sort(levels + 1, levels + 1 + tot);
    int curt_time = 0, pos = 0;
    for (int i = 1; i <= tot; i++)
        if (levels[i].l <= pos)
            curt_time += max(0, levels[i].r - pos), pos = max(pos, levels[i].r);
        else
            curt_time += levels[i].r - levels[i].l + 1, pos = levels[i].r;
    curt_time = (curt_time * 2) + 1 + n;
    return curt_time <= t;
}

int main()
{
    scanf("%d%d%d%d", &m, &n, &k, &t);
    for (int i = 1; i <= m; i++)
        scanf("%d", &ai[i]);
    for (int i = 1; i <= k; i++)
        scanf("%d%d%d", &li[i], &ri[i], &di[i]);
    sort(ai + 1, ai + 1 + m);
    int l = 1, r = m, ans = 0;
    while (l <= r)
    {
        int mid = (l + r) >> 1;
        if (check(mid))
            l = mid + 1, ans = mid;
        else
            r = mid - 1;
    }
    printf("%d\n", ans);
    return 0;
}