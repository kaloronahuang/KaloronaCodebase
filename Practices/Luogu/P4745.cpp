// P4745.cpp
#include <bits/stdc++.h>

using namespace std;

const int MAX_N = 301000;
typedef pair<double, int> pdi;

int head[MAX_N], n, m, current, deg[MAX_N], cnt[MAX_N];
double dist[MAX_N], sum[MAX_N];
bool vis[MAX_N];

struct edge
{
    int to, nxt;
} edges[MAX_N << 1];

void addpath(int src, int dst)
{
    edges[current].to = dst, edges[current].nxt = head[src];
    head[src] = current++;
}

void shortest_path()
{
    priority_queue<pdi> pq;
    pq.push(make_pair(0, n));
    while (!pq.empty())
    {
        int u = pq.top().second;
        pq.pop();
        if (vis[u])
            continue;
        vis[u] = true;
        for (int i = head[u]; i != -1; i = edges[i].nxt)
            if (vis[edges[i].to] == false)
            {
                cnt[edges[i].to]++, sum[edges[i].to] += dist[u];
                dist[edges[i].to] = double(sum[edges[i].to] + deg[edges[i].to]) / double(cnt[edges[i].to]);
                pq.push(make_pair(-dist[edges[i].to], edges[i].to));
            }
    }
}

int main()
{
    memset(head, -1, sizeof(head));
    scanf("%d%d", &n, &m);
    for (int i = 1, u, v; i <= m; i++)
        scanf("%d%d", &u, &v), addpath(u, v), addpath(v, u), deg[u]++, deg[v]++;
    shortest_path(), printf("%.10lf\n", dist[1]);
    return 0;
}