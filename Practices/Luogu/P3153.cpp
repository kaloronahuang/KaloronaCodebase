// P3153.cpp
#include <bits/stdc++.h>

using namespace std;

const int MAX_N = 1e5 + 200, INF = 0x3f3f3f3f;

int head[MAX_N], current, n, k, st, ed, dep[MAX_N], cur[MAX_N];
char opt[110][110];

struct edge
{
    int to, nxt, weight;
} edges[MAX_N << 1];

void addpath(int src, int dst, int weight)
{
    edges[current].to = dst, edges[current].nxt = head[src];
    edges[current].weight = weight, head[src] = current++;
}

void addtube(int src, int dst, int flow)
{
    addpath(src, dst, flow);
    addpath(dst, src, 0);
}

bool bfs()
{
    memset(dep, 0, sizeof(dep));
    queue<int> q;
    q.push(st), dep[st] = 1;
    while (!q.empty())
    {
        int u = q.front();
        q.pop();
        for (int i = head[u]; i != -1; i = edges[i].nxt)
            if (edges[i].weight > 0 && dep[edges[i].to] == 0)
                dep[edges[i].to] = dep[u] + 1, q.push(edges[i].to);
    }
    return dep[ed] != 0;
}

int dfs(int u, int flow)
{
    if (u == ed || flow == 0)
        return flow;
    for (int &i = cur[u]; i != -1; i = edges[i].nxt)
        if (dep[edges[i].to] == dep[u] + 1 && edges[i].weight > 0)
            if (int di = dfs(edges[i].to, min(flow, edges[i].weight)) > 0)
            {
                edges[i].weight -= di, edges[i ^ 1].weight += di;
                return di;
            }
    return 0;
}

int dinic()
{
    int ans = 0;
    while (bfs())
    {
        memcpy(cur, head, sizeof(head));
        while (int di = dfs(st, INF))
            ans += di;
    }
    return ans;
}

void build_graph(int mid)
{
    memset(head, -1, sizeof(head));
    current = 0;
    for (int i = 1; i <= n; i++)
    {
        addtube(st, i, mid);
        addtube(i + (n << 1), ed, mid);
        addtube(i, i + n, k);
        addtube(i + 3 * n, i + (n << 1), k);
    }
    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= n; j++)
            if (opt[i][j] == 'Y')
                addtube(i, j + (n << 1), 1);
            else
                addtube(i + n, j + 3 * n, 1);
}

int main()
{
    scanf("%d%d", &n, &k);
    st = (n << 2) | 1, ed = st + 1;
    for (int i = 1; i <= n; i++)
        scanf("%s", opt[i] + 1);
    int l = 0, r = n, ans = 0;
    while (l <= r)
    {
        int mid = (l + r) >> 1;
        build_graph(mid);
        if (dinic() == mid * n)
            l = mid + 1, ans = mid;
        else
            r = mid - 1;
    }
    printf("%d", ans);
    return 0;
}