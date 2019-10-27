// P5201.cpp
#include <bits/stdc++.h>
#define ll long long
#define pr pair<ll, int>

using namespace std;

const int MAX_N = 1e5 + 200, MAX_E = MAX_N * 5;

int head[MAX_N], current, n, m, siz[MAX_N], pre[MAX_N], upweight[MAX_N];
ll dist[MAX_N], dp[MAX_N], aux[MAX_N], T, answer;
bool vis[MAX_N];

struct edge
{
    int to, nxt, weight;
} edges[MAX_E << 1];

void addpath(int src, int dst, int weight)
{
    edges[current].to = dst, edges[current].nxt = head[src];
    edges[current].weight = weight, head[src] = current++;
}

void shortest_path(int src)
{
    memset(pre, 0x3f, sizeof(pre));
    memset(dist, 0x3f, sizeof(dist));
    priority_queue<pr> pq;
    pq.push(make_pair(0, src)), dist[src] = 0;
    while (!pq.empty())
    {
        int u = pq.top().second;
        pq.pop();
        if (vis[u])
            continue;
        vis[u] = true;
        for (int i = head[u]; i != -1; i = edges[i].nxt)
            if (dist[edges[i].to] > dist[u] + edges[i].weight)
                dist[edges[i].to] = dist[u] + edges[i].weight, pq.push(make_pair(-dist[edges[i].to], edges[i].to)), pre[edges[i].to] = u, upweight[edges[i].to] = edges[i].weight;
            else if (dist[edges[i].to] == dist[u] + edges[i].weight && pre[edges[i].to] > u)
                pre[edges[i].to] = u, upweight[edges[i].to] = edges[i].weight;
    }
}

void dfs(int u, int fa)
{
    for (int i = head[u]; i != -1; i = edges[i].nxt)
        if (edges[i].to != fa)
            dist[edges[i].to] = dist[u] + edges[i].weight, dfs(edges[i].to, u), siz[u] += siz[edges[i].to], answer = max(answer, siz[edges[i].to] * (dist[edges[i].to] - T));
}

int main()
{
    //freopen("testdata.in", "r", stdin);
    memset(head, -1, sizeof(head));
    scanf("%d%d%lld", &n, &m, &T);
    for (int i = 1; i <= n; i++)
        scanf("%d", &siz[i]);
    for (int i = 1, u, v, w; i <= m; i++)
        scanf("%d%d%d", &u, &v, &w), addpath(u, v, w), addpath(v, u, w);
    shortest_path(1);
    memset(head, -1, sizeof(head)), current = 0;
    for (int i = 2; i <= n; i++)
        addpath(pre[i], i, upweight[i]), addpath(i, pre[i], upweight[i]);
    dfs(1, 0), printf("%lld", answer);
    return 0;
}