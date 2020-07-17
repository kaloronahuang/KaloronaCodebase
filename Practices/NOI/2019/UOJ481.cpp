// UOJ481.cpp
#include <bits/stdc++.h>

using namespace std;

const int MAX_N = 7e4 + 200, MAX_E = 1.5e5 + 200;

typedef pair<int, int> pii;

int n, m, w, h, xi[MAX_N], yi[MAX_N], head[MAX_N], current, dist[MAX_N];
bool vis[MAX_N];
multiset<pii> nodes[MAX_N << 2];
priority_queue<pii> pq;

struct edge
{
    int src, weight, l, r, d, u, nxt;
} edges[MAX_E << 1];

void addpath()
{
    scanf("%d%d%d%d%d%d", &edges[current].src, &edges[current].weight,
          &edges[current].l, &edges[current].r, &edges[current].d, &edges[current].u);
    edges[current].nxt = head[edges[current].src], head[edges[current].src] = current;
    current++;
}

#define lson (p << 1)
#define rson ((p << 1) | 1)
#define mid ((l + r) >> 1)

void insert(int qx, int qy, int l, int r, int p, int idx)
{
    nodes[p].insert(make_pair(qy, idx));
    if (l == r)
        return;
    if (qx <= mid)
        insert(qx, qy, l, mid, lson, idx);
    else
        insert(qx, qy, mid + 1, r, rson, idx);
}

void remove(int eid, int l, int r, int p, int cd)
{
    if (edges[eid].l <= l && r <= edges[eid].r)
    {
        auto x = nodes[p].lower_bound(make_pair(edges[eid].d, 0));
        while (x != nodes[p].end() && x->first <= edges[eid].u)
        {
            int u = x->second;
            if (!vis[u])
            {
                vis[u] = true, dist[u] = cd;
                for (int i = head[u]; i != -1; i = edges[i].nxt)
                    pq.push(make_pair(-(cd + edges[i].weight), i));
            }
            auto tmp = x;
            x++, nodes[p].erase(tmp);
        }
        return;
    }
    if (edges[eid].l <= mid)
        remove(eid, l, mid, lson, cd);
    if (mid < edges[eid].r)
        remove(eid, mid + 1, r, rson, cd);
}

int main()
{
    memset(head, -1, sizeof(head));
    scanf("%d%d%d%d", &n, &m, &w, &h);
    for (int i = 1; i <= n; i++)
    {
        scanf("%d%d", &xi[i], &yi[i]);
        insert(xi[i], yi[i], 1, w, 1, i);
    }
    for (int i = 1; i <= m; i++)
        addpath();
    vis[1] = true;
    for (int i = head[1]; i != -1; i = edges[i].nxt)
        pq.push(make_pair(-edges[i].weight, i));
    while (!pq.empty())
    {
        pii u = pq.top();
        pq.pop(), remove(u.second, 1, w, 1, -u.first);
    }
    for (int i = 2; i <= n; i++)
        printf("%d\n", dist[i]);
    return 0;
}