// classroom.cpp
#include <bits/stdc++.h>
#define ll long long
#define pr pair<ll, int>

using namespace std;

const int MAX_N = 7e5 + 200, MAX_E = 1e6 + 200;

int head[MAX_N], n, m, current, ptot, ufs[MAX_N], fa[21][MAX_N], level[MAX_N], T;
ll dist[MAX_N], val[MAX_N];
int Q, K, S;
bool vis[MAX_N];

inline int read()
{
    int X = 0, w = 0;
    char ch = 0;
    while (!isdigit(ch))
    {
        w |= ch == '-';
        ch = getchar();
    }
    while (isdigit(ch))
        X = (X << 3) + (X << 1) + (ch ^ 48), ch = getchar();
    return w ? -X : X;
}

struct edge
{
    int from, to, nxt, weight, level;
    bool operator<(const edge &target) const { return level > target.level; }
} edges[MAX_E], org[MAX_E];

int find(int x) { return x == ufs[x] ? x : ufs[x] = find(ufs[x]); }

void addpath(int src, int dst, int weight, int level)
{
    edges[current].to = dst, edges[current].weight = weight;
    edges[current].nxt = head[src], edges[current].level = level;
    head[src] = current++;
}

void shortest_path(int st)
{
    memset(dist, 0x3f, sizeof(dist));
    memset(vis, false, sizeof(vis));
    priority_queue<pr> pq;
    while (!pq.empty())
        pq.pop();
    dist[st] = 0, pq.push(make_pair(0, st));
    while (!pq.empty())
    {
        int u = pq.top().second;
        pq.pop();
        if (vis[u])
            continue;
        vis[u] = true;
        for (int i = head[u]; i != -1; i = edges[i].nxt)
            if (dist[edges[i].to] > dist[u] + edges[i].weight)
            {
                dist[edges[i].to] = dist[u] + edges[i].weight;
                pq.push(make_pair(-dist[edges[i].to], edges[i].to));
            }
    }
}

void kruskal()
{
    memset(fa, 0, sizeof(fa)), memset(val, 0x3f, sizeof(val));
    memset(head, -1, sizeof(head)), memset(level, 0, sizeof(level));
    current = 0, ptot = n;
    sort(org + 1, org + 1 + m);
    for (int i = 1; i <= n; i++)
        val[i] = dist[i];
    for (int i = 1; i <= (n + m); i++)
        ufs[i] = i;
    for (int i = 1; i <= m; i++)
    {
        edge curt = org[i];
        int fx = find(curt.from), fy = find(curt.to);
        int p = ++ptot;
        fa[0][fx] = p, fa[0][fy] = p;
        ufs[fx] = ufs[fy] = p;
        val[p] = min(val[fx], val[fy]);
        level[p] = curt.level;
        if (level[fx] == 0)
            level[fx] = curt.level;
        if (level[fy] == 0)
            level[fy] = curt.level;
        continue;
    }
    for (int i = 1; i < 20; i++)
        for (int j = 1; j <= ptot; j++)
            fa[i][j] = fa[i - 1][fa[i - 1][j]];
}

int query(int x, int limit)
{
    ll ans = dist[x];
    int p = x;
    for (int i = 19; i >= 0; i--)
        if (level[fa[i][p]] > limit)
            p = fa[i][p], ans = min(ans, val[p]);
    return ans;
}

int main()
{
    freopen("classroom.in", "r", stdin);
    freopen("classroom.out", "w", stdout);
    T = read();
    while (T--)
    {
        memset(head, -1, sizeof(head)), current = 0;
        n = read(), m = read();
        for (int i = 1, u, v, l, a; i <= m; i++)
        {
            u = read(), v = read(), l = read(), a = read();
            addpath(u, v, l, a), addpath(v, u, l, a);
            org[i] = {u, v, 0, l, a};
        }
        shortest_path(1), kruskal();
        ll lastans = 0;
        Q = read(), K = read(), S = read();
        while (Q--)
        {
            int v = read(), p = read();
            v = (v + K * lastans - 1) % n + 1;
            p = (p + K * lastans) % (S + 1);
            printf("%lld\n", lastans = query(v, p));
        }
    }
    return 0;
}