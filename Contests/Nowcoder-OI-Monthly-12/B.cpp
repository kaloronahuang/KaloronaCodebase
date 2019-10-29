// B.cpp
#include <bits/stdc++.h>
#define ll long long
#define pr pair<int, int>

using namespace std;

const int MAX_N = 1010;

int dist[MAX_N][MAX_N], head[MAX_N], current, n, m, ai[MAX_N], bi[MAX_N], atot, btot;
ll dp[MAX_N][MAX_N][2];
bool vis[MAX_N];

struct edge
{
    int to, nxt, weight;
} edges[MAX_N * 20];

void addpath(int src, int dst, int weight)
{
    edges[current].to = dst, edges[current].nxt = head[src];
    edges[current].weight = weight, head[src] = current++;
}

void shortest_path(int src)
{
    memset(dist[src], 0x3f, sizeof(dist[src]));
    memset(vis, false, sizeof(vis)), dist[src][0] = 0;
    priority_queue<pr> pq;
    pq.push(make_pair(0, src)), dist[src][src] = 0;
    while (!pq.empty())
    {
        int u = pq.top().second;
        pq.pop();
        if (vis[u])
            continue;
        vis[u] = true;
        for (int i = head[u]; i != -1; i = edges[i].nxt)
            if (dist[src][edges[i].to] > dist[src][u] + edges[i].weight)
                dist[src][edges[i].to] = dist[src][u] + edges[i].weight, pq.push(make_pair(-dist[src][edges[i].to], edges[i].to));
    }
}

int main()
{
    memset(head, -1, sizeof(head));
    scanf("%d%d", &n, &m);
    for (int i = 1, u, v, w; i <= m; i++)
        scanf("%d%d%d", &u, &v, &w), addpath(u, v, w), addpath(v, u, w);
    for (int i = 1; i <= n; i++)
        shortest_path(i);
    scanf("%d", &atot);
    for (int i = 1; i <= atot; i++)
        scanf("%d", &ai[i]);
    scanf("%d", &btot);
    for (int i = 1; i <= btot; i++)
        scanf("%d", &bi[i]);
    memset(dp, 0x3f, sizeof(dp)), dp[0][1][1] = dp[1][0][0] = 0;
    for (int i = 0; i <= atot; i++)
        for (int j = 0; j <= btot; j++)
        {
            if (i + j == 0)
                continue;
            dp[i + 1][j][0] = min(dp[i + 1][j][0], dp[i][j][0] + dist[ai[i]][ai[i + 1]]);
            dp[i + 1][j][0] = min(dp[i + 1][j][0], dp[i][j][1] + dist[bi[j]][ai[i + 1]]);
            dp[i][j + 1][1] = min(dp[i][j + 1][1], dp[i][j][1] + dist[bi[j]][bi[j + 1]]);
            dp[i][j + 1][1] = min(dp[i][j + 1][1], dp[i][j][0] + dist[ai[i]][bi[j + 1]]);
        }
    printf("%lld", min(dp[atot][btot][0], dp[atot][btot][1]));
    return 0;
}