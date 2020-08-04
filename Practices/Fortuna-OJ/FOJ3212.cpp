// FOJ3212.cpp
#include <bits/stdc++.h>
using namespace std;

const int MAX_N = 8e4 + 20;

int head[MAX_N], current, fa[20][MAX_N], val[MAX_N], bucket[MAX_N];
int testcase, n, m, t, bucketTot, siz[MAX_N], dep[MAX_N], buff[MAX_N];
bool vis[MAX_N];
char opt[20];
struct edge
{
    int to, nxt;
} edges[MAX_N << 1];

struct node
{
    int sum, lson, rson;
} nodes[80001 * 540];

int treeTot, roots[MAX_N];

int find(int x) { return x == buff[x] ? x : buff[x] = find(buff[x]); }

void addpath(int src, int dst)
{
    edges[current].to = dst, edges[current].nxt = head[src];
    head[src] = current++;
}

int build(int l, int r)
{
    int p = ++treeTot;
    nodes[p].sum = 0;
    if (l == r)
        return p;
    int mid = (l + r) >> 1;
    nodes[p].lson = build(l, mid), nodes[p].rson = build(mid + 1, r);
    return p;
}

int update(int qx, int l, int r, int pre, int val)
{
    int p = ++treeTot;
    nodes[p].sum = nodes[pre].sum + val;
    nodes[p].lson = nodes[pre].lson, nodes[p].rson = nodes[pre].rson;
    if (l == r)
        return p;
    int mid = (l + r) >> 1;
    if (qx <= mid)
        nodes[p].lson = update(qx, l, mid, nodes[pre].lson, val);
    else
        nodes[p].rson = update(qx, mid + 1, r, nodes[pre].rson, val);
    return p;
}

void dfs(int u, int fat, int top)
{
    fa[0][u] = fat;
    for (int i = 1; i < 20; i++)
        fa[i][u] = fa[i - 1][fa[i - 1][u]];
    buff[u] = fat;
    siz[top]++, dep[u] = dep[fat] + 1;
    vis[u] = true, roots[u] = update(val[u], 1, bucketTot, roots[fat], 1);
    for (int i = head[u]; i != -1; i = edges[i].nxt)
        if (edges[i].to != fat)
            dfs(edges[i].to, u, top);
}

int getLCA(int x, int y)
{
    if (dep[x] < dep[y])
        swap(x, y);
    for (int i = 19; i >= 0; i--)
        if (dep[fa[i][x]] >= dep[y])
            x = fa[i][x];
    if (x == y)
        return x;
    for (int i = 19; i >= 0; i--)
        if (fa[i][x] != fa[i][y])
            x = fa[i][x], y = fa[i][y];
    return fa[0][x];
}

int query(int ptr1, int ptr2, int pre1, int pre2, int l, int r, int k)
{
    if (l == r)
        return bucket[l];
    int lson_siz = nodes[nodes[ptr1].lson].sum + nodes[nodes[ptr2].lson].sum;
    lson_siz -= nodes[nodes[pre1].lson].sum + nodes[nodes[pre2].lson].sum;
    int mid = (l + r) >> 1;
    if (k <= lson_siz)
        return query(nodes[ptr1].lson, nodes[ptr2].lson, nodes[pre1].lson, nodes[pre2].lson, l, mid, k);
    else
        return query(nodes[ptr1].rson, nodes[ptr2].rson, nodes[pre1].rson, nodes[pre2].rson, mid + 1, r, k - lson_siz);
}

int main()
{
    memset(head, -1, sizeof(head));
    scanf("%d%d%d%d", &testcase, &n, &m, &t);
    for (int i = 1; i <= n; i++)
        scanf("%d", &val[i]), bucket[i] = val[i];
    sort(bucket + 1, bucket + 1 + n), bucketTot = unique(bucket + 1, bucket + 1 + n) - bucket - 1;
    for (int i = 1; i <= n; i++)
        val[i] = lower_bound(bucket + 1, bucket + 1 + bucketTot, val[i]) - bucket;
    for (int i = 1, u, v; i <= m; i++)
        scanf("%d%d", &u, &v), addpath(u, v), addpath(v, u);
    roots[0] = build(1, bucketTot);
    for (int i = 1; i <= n; i++)
        if (!vis[i])
            dfs(i, 0, i), buff[i] = i;
    int lastans = 0, x, y, k;
    while (t--)
    {
        scanf("%s%d%d", opt, &x, &y);
        x ^= lastans, y ^= lastans;
        if (opt[0] == 'Q')
        {
            scanf("%d", &k), k ^= lastans;
            int lca = getLCA(x, y);
            lastans = query(roots[x], roots[y], roots[lca], roots[fa[0][lca]], 1, bucketTot, k);
            printf("%d\n", lastans);
        }
        else
        {
            addpath(x, y), addpath(y, x);
            int rt_x = find(x), rt_y = find(y);
            if (siz[rt_x] < siz[rt_y])
                swap(rt_x, rt_y);
            dfs(y, x, rt_x);
        }
    }
    return 0;
}