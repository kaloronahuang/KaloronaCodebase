// P3588.cpp
#include <bits/stdc++.h>

using namespace std;

const int MAX_N = 6e5 + 200, MAX_E = 8e6 + 200;

int n, s, m, dp[MAX_N], head[MAX_N], current, sidx[MAX_N], ptot, deg[MAX_N], topoidx[MAX_N], topotot;
bool isFixed[MAX_N];

struct edge
{
    int to, nxt, weight;
} edges[MAX_E];

void addpath(int src, int dst, int weight)
{
    edges[current].to = dst, edges[current].nxt = head[src];
    edges[current].weight = weight, head[src] = current++, deg[dst]++;
}

#define lson (p << 1)
#define rson ((p << 1) | 1)
#define mid ((l + r) >> 1)

void build(int l, int r, int p)
{
    ptot = max(ptot, p);
    if (l == r)
        return (void)(sidx[l] = p);
    addpath(p, lson, 0), addpath(p, rson, 0);
    build(l, mid, lson), build(mid + 1, r, rson);
}

void update(int ql, int qr, int l, int r, int p, int src)
{
    if (ql > qr)
        return;
    if (ql <= l && r <= qr)
        return (void)(addpath(src, p, 0));
    if (ql <= mid)
        update(ql, qr, l, mid, lson, src);
    if (mid < qr)
        update(ql, qr, mid + 1, r, rson, src);
}

#undef mid
#undef rson
#undef lson

int main()
{
    memset(head, -1, sizeof(head));
    scanf("%d%d%d", &n, &s, &m), build(1, n, 1);
    for (int i = 1; i <= n; i++)
        dp[sidx[i]] = 1;
    for (int i = 1, p, d; i <= s; i++)
        scanf("%d%d", &p, &d), dp[sidx[p]] = d, isFixed[sidx[p]] = true;
    while (m--)
    {
        int l, r, k, cpt, last = l - 1;
        scanf("%d%d%d", &l, &r, &k), cpt = ++ptot, last = l - 1;
        for (int i = 1, pt; i <= k; i++)
            scanf("%d", &pt), addpath(sidx[pt], cpt, 1), update(last + 1, pt - 1, 1, n, 1, cpt), last = pt;
        update(last + 1, r, 1, n, 1, cpt);
    }
    queue<int> q;
    for (int i = 1; i <= ptot; i++)
        if (deg[i] == 0)
            q.push(i);
    while (!q.empty())
    {
        int u = q.front();
        q.pop(), topoidx[++topotot] = u;
        for (int i = head[u]; i != -1; i = edges[i].nxt)
            if (--deg[edges[i].to] == 0)
                q.push(edges[i].to);
    }
    for (int i = 1; i <= ptot; i++)
        if (deg[i] != 0)
            puts("NIE"), exit(0);
    for (int id = ptot; id >= 1; id--)
    {
        int u = topoidx[id], max_val = 1;
        for (int i = head[u]; i != -1; i = edges[i].nxt)
            max_val = max(max_val, dp[edges[i].to] + edges[i].weight);
        if (isFixed[u] && max_val > dp[u])
            puts("NIE"), exit(0);
        else if (!isFixed[u])
            dp[u] = max_val;
    }
    for (int i = 1; i <= n; i++)
        if (dp[sidx[i]] > 1e9 || dp[sidx[i]] < 1)
            puts("NIE"), exit(0);
    puts("TAK");
    for (int i = 1; i <= n; i++)
        printf("%d%c", dp[sidx[i]], " \n"[i == n]);
    return 0;
}