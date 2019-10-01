// P2720.cpp
#include <bits/stdc++.h>

using namespace std;

const int MAX_N = 100100;

int head[MAX_N], n, current, q, tmpx, ptot, roots[MAX_N];

struct node
{
    int sum, lson, rson;
} nodes[MAX_N * 20];

struct edge
{
    int to, nxt;
} edges[MAX_N];

void addpath(int src, int dst)
{
    edges[current].to = dst, edges[current].nxt = head[src];
    head[src] = current++;
}

int update(int qx, int l, int r)
{
    int p = ++ptot;
    nodes[p].sum = 1;
    if (l == r)
        return p;
    int mid = (l + r) >> 1;
    if (qx <= mid)
        nodes[p].lson = update(qx, l, mid);
    else
        nodes[p].rson = update(qx, mid + 1, r);
    return p;
}

int merge(int p1, int p2, int l, int r)
{
    if (p1 == 0)
        return p2;
    if (p2 == 0)
        return p1;
    if (l == r)
    {
        nodes[p1].sum = max(nodes[p1].sum, nodes[p2].sum);
        return p1;
    }
    int mid = (l + r) >> 1;
    nodes[p1].lson = merge(nodes[p1].lson, nodes[p2].lson, l, mid);
    nodes[p1].rson = merge(nodes[p1].rson, nodes[p2].rson, mid + 1, r);
    nodes[p1].sum = nodes[nodes[p1].lson].sum + nodes[nodes[p1].rson].sum;
    return p1;
}

void dfs(int u)
{
    for (int i = head[u]; i != -1; i = edges[i].nxt)
        dfs(edges[i].to), merge(roots[u], roots[edges[i].to], 1, 60000);
}

int main()
{
    memset(head, -1, sizeof(head));
    scanf("%d", &n);
    for (int i = 2, tmp; i <= n; i++)
        scanf("%d", &tmp), addpath(tmp, i);
    for (int i = 1, tmp; i <= n; i++)
        scanf("%d", &tmp), roots[i] = update(tmp, 1, 60000);
    dfs(1), scanf("%d", &q);
    while (q--)
        scanf("%d", &tmpx), printf("%d\n", nodes[roots[tmpx]].sum);
    return 0;
}