#include <iostream>
#include <cmath>

using namespace std;

void build(int u, int f)
{
    dep[u] = dep[f] + 1;
    dfq[++dfn] = u;
    pos[u] = dfn;
    for (int i = head[u]; i; i = l[i].next)
    {
        int v = l[i].to;
        if (v == f)
            continue;
        build(v, u);
        dfq[++dfn] = u;
    }
}
void init()
{
    for (int i = 1; i <= dfn; i++)
        lca[i][0] = dfq[i];
    for (int j = 1; j < 20; j++)
        for (int i = 1; i <= dfn; i++)
        {
            if (i + (1 << j) - 1 <= dfn)
            {
                if (dep[lca[i][j - 1]] < dep[lca[i + (1 << (j - 1))][j - 1]])
                    lca[i][j] = lca[i][j - 1];
                else
                    lca[i][j] = lca[i + (1 << (j - 1))][j - 1];
            }
        }
}
int getlca(int x, int y)
{
    int l = pos[x], r = pos[y];
    if (l > r)
        swap(l, r);
    int k = log(r - l + 1.0) / log(2.0);
    if (dep[lca[l][k]] < dep[lca[r - (1 << k) + 1][k]])
        return lca[l][k];
    return lca[r - (1 << k) + 1][k];
}