// CF292D.cpp
#include <bits/stdc++.h>

using namespace std;

const int MAX_N = 10010;

struct ufs
{
    int fa[550], antiComponentCount;
    int find(int x) { return fa[x] ? fa[x] = find(fa[x]) : x; }
    void unite(int x, int y)
    {
        if (find(x) != find(y))
            antiComponentCount++, fa[find(x)] = find(y);
    }
} lft[MAX_N], rig[MAX_N], ans;

int n, m, xi[MAX_N], yi[MAX_N], q;

int main()
{
    scanf("%d%d", &n, &m);
    for (int i = 1; i <= m; i++)
        scanf("%d%d", &xi[i], &yi[i]), lft[i] = lft[i - 1], lft[i].unite(xi[i], yi[i]);
    for (int i = m; i >= 1; i--)
        rig[i] = rig[i + 1], rig[i].unite(xi[i], yi[i]);
    scanf("%d", &q);
    while (q--)
    {
        int l, r;
        scanf("%d%d", &l, &r);
        ans = lft[l - 1];
        for (int i = 1; i <= n; i++)
            if (rig[r + 1].fa[i])
                ans.unite(rig[r + 1].fa[i], i);
        printf("%d\n", n - ans.antiComponentCount);
    }
    return 0;
}