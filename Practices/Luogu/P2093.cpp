// P2093.cpp
#include <bits/stdc++.h>

using namespace std;

const int MAX_N = 1e5 + 200;

typedef long long ll;

int n, q, current_frame, groot;

struct node
{
    ll ch[2], d[2], mx[2], mn[2];
    int id;
    bool operator<(const node &rhs) const { return d[current_frame] < rhs.d[current_frame]; }
} nodes[MAX_N];

struct info
{
    ll dist;
    int id;
    bool operator<(const info &rhs) const { return dist > rhs.dist || (dist == rhs.dist && id < rhs.id); }
};

priority_queue<info> pq;

ll maxDist(node &rhs, ll X, ll Y)
{
    return max((rhs.mn[0] - X) * (rhs.mn[0] - X), (rhs.mx[0] - X) * (rhs.mx[0] - X)) +
           max((rhs.mn[1] - Y) * (rhs.mn[1] - Y), (rhs.mx[1] - Y) * (rhs.mx[1] - Y));
}

ll getDist(node &rhs, ll X, ll Y) { return (X - rhs.d[0]) * (X - rhs.d[0]) + (Y - rhs.d[1]) * (Y - rhs.d[1]); }

void pushup(int p)
{
    for (int i = 0; i < 2; i++)
        nodes[p].mx[i] = nodes[p].mn[i] = nodes[p].d[i];
    for (int i = 0; i < 2; i++)
        if (nodes[p].ch[i])
            for (int d = 0; d < 2; d++)
            {
                nodes[p].mn[d] = min(nodes[p].mn[d], nodes[nodes[p].ch[i]].mn[d]);
                nodes[p].mx[d] = max(nodes[p].mx[d], nodes[nodes[p].ch[i]].mx[d]);
            }
}

int build(int l, int r)
{
    if (l > r)
        return 0;
    int mid = (l + r) >> 1;
    nth_element(nodes + l, nodes + mid, nodes + r + 1), current_frame ^= 1;
    nodes[mid].ch[0] = build(l, mid - 1), nodes[mid].ch[1] = build(mid + 1, r);
    current_frame ^= 1, pushup(mid);
    return mid;
}

void query(int p, int x, int y)
{
    if (p == 0)
        return;
    ll res = getDist(nodes[p], x, y);
    if (res > pq.top().dist || (res == pq.top().dist && nodes[p].id < pq.top().id))
        pq.pop(), pq.push(info{res, nodes[p].id});
    int ls = nodes[p].ch[0], rs = nodes[p].ch[1];
    ll lft = 0, rig = 0;
    if (ls)
        lft = maxDist(nodes[ls], x, y);
    if (rs)
        rig = maxDist(nodes[rs], x, y);
    if (lft > rig)
    {
        if (lft >= pq.top().dist)
            query(ls, x, y);
        if (rig >= pq.top().dist)
            query(rs, x, y);
    }
    else
    {
        if (rig >= pq.top().dist)
            query(rs, x, y);
        if (lft >= pq.top().dist)
            query(ls, x, y);
    }
}

int main()
{
    scanf("%d", &n);
    for (int i = 1; i <= n; i++)
        scanf("%lld%lld", &nodes[i].d[0], &nodes[i].d[1]), nodes[i].id = i;
    groot = build(1, n), scanf("%d", &q);
    while (q--)
    {
        int x, y, k;
        scanf("%d%d%d", &x, &y, &k);
        while (!pq.empty())
            pq.pop();
        for (int i = 1; i <= k; i++)
            pq.push(info{-1, 0});
        query(groot, x, y), printf("%d\n", pq.top().id);
    }
    return 0;
}