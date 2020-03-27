// BZ4842.cpp
#include <bits/stdc++.h>

using namespace std;

const int MAX_N = 1100;

typedef long long ll;

int n, k, t1, t2, head[MAX_N], current, pre[MAX_N], start_pt, end_pt, flow[MAX_N], si[MAX_N], ei[MAX_N], pivot[MAX_N];
bool vis[MAX_N];
ll dist[MAX_N];

struct edge
{
    int to, nxt, weight, cost;
} edges[MAX_N * 20];

void addpath(int src, int dst, int weight, int cost)
{
    edges[current].to = dst, edges[current].nxt = head[src];
    edges[current].weight = weight, edges[current].cost = cost;
    head[src] = current++;
}

void addtube(int src, int dst, int weight, int cost)
{
    addpath(src, dst, weight, cost);
    addpath(dst, src, 0, -cost);
}

bool spfa()
{
    memset(dist, 0xbf, sizeof(dist)), memset(pre, -1, sizeof(pre));
    memset(vis, false, sizeof(vis));
    queue<int> q;
    q.push(start_pt), vis[start_pt] = true, dist[start_pt] = 0, flow[start_pt] = 0x3f3f3f3f;
    while (!q.empty())
    {
        int u = q.front();
        q.pop();
        vis[u] = false;
        for (int i = head[u]; i != -1; i = edges[i].nxt)
            if (edges[i].weight > 0 && dist[edges[i].to] < dist[u] + edges[i].cost)
            {
                dist[edges[i].to] = dist[u] + edges[i].cost, pre[edges[i].to] = i;
                flow[edges[i].to] = min(flow[u], edges[i].weight);
                if (vis[edges[i].to] == false)
                    vis[edges[i].to] = true, q.push(edges[i].to);
            }
    }
    return pre[end_pt] != -1;
}

ll mfmc()
{
    ll ret = 0;
    while (spfa())
    {
        ret += 1LL * dist[end_pt] * flow[end_pt];
        int p = end_pt;
        while (p != start_pt)
            edges[pre[p]].weight -= flow[end_pt], edges[pre[p] ^ 1].weight += flow[end_pt], p = edges[pre[p] ^ 1].to;
    }
    return ret;
}

int main()
{
    ll ans = 0;
    memset(head, -1, sizeof(head));
    scanf("%d%d%d%d", &n, &k, &t1, &t2);
    for (int i = 1; i <= n; i++)
        scanf("%d", &si[i]);
    for (int i = 1; i <= n; i++)
        scanf("%d", &ei[i]), ans += ei[i];
    end_pt = n + 1;
    for (int i = 1; i <= n; i++)
    {
        addtube(i, min(i + k, end_pt), 1, si[i] - ei[i]);
        pivot[i] = current - 2, addtube(i, i + 1, k - t1 - t2, 0);
    }
    start_pt = n + 2;
    for (int i = 1; i <= k; i++)
        addtube(0, i, 0x3f3f3f3f, 0);
    addtube(start_pt, 0, k - t2, 0);
    printf("%lld\n", ans + mfmc());
    for (int i = 1; i <= n; i++)
        if (edges[pivot[i]].weight == 0)
            // flowed;
            putchar('S');
        else
            putchar('E');
    putchar('\n');
    return 0;
}