// escape.cpp
#include <bits/stdc++.h>

using namespace std;

const int MAX_N = 2e5 + 200;

int n, head[MAX_N], current, roots[MAX_N], lft[MAX_N], rig[MAX_N];
int ptot, stot, dep[MAX_N], ai[MAX_N], dp[MAX_N];

struct edge
{
    int to, nxt;
} edges[MAX_N << 1];

struct node
{
    int lson, rson, sum;
} nodes[MAX_N * 30];

#define mid ((l + r) >> 1)

void addpath(int src, int dst)
{
    edges[current].to = dst, edges[current].nxt = head[src];
    head[src] = current++;
}

int update(int qx, int l, int r, int pre, int val)
{
    int p = ++ptot;
    nodes[p] = nodes[pre], nodes[p].sum += val;
    if (l == r)
        return p;
    if (qx <= mid)
        nodes[p].lson = update(qx, l, mid, nodes[pre].lson, val);
    else
        nodes[p].rson = update(qx, mid + 1, r, nodes[pre].rson, val);
    return p;
}

int query(int ql, int qr, int l, int r, int p, int pre)
{
    if (p == 0)
        return 0;
    if (ql <= l && r <= qr)
        return nodes[p].sum - nodes[pre].sum;
    int ret = 0;
    if (ql <= mid)
        ret += query(ql, qr, l, mid, nodes[p].lson, nodes[pre].lson);
    if (mid < qr)
        ret += query(ql, qr, mid + 1, r, nodes[p].rson, nodes[pre].rson);
    return ret;
}

void dfs(int u, int fa)
{
    lft[u] = ++stot, dep[u] = dep[fa] + 1;
    roots[stot] = update(dep[u], 1, n, roots[stot - 1], ai[u]);
    for (int i = head[u]; i != -1; i = edges[i].nxt)
        if (edges[i].to != fa)
            dfs(edges[i].to, u);
    rig[u] = stot;
}

void collect(int u, int fa)
{
    dp[u] = dp[fa] + query(max(1, dep[u] * 2 - 2), min(n, dep[u] * 2 - 1), 1, n, roots[rig[u]], roots[lft[u] - 1]);
    for (int i = head[u]; i != -1; i = edges[i].nxt)
        if (edges[i].to != fa)
            collect(edges[i].to, u);
}

int main()
{
    memset(head, -1, sizeof(head));
    scanf("%d", &n);
    for (int i = 1; i <= n; i++)
        scanf("%d", &ai[i]);
    for (int i = 1, u, v; i <= n - 1; i++)
        scanf("%d%d", &u, &v), addpath(u, v), addpath(v, u);
    dfs(1, 0), collect(1, 0);
    for (int i = 1; i <= n; i++)
        printf("%d\n", dp[i]);
    return 0;
}