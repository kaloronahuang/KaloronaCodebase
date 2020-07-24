// BZ3275.cpp
#include <bits/stdc++.h>

using namespace std;

const int MAX_N = 3030, INF = 0x3f3f3f3f;

typedef long long ll;

int n, ai[MAX_N], head[MAX_N], current, dep[MAX_N], start_pos, end_pos;

struct edge
{
    int to, nxt, weight;
} edges[MAX_N * MAX_N];

void addpath(int src, int dst, int weight)
{
    edges[current].to = dst, edges[current].nxt = head[src];
    edges[current].weight = weight, head[src] = current++;
}

void addtube(int src, int dst, int weight)
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
int dfs(int u, int flow)
{
    if (u == end_pos || flow == 0)
        return flow;
    for (int i = head[u]; i != -1; i = edges[i].nxt)
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
        while (int di = dfs(start_pos, INF))
            ret += di;
    return ret;
}

bool check(ll x)
{
    ll bas = sqrt(x);
    return 1LL * bas * bas == x;
}

int main()
{
    memset(head, -1, sizeof(head));
    scanf("%d", &n), start_pos = n + 1, end_pos = n + 2;
    long long sum = 0;
    for (int i = 1; i <= n; i++)
    {
        scanf("%d", &ai[i]), sum += ai[i];
        if (ai[i] & 1)
            addtube(start_pos, i, ai[i]);
        else
            addtube(i, end_pos, ai[i]);
    }
    for (int i = 1; i <= n; i++)
        if (ai[i] & 1)
            for (int j = 1; j <= n; j++)
                if (i != j)
                    if (__gcd(ai[i], ai[j]) == 1 && check(1LL * ai[i] * ai[i] + 1LL * ai[j] * ai[j]))
                        addtube(i, j, INF);
    printf("%lld\n", sum - dinic());
    return 0;
}