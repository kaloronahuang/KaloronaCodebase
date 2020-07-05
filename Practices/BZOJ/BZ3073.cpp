// BZ3073.cpp
#include <bits/stdc++.h>

using namespace std;

const int MAX_N = 5e5 + 200, MAX_NODE = MAX_N * 9 + 1e5, MAX_E = 2e5 * 4 * 18 + MAX_NODE;

typedef pair<int, int> pii;

int n, m, head[MAX_NODE], current, ptot, start_pos, roots[2], dist[MAX_NODE];
bool vis[MAX_NODE];

struct node
{
    int lson, rson;
} nodes[MAX_NODE];

struct edge
{
    int to, nxt, weight;
} edges[MAX_E];

void addpath(int src, int dst, int weight, int opt)
{
    if (opt)
        swap(src, dst);
    edges[current].to = dst, edges[current].weight = weight;
    edges[current].nxt = head[src], head[src] = current++;
}

#define mid ((l + r) >> 1)

int build(int l, int r, int opt)
{
    int p = ++ptot;
    if (l == r)
        return addpath(p, l, 0, opt), p;
    addpath(p, nodes[p].lson = build(l, mid, opt), 0, opt);
    addpath(p, nodes[p].rson = build(mid + 1, r, opt), 0, opt);
    return p;
}

void connect(int ql, int qr, int l, int r, int src, int p, int weight, int opt)
{
    if (ql <= l && r <= qr)
        return (void)(addpath(src, p, weight, opt));
    if (ql <= mid)
        connect(ql, qr, l, mid, src, nodes[p].lson, weight, opt);
    if (mid < qr)
        connect(ql, qr, mid + 1, r, src, nodes[p].rson, weight, opt);
}

int main()
{
    memset(head, -1, sizeof(head));
    scanf("%d%d%d", &n, &m, &start_pos), ptot = n;
    for (int i = 0; i < 2; i++)
        roots[i] = build(1, n, i);
    while (m--)
    {
        int a, b, c, d;
        scanf("%d%d%d%d", &a, &b, &c, &d);
        int transfer = ++ptot;
        connect(a, b, 1, n, transfer, roots[1], 0, 1);
        connect(c, d, 1, n, transfer, roots[0], 1, 0);
        swap(a, c), swap(b, d), transfer = ++ptot;
        connect(a, b, 1, n, transfer, roots[1], 0, 1);
        connect(c, d, 1, n, transfer, roots[0], 1, 0);
    }
    memset(dist, 0x3f, sizeof(dist));
    priority_queue<pii> pq;
    pq.push(make_pair(0, start_pos)), dist[start_pos] = 0;
    while (!pq.empty())
    {
        int u = pq.top().second;
        pq.pop();
        if (vis[u])
            continue;
        vis[u] = true;
        for (int i = head[u]; i != -1; i = edges[i].nxt)
            if (dist[edges[i].to] > dist[u] + edges[i].weight)
                dist[edges[i].to] = dist[u] + edges[i].weight, pq.push(make_pair(-dist[edges[i].to], edges[i].to));
    }
    for (int i = 1; i <= n; i++)
        printf("%d\n", dist[i]);
    return 0;
}