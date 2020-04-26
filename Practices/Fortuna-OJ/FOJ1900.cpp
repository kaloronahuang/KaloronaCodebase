// FOJ1900.cpp
#include <bits/stdc++.h>

using namespace std;

const int MAX_N = 660, INF = 0x3f3f3f3f;

typedef long long ll;

inline char nc()
{
    static char buf[10000000], *p1 = buf, *p2 = buf;
    return p1 == p2 && (p2 = (p1 = buf) + fread(buf, 1, 10000000, stdin), p1 == p2) ? EOF : *p1++;
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

int n, bi[MAX_N][MAX_N], ci[MAX_N], head[MAX_N * MAX_N], current, dep[MAX_N * MAX_N], cur[MAX_N * MAX_N];
int start_pos, end_pos;

struct edge
{
    int to, nxt;
    ll weight;
} edges[2LL * MAX_N * MAX_N + 4 * MAX_N];

void addpath(int src, int dst, ll weight)
{
    edges[current].to = dst, edges[current].nxt = head[src];
    edges[current].weight = weight, head[src] = current++;
}

void addtube(int src, int dst, ll weight)
{
    addpath(src, dst, weight);
    addpath(dst, src, 0);
}

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

ll dfs(int u, ll flow)
{
    if (u == end_pos || flow == 0)
        return flow;
    for (int &i = cur[u]; i != -1; i = edges[i].nxt)
        if (edges[i].weight > 0 && dep[edges[i].to] == dep[u] + 1)
            if (ll di = dfs(edges[i].to, min(flow, edges[i].weight)))
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
        memcpy(cur, head, sizeof(head));
        while (ll di = dfs(start_pos, INF))
            ret += di;
    }
    return ret;
}

int main()
{
    freopen("matrix7.in", "r", stdin);
    memset(head, -1, sizeof(head));
    n = read(), start_pos = n + 1, end_pos = start_pos + 1;
    ll ans = 0;
    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= n; j++)
            bi[i][j] = read();
    for (int i = 1; i <= n; i++)
    {
        ll bust = 0;
        for (int j = 1; j <= n; j++)
            bust += bi[j][i];
        ans += bust, addtube(start_pos, i, bust);
        for (int j = 1; j < i; j++)
            addpath(i, j, bi[j][i]), addpath(j, i, bi[i][j]);
    }
    for (int i = 1; i <= n; i++)
        ci[i] = read(), addtube(i, end_pos, ci[i]);
    printf("%lld\n", ans - dinic());
    return 0;
}