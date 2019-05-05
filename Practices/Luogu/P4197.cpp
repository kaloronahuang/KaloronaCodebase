// P4197.cpp
#include <bits/stdc++.h>
using namespace std;

const int MAX_N = 2e5 + 5, MAX_M = 5e5 + 5, MAX_T = 20 * MAX_N;

int head[MAX_N], current, fa[20][MAX_N], tot, n, m, q, hi[MAX_N], tmpx, tmpy, tmpz;
int buff[MAX_N], tmp[MAX_N], limit, pval[MAX_N], lft[MAX_N], rig[MAX_N], dfn;
int sum[MAX_T], lson[MAX_T], rson[MAX_T], roots[MAX_N], ttot;
struct edge
{
    int from, to, weight, nxt;
    bool operator<(const edge &e) const { return weight < e.weight; }
} G[MAX_M], edges[MAX_N];

void addpath(int src, int dst, int weight)
{
    edges[current].to = dst, edges[current].nxt = head[src];
    edges[current].from = src, edges[current].weight = weight;
    head[src] = current++;
}

int find(int x) { return (buff[x] == x) ? x : buff[x] = find(buff[x]); }

int update(int qx, int l, int r, int pre)
{
    int p = ++ttot;
    sum[p] = sum[pre] + 1;
    if (l == r)
        return p;
    int mid = (l + r) >> 1;
    rson[p] = rson[pre], lson[p] = lson[pre];
    if (qx <= mid)
        lson[p] = update(qx, l, mid, lson[pre]);
    else
        rson[p] = update(qx, mid + 1, r, rson[pre]);
    return p;
}

int query(int a, int x, int k)
{
    int l = 1, r = limit;
    for (int i = 19; i >= 0; i--)
        if (fa[i][a] != 0 && pval[fa[i][a]] <= x)
            a = fa[i][a];
    int v = roots[rig[a]], u = roots[lft[a] - 1];
    if (sum[v] - sum[u] < k)
        return -1;
    while (l < r)
    {
        int tp = sum[rson[v]] - sum[rson[u]], mid = (l + r) >> 1;
        if (tp >= k)
            v = rson[v], u = rson[u], l = mid + 1;
        else
            v = lson[v], u = lson[u], r = mid, k -= tp;
    }
    return tmp[r];
}

void dfs(int u)
{
    for (int i = 1; i < 20; i++)
        fa[i][u] = fa[i - 1][fa[i - 1][u]];
    lft[u] = ++tot;
    if (u <= n)
        roots[tot] = update(hi[u], 1, limit, roots[tot - 1]);
    else
        roots[tot] = roots[tot - 1];
    for (int i = head[u]; i != -1; i = edges[i].nxt)
        dfs(edges[i].to);
    rig[u] = tot;
}

int main()
{
    memset(head, -1, sizeof(head));
    scanf("%d%d%d", &n, &m, &q);

    for (int i = 1; i <= 2 * n; i++)
        buff[i] = i;

    for (int i = 1; i <= n; i++)
        scanf("%d", &hi[i]), tmp[i] = hi[i];
    for (int i = 1; i <= m; i++)
        scanf("%d%d%d", &tmpx, &tmpy, &tmpz), G[i] = edge{tmpx, tmpy, tmpz, -1};

    sort(tmp + 1, tmp + 1 + n), limit = unique(tmp + 1, tmp + 1 + n) - tmp - 1;
    for (int i = 1; i <= n; i++)
        hi[i] = lower_bound(tmp + 1, tmp + 1 + limit, hi[i]) - tmp;

    dfn = n, sort(G + 1, G + 1 + m);

    for (int i = 1; i <= m; i++)
    {
        int a = find(G[i].from), b = find(G[i].to);
        if (a != b)
        {
            pval[++dfn] = G[i].weight, buff[a] = buff[b] = dfn;
            addpath(dfn, a, 0), addpath(dfn, b, 0);
            fa[0][a] = fa[0][b] = dfn;
            if (dfn - n == n - 1)
                break;
        }
    }

    for (int i = 1; i <= dfn; i++)
        if (lft[i] == 0)
            dfs(find(i));

    while (q--)
    {
        int v, x, k;
        scanf("%d%d%d", &v, &x, &k), printf("%d\n", query(v, x, k));
    }
    return 0;
}