// BZ1497.cpp
#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

const int MAX_N = 2e5 + 200, MAX_E = 5050 + 5e4 + 200 + (5e4 + 200) * 2, INF = 0x3f3f3f3f;

int n, m, head[MAX_N], current, start_pos, end_pos, dep[MAX_N], cur[MAX_N], pi[MAX_N];

struct edge
{
    int to, nxt, weight;
} edges[MAX_E << 1];

void addpath(int src, int dst, int weight)
{
    edges[current].to = dst, edges[current].weight = weight;
    edges[current].nxt = head[src], head[src] = current++;
}

void addtube(int src, int dst, int weight) { addpath(src, dst, weight), addpath(dst, src, 0); }

bool bfs()
{
    memset(dep, 0, sizeof(dep));
    queue<int> q;
    q.push(start_pos), dep[start_pos] = 1;
    while (!q.empty())
    {
        int u = q.front();
        q.pop();
        for (int i = head[u]; i != -1; i = edges[i].nxt)
            if (edges[i].weight > 0 && dep[edges[i].to] == 0)
                dep[edges[i].to] = dep[u] + 1, q.push(edges[i].to);
    }
    return dep[end_pos] != 0;
}

int dfs(int u, int flow)
{
    if (u == end_pos || flow == 0)
        return flow;
    for (int &i = cur[u]; i != -1; i = edges[i].nxt)
        if (edges[i].weight > 0 && dep[edges[i].to] == dep[u] + 1)
            if (int di = dfs(edges[i].to, min(flow, edges[i].weight)))
            {
                edges[i].weight -= di, edges[i ^ 1].weight += di;
                return di;
            }
    return 0;
}

ll dinic()
{
    ll ret = 0;
    while (bfs())
    {
        memcpy(cur, head, sizeof(cur));
        while (int di = dfs(start_pos, INF))
            ret += di;
    }
    return ret;
}

int main()
{
    memset(head, -1, sizeof(head));
    scanf("%d%d", &n, &m), start_pos = n + m + 1, end_pos = start_pos + 1;
    ll ans = 0;
    for (int i = 1; i <= n; i++)
        scanf("%d", &pi[i]), addtube(i, end_pos, pi[i]);
    for (int i = 1, a, b, c; i <= m; i++)
    {
        scanf("%d%d%d", &a, &b, &c), addtube(start_pos, i + n, c);
        addtube(i + n, a, INF), addtube(i + n, b, INF), ans += c;
    }
    printf("%lld\n", ans - dinic());
    return 0;
}