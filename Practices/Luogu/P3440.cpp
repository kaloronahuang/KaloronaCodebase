// P3440.cpp
#include <bits/stdc++.h>
#define ll long long
using namespace std;

const int MAX_N = 1010, MAX_M = 40000 + (MAX_N << 1), INF = 0x3f3f3f3f;

int head[MAX_N], current, flow[MAX_N], dist[MAX_N], s, t, pre[MAX_N], n;
bool vis[MAX_N];

struct edge
{
    int to, nxt, weight, cost;
} edges[MAX_M << 1];

void addpath(int src, int dst, int weight, int cst)
{
    edges[current].to = dst, edges[current].nxt = head[src];
    edges[current].weight = weight, edges[current].cost = cst;
    head[src] = current++;
}

void addtube(int src, int dst, int weight, int cst)
{
    addpath(src, dst, weight, cst);
    addpath(dst, src, 0, -cst);
}

bool spfa()
{
    memset(dist, 0x3f, sizeof(dist));
    queue<int> q;
    q.push(s), vis[s] = true;
    flow[s] = INF, dist[s] = 0;
    while (!q.empty())
    {
        int u = q.front();
        q.pop();
        vis[u] = false;
        for (int i = head[u]; i != -1; i = edges[i].nxt)
            if (edges[i].weight > 0 && dist[edges[i].to] > dist[u] + edges[i].cost)
            {
                dist[edges[i].to] = dist[u] + edges[i].cost;
                flow[edges[i].to] = min(flow[u], edges[i].weight);
                pre[edges[i].to] = i;
                if (!vis[edges[i].to])
                    vis[edges[i].to] = true, q.push(edges[i].to);
            }
    }
    return dist[t] != INF;
}

pair<ll, ll> mcmf()
{
    ll ans1 = 0, ans2 = 0;
    while (spfa())
    {
        ans1 += flow[t], ans2 += flow[t] * dist[t];
        int pt = t, side = pre[pt];
        while (pt != s)
        {
            edges[side].weight -= flow[t], edges[side ^ 1].weight += flow[t];
            pt = edges[side ^ 1].to, side = pre[pt];
        }
    }
    return make_pair(ans1, ans2);
}

int main()
{
    memset(head, -1, sizeof(head));

    scanf("%d", &n), s = (n << 1) + 1, t = (n << 1) + 2;
    for (int i = 1, m, a, b, k; i <= n; i++)
    {
        scanf("%d%d%d%d", &m, &a, &b, &k);
        for (int j = a; j <= b; j++)
            addtube(i, j + n, 1, k * abs(j - m));
    }
    for (int i = 1; i <= n; i++)
        addtube(s, i, 1, 0), addtube(i + n, t, 1, 0);
    pair<ll, ll> res = mcmf();
    if (res.first != n)
        puts("NIE");
    else
        printf("%lld\n", res.second);
    return 0;
}