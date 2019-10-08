// P1772.cpp
#include <bits/stdc++.h>
#define ll long long
#define pr pair<ll, int>

using namespace std;

const int MAX_N = 110;
const ll INF = 0x3f3f3f3f3f3f3f3f;

int head[MAX_N], current, T, n, m, K, tmp;
ll dist[MAX_N], dp[MAX_N];
bool vis[MAX_N], tag[MAX_N], AVAILABILITY[MAX_N][MAX_N];

struct edge
{
    int to, nxt, weight;
} edges[MAX_N * 20];

void addpath(int src, int dst, int weight)
{
    edges[current].to = dst, edges[current].nxt = head[src];
    edges[current].weight = weight, head[src] = current++;
}

void shortest_path()
{
    memset(dist, 0x3f, sizeof(dist));
    memset(vis, false, sizeof(vis));
    priority_queue<pr> pq;
    pq.push(make_pair(0, 1)), dist[1] = 0;
    while (!pq.empty())
    {
        int u = pq.top().second;
        pq.pop();
        if (vis[u])
            continue;
        vis[u] = true;
        for (int i = head[u]; i != -1; i = edges[i].nxt)
            if (dist[edges[i].to] > dist[u] + edges[i].weight && tag[edges[i].to] == false)
                dist[edges[i].to] = dist[u] + edges[i].weight, pq.push(make_pair(-dist[edges[i].to], edges[i].to));
    }
}

int main()
{
    memset(head, -1, sizeof(head));
    scanf("%d%d%d%d", &T, &n, &K, &m);
    for (int i = 1, u, v, w; i <= m; i++)
        scanf("%d%d%d", &u, &v, &w), addpath(u, v, w), addpath(v, u, w);
    scanf("%d", &tmp);
    while (tmp--)
    {
        int l, r, pt;
        scanf("%d%d%d", &pt, &l, &r);
        for (int i = l; i <= r; i++)
            AVAILABILITY[pt][i] = true;
    }
    memset(dp, 0x3f, sizeof(dp));
    shortest_path(), dp[0] = -K;
    for (int i = 1; i <= T; i++)
    {
        memset(tag, false, sizeof(tag));
        for (int j = i; j >= 1; j--)
        {
            for (int k = 1; k <= n; k++)
                tag[k] |= AVAILABILITY[k][j];
            shortest_path();
            if (dist[n] >= INF)
                continue;
            dp[i] = min(dp[i], dp[j - 1] + K + 1LL * dist[n] * (i - j + 1));
        }
    }
    printf("%d", dp[T]);
    return 0;
}