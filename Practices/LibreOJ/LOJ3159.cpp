// LOJ3159.cpp
#include <bits/stdc++.h>

using namespace std;

const int MAX_N = 7e4 + 20, MAX_M = 1.5e5 + 20;

typedef pair<int, int> pii;
typedef multiset<pii>::iterator mit;

int n, m, w, h, pi[MAX_M], ti[MAX_M], li[MAX_M], ri[MAX_M], di[MAX_M], ui[MAX_M];
int head[MAX_M], nxt[MAX_M], dist[MAX_N];
pii cities[MAX_N];
bool vis[MAX_N];
multiset<pii> nodes[MAX_N << 2];
priority_queue<pii> pq;

void fileIO()
{
    freopen("jump.in", "r", stdin);
    freopen("jump.out", "w", stdout);
}

#define lson (p << 1)
#define rson ((p << 1) | 1)
#define mid ((l + r) >> 1)

void insert(int qx, int l, int r, int p, int id)
{
    nodes[p].insert(make_pair(cities[id].second, id));
    if (l == r)
        return;
    if (qx <= mid)
        insert(qx, l, mid, lson, id);
    else
        insert(qx, mid + 1, r, rson, id);
}

void remove(int l, int r, int p, int id, int d)
{
    if (li[id] <= l && r <= ri[id])
    {
        mit it = nodes[p].lower_bound(make_pair(di[id], 0)), tmp;
        while (it != nodes[p].end() && it->first <= ui[id])
        {
            int u = it->second;
            if (!vis[u])
            {
                vis[u] = true, dist[u] = d;
                for (int i = head[u]; i != 0; i = nxt[i])
                    pq.push(make_pair(-d - ti[i], i));
            }
            tmp = it, it++, nodes[p].erase(tmp);
        }
        return;
    }
    if (li[id] <= mid)
        remove(l, mid, lson, id, d);
    if (mid < ri[id])
        remove(mid + 1, r, rson, id, d);
}

#undef mid
#undef rson
#undef lson

int main()
{
    fileIO();
    scanf("%d%d%d%d", &n, &m, &w, &h);
    for (int i = 1; i <= n; i++)
    {
        scanf("%d%d", &cities[i].first, &cities[i].second);
        insert(cities[i].first, 1, w, 1, i);
    }
    for (int i = 1; i <= m; i++)
        scanf("%d%d%d%d%d%d", &pi[i], &ti[i], &li[i], &ri[i], &di[i], &ui[i]), nxt[i] = head[pi[i]], head[pi[i]] = i;
    dist[1] = 0, vis[1] = true;
    for (int i = head[1]; i != 0; i = nxt[i])
        pq.push(make_pair(-ti[i], i));
    while (!pq.empty())
    {
        pii curt = pq.top();
        pq.pop();
        remove(1, w, 1, curt.second, -curt.first);
    }
    for (int i = 2; i <= n; i++)
        printf("%d\n", dist[i]);
    return 0;
}