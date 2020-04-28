// P3324.cpp
#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

const int MAX_N = 2e5 + 200;
const ll INF = 0x3f3f3f3f3f3f3f3f;
const double eps = 1e-4;

int n, m, attack[55][55], head[MAX_N], cur[MAX_N], dep[MAX_N], start_pos, end_pos, current;
ll ai[55], bi[55];

struct edge
{
    int to, nxt;
    ll weight;
} edges[MAX_N << 1];

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
            if (dep[edges[i].to] == 0 && edges[i].weight > 0)
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
        memcpy(cur, head, sizeof(cur));
        while (ll di = dfs(start_pos, INF))
            ret += di;
    }
    return ret;
}

ll calibre;

bool check(ll mid)
{
    start_pos = n + m + 1, end_pos = start_pos + 1;
    memset(head, -1, sizeof(head)), current = 0;
    for (int i = 1; i <= m; i++)
        addtube(start_pos, i, mid * bi[i]);
    for (int i = 1; i <= n; i++)
        addtube(i + m, end_pos, ai[i]);
    for (int i = 1; i <= m; i++)
        for (int j = 1; j <= n; j++)
            if (attack[i][j])
                addtube(i, j + m, INF);
    return dinic() >= calibre;
}

int main()
{
    scanf("%d%d", &n, &m);
    for (int i = 1; i <= n; i++)
        scanf("%lld", &ai[i]), ai[i] *= 1e4, calibre += ai[i];
    for (int i = 1; i <= m; i++)
        scanf("%lld", &bi[i]);
    for (int i = 1; i <= m; i++)
        for (int j = 1; j <= n; j++)
            scanf("%d", &attack[i][j]);
    ll l = 0, r = 1e12, res;
    while (l + eps < r)
    {
        ll mid = (l + r) >> 1;
        if (check(mid))
            r = mid - 1, res = mid;
        else
            l = mid + 1;
    }
    printf("%.4lf\n", res / 10000.0);
    return 0;
}