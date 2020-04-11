// LOJ6079.cpp
#include <bits/stdc++.h>

using namespace std;

const int MAX_N = 1010, INF = 0x3f3f3f3f;

typedef long long ll;

int n, k, ms, me, si[MAX_N], ei[MAX_N], pre[MAX_N], flow[MAX_N], start_pos, end_pos, head[MAX_N], current, spot[MAX_N];
ll dist[MAX_N], ans;
bool vis[MAX_N];

struct edge
{
    int to, nxt, weight, cost;
} edges[MAX_N * 6];

void addpath(int src, int dst, int weight, int cost)
{
    edges[current].to = dst, edges[current].nxt = head[src];
    edges[current].weight = weight, edges[current].cost = cost;
    head[src] = current++;
}

void addtube(int src, int dst, int weight, int cost) { addpath(src, dst, weight, cost), addpath(dst, src, 0, -cost); }

bool spfa_max(int src)
{
    memset(vis, false, sizeof(vis));
    memset(pre, -1, sizeof(pre)), memset(dist, 128, sizeof(dist));
    queue<int> q;
    q.push(src), vis[src] = true, dist[src] = 0, flow[src] = 0x3f3f3f3f;
    while (!q.empty())
    {
        int u = q.front();
        q.pop(), vis[u] = false;
        for (int i = head[u]; i != -1; i = edges[i].nxt)
            if (edges[i].weight > 0 && dist[edges[i].to] < dist[u] + edges[i].cost)
            {
                dist[edges[i].to] = dist[u] + edges[i].cost;
                pre[edges[i].to] = i, flow[edges[i].to] = min(flow[u], edges[i].weight);
                if (!vis[edges[i].to])
                    vis[edges[i].to] = true, q.push(edges[i].to);
            }
    }
    return pre[end_pos] != -1;
}

ll mfmc()
{
    ll ret = 0;
    while (spfa_max(start_pos))
    {
        ret += 1LL * dist[end_pos] * flow[end_pos];
        int p = end_pos;
        while (p != start_pos)
            edges[pre[p]].weight -= flow[end_pos], edges[pre[p] ^ 1].weight += flow[end_pos], p = edges[pre[p] ^ 1].to;
    }
    return ret;
}

int main()
{
    memset(head, -1, sizeof(head));
    scanf("%d%d%d%d", &n, &k, &ms, &me);
    for (int i = 1; i <= n; i++)
        scanf("%d", &si[i]), ans += si[i];
    for (int i = 1; i <= n; i++)
        scanf("%d", &ei[i]);
    end_pos = n + 1, start_pos = n + 2;
    int gpt = n + 3;
    for (int i = 1; i <= n; i++)
        addtube(i, i + 1, k - me - ms, 0);
    for (int i = 1; i <= n; i++)
        addtube(i, min(i + k, end_pos), 1, ei[i] - si[i]), spot[i] = current - 1;
    addtube(start_pos, gpt, k - ms, 0);
    for (int i = 1; i <= k; i++)
        addtube(gpt, i, INF, 0);
    ans += mfmc();
    printf("%lld\n", ans);
    for (int i = 1; i <= n; i++)
        if (edges[spot[i]].weight == 0)
            putchar('S');
        else
            putchar('E');
    return 0;
}