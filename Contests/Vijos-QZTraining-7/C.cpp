// C.cpp
#include <bits/stdc++.h>

using namespace std;

const int MAX_N = 1e5 + 200, INF = 0x3f3f3f3f;

struct block
{
    int l, r;
    bool operator<(const block &target) const { return l < target.l || (l == target.l && r < target.r); }
} bs[MAX_N];

int n, q, len, ci[MAX_N], suffix[MAX_N], pos[MAX_N];

int main()
{
    scanf("%d%d%d", &n, &q, &len);
    for (int i = 1; i <= n; i++)
        scanf("%d%d", &bs[i].l, &bs[i].r);
    sort(bs + 1, bs + 1 + n);
    for (int i = 1; i <= len + 1; i++)
        ci[i] = len + 1;
    for (int i = 1; i <= n; i++)
    {
        if (i > 1 && bs[i].l == bs[i - 1].l)
            continue;
        ci[bs[i].l] = bs[i].r;
    }
    suffix[len] = ci[len], pos[len] = len;
    for (int i = len - 1; i >= 1; i--)
    {
        suffix[i] = min(suffix[i + 1], ci[i]);
        pos[i] = suffix[i + 1] < ci[i] ? pos[i + 1] : i;
    }
    pos[len + 1] = len + 1;
    while (q--)
    {
        int x, y;
        scanf("%d%d", &x, &y);
        int z = pos[x], res = 0;
        while (ci[z] <= y)
            res++, z = pos[ci[z] + 1];
        printf("%d\n", res);
    }
    return 0;
}