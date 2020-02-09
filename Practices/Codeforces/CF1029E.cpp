// CF1029E.cpp
#include <bits/stdc++.h>

using namespace std;

const int MAX_N = 2e5 + 200;
typedef pair<int, int> pii;

int head[MAX_N], current, n, dep[MAX_N], up[MAX_N];
bool tag[MAX_N];

struct edge
{
    int to, nxt;
} edges[MAX_N << 1];

void addpath(int src, int dst)
{
    edges[current].to = dst, edges[current].nxt = head[src];
    head[src] = current++;
}

void dfs(int u, int fa)
{
    dep[u] = dep[fa] + 1, up[u] = fa;
    for (int i = head[u]; i != -1; i = edges[i].nxt)
        if (edges[i].to != fa)
            dfs(edges[i].to, u);
}

int main()
{
    memset(head, -1, sizeof(head));
    scanf("%d", &n);
    for (int i = 1, u, v; i <= n - 1; i++)
        scanf("%d%d", &u, &v), addpath(u, v), addpath(v, u);
    dep[0] = -1, dfs(1, 0);
    int cnt = 0;
    priority_queue<pii> pq;
    for (int i = 1; i <= n; i++)
        if (dep[i] > 2)
            pq.push(make_pair(dep[i], i));
    while (!pq.empty())
    {
        pii curt = pq.top();
        pq.pop();
        if (curt.first <= 2 || tag[curt.second])
            continue;
        int u = up[curt.second];
        cnt++, tag[u] = true;
        for (int i = head[u]; i != -1; i = edges[i].nxt)
            tag[edges[i].to] = true;
    }
    printf("%d\n", cnt);
    return 0;
}