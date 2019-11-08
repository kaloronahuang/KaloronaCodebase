// B.cpp
#include <bits/stdc++.h>
typedef long long ll;
#define pr pair<ll, int>

using namespace std;

const int MAX_N = 5e4 + 200, MAX_E = 2e5 + 200;

struct edge
{
    int from, to, weight, nxt;
} edges[MAX_E << 1], org[40];

int n, m, limit, pts[30], head[MAX_N], current, ptot, tag[MAX_N];
ll dists[30][MAX_N], dp[1 << 12][30][2], *dist;
bool vis[MAX_N];

inline char nc()
{
    static char buf[100000], *p1 = buf, *p2 = buf;
    return p1 == p2 && (p2 = (p1 = buf) + fread(buf, 1, 100000, stdin), p1 == p2) ? EOF : *p1++;
}

int read()
{
    int x = 0, f = 1;
    char ch = nc();
    while (!isdigit(ch))
    {
        if (ch == '-')
            f = -1;
        ch = nc();
    }
    while (isdigit(ch))
        x = (x << 3) + (x << 1) + ch - '0', ch = nc();
    return x * f;
}

void addpath(int src, int dst, int weight)
{
    edges[++current].to = dst, edges[current].nxt = head[src];
    edges[current].weight = weight, head[src] = current;
}

inline void shortest_path(int src, bool traditional = false)
{
    memset(vis, false, sizeof(vis));
    priority_queue<pr> pq;
    int idx = tag[src];
    if (traditional)
        idx = 0;
    memset(dists[idx], 0x3f, sizeof(dists[idx]));
    dist = dists[idx];
    pq.push(make_pair(0, src)), dist[src] = 0;
    while (!pq.empty())
    {
        int u = pq.top().second;
        pq.pop();
        if (vis[u])
            continue;
        vis[u] = true;
        for (int i = head[u]; i; i = edges[i].nxt)
            if (dist[edges[i].to] > dist[u] + edges[i].weight)
                dist[edges[i].to] = dist[u] + edges[i].weight, pq.push(make_pair(-dist[edges[i].to], edges[i].to));
    }
}

int main()
{
    memset(dp, 0x3f, sizeof(dp));
    freopen("test.in", "r", stdin);
    n = read(), m = read(), limit = read();
    for (int i = 1, u, v, w; i <= limit; i++)
    {
        u = read(), v = read(), w = read(), addpath(u, v, w), addpath(v, u, w);
        pts[++ptot] = u, tag[u] = ptot;
        pts[++ptot] = v, tag[v] = ptot;
        org[i] = edge{u, v, w, 0};
    }
    for (int i = limit + 1, u, v, w; i <= m; i++)
        u = read(), v = read(), w = read(), addpath(u, v, w), addpath(v, u, w);
    shortest_path(1, true);
    for (int i = 1; i <= ptot; i++)
        shortest_path(pts[i]);
    for (int i = 1; i <= limit; i++)
    {
        dp[1 << (i - 1)][i][0] = dists[0][org[i].from] + org[i].weight;
        dp[1 << (i - 1)][i][1] = dists[0][org[i].to] + org[i].weight;
    }
    for (int stat = 1; stat < (1 << limit); stat++)
    {
        if (__builtin_popcount(stat) == 1)
            continue;
        for (int i = 1; i <= limit; i++)
            if (stat & (1 << (i - 1)))
            {
                // from this side;
                // dp[stat][i][0] && dp[stat][i][1];
                for (int j = 1; j <= limit; j++)
                    if (i != j && (stat & (1 << (j - 1))))
                    {
                        dp[stat][i][0] = min(dp[stat][i][0], dp[stat ^ (1 << (i - 1))][j][0] + dists[tag[org[j].to]][org[i].from] + org[i].weight);
                        dp[stat][i][0] = min(dp[stat][i][0], dp[stat ^ (1 << (i - 1))][j][1] + dists[tag[org[j].from]][org[i].from] + org[i].weight);
                        dp[stat][i][1] = min(dp[stat][i][1], dp[stat ^ (1 << (i - 1))][j][0] + dists[tag[org[j].to]][org[i].to] + org[i].weight);
                        dp[stat][i][1] = min(dp[stat][i][1], dp[stat ^ (1 << (i - 1))][j][1] + dists[tag[org[j].from]][org[i].to] + org[i].weight);
                    }
            }
    }
    ll ans = 0x3f3f3f3f3f3f3f3f;
    for (int i = 1; i <= limit; i++)
    {
        ans = min(ans, dp[(1 << limit) - 1][i][0] + dists[0][org[i].to]);
        ans = min(ans, dp[(1 << limit) - 1][i][1] + dists[0][org[i].from]);
    }
    printf("%lld", ans);
    return 0;
}