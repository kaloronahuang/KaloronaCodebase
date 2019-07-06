// P4843.cpp
#include <bits/stdc++.h>

using namespace std;

const int MAX_N = 1100, INF = 0x3f3f3f3f;

int n, head[MAX_N], current, di[MAX_N], s, t, S, T, dep[MAX_N];

struct edge
{
    int to, nxt, weight;
} edges[MAX_N * MAX_N / 10];

void addpath(int src, int dst, int weight)
{
    edges[current].to = dst, edges[current].nxt = head[src];
    edges[current].weight = weight, head[src] = current++;
}

void addtube(int src, int dst, int upper, int lower)
{
    addpath(src, dst, upper - lower), addpath(dst, src, 0);
    di[src] -= lower, di[dst] += lower;
}

inline bool bfs()
{
    memset(dep, 0, sizeof(dep));
    queue<int> q;
    q.push(S), dep[S] = 1;
    while (!q.empty())
    {
        int u = q.front();
        q.pop();
        for (int i = head[u]; i != -1; i = edges[i].nxt)
            if (edges[i].weight > 0 && dep[edges[i].to] == 0)
                q.push(edges[i].to), dep[edges[i].to] = dep[u] + 1;
    }
    return dep[T] != 0;
}

int dfs(int u, int flow)
{
    if (u == T || flow == 0)
        return flow;
    int rest = flow;
    for (int i = head[u]; i != -1 && rest > 0; i = edges[i].nxt)
        if (edges[i].weight > 0 && dep[edges[i].to] == dep[u] + 1)
            if (int d = dfs(edges[i].to, min(rest, edges[i].weight)))
                edges[i].weight -= d, edges[i ^ 1].weight += d, rest -= d;
            else
                di[edges[i].to] = 0;
    return flow - rest;
}

int main()
{
    memset(head, -1, sizeof(head));
    scanf("%d", &n);
    s = n + 1, t = s + 1, S = t + 1, T = S + 1;
    for (int i = 1; i <= n; i++)
    {
        addtube(s, i, INF, 0), addtube(i, t, INF, 0);
        int m, target_pt;
        scanf("%d", &m);
        while (m--)
            scanf("%d", &target_pt), addtube(i, target_pt, INF, 1);
    }
    for (int i = 1; i <= t; i++)
        if (di[i] > 0)
            addtube(S, i, di[i], 0);
        else if (di[i] < 0)
            addtube(i, T, -di[i], 0);
    while (bfs())
        while(dfs(S, INF))
            ;
    addtube(t, s, INF, 0);
    while (bfs())
        while(dfs(S, INF))
            ;
    printf("%d", edges[current - 1].weight);
    return 0;
}