// LOJ6006.cpp
#include <bits/stdc++.h>
using namespace std;
const int MAX_N = 1010, INF = 0x3f3f3f3f;
int head[MAX_N << 1], s, t, current, n, k, dep[MAX_N], cur[MAX_N], ki[MAX_N], m, p, tmpx, downward[MAX_N];
vector<int> vec[MAX_N];
struct edge
{
    int to, nxt, weight;
} edges[MAX_N << 4];
void addpath(int src, int dst, int weight)
{
    edges[current].to = dst, edges[current].nxt = head[src];
    edges[current].weight = weight, head[src] = current++;
}
void add(int src, int dst, int weight) { addpath(src, dst, weight), addpath(dst, src, 0); }
bool bfs()
{
    memset(dep, 0, sizeof(dep));
    queue<int> q;
    q.push(s), dep[s] = 1;
    while (!q.empty())
    {
        int u = q.front();
        q.pop();
        for (int i = head[u]; i != -1; i = edges[i].nxt)
            if (edges[i].weight > 0 && dep[edges[i].to] == 0)
                dep[edges[i].to] = dep[u] + 1, q.push(edges[i].to);
    }
    return dep[t] != 0;
}
int dfs(int u, int flow)
{
    if (u == t || flow == 0)
        return flow;
    for (int &i = cur[u]; i != -1; i = edges[i].nxt)
        if (edges[i].weight > 0 && dep[edges[i].to] == dep[u] + 1)
        {
            int di = dfs(edges[i].to, min(flow, edges[i].weight));
            if (di)
            {
                edges[i].weight -= di, edges[i ^ 1].weight += di;
                downward[u] = edges[i].to;
                return di;
            }
        }
    return 0;
}
int dinic()
{
    int ans = 0;
    while (bfs())
    {
        for (int i = 0; i <= t; i++)
            cur[i] = head[i];
        while (int di = dfs(s, INF))
            ans += di;
    }
    return ans;
}
int main()
{
    memset(head, -1, sizeof(head));
    scanf("%d%d", &k, &n);
    s = 0, t = n + k + 1;
    for (int i = 1; i <= k; i++)
        scanf("%d", &ki[i]), m += ki[i], add(i + n, t, ki[i]);
    for (int i = 1; i <= n; i++)
    {
        add(s, i, 1), scanf("%d", &p);
        while (p--)
            scanf("%d", &tmpx), add(i, tmpx + n, 1);
    }
    int ans = dinic();
    if (ans != m)
        printf("No Solution!"), exit(0);
    for (int i = 1; i <= n; i++)
        vec[max(downward[i] - n, 0)].push_back(i);
    for (int i = 1; i <= k; i++)
    {
        printf("%d:", i);
        for (vector<int>::iterator it = vec[i].begin(); it != vec[i].end(); it++)
            printf(" %d", *it);
        puts("");
    }
    return 0;
}