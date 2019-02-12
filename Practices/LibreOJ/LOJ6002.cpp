// LOJ6002.cpp
#include <bits/stdc++.h>
using namespace std;
const int MAX_N = 200 * 3, INF = 0x3f3f3f3f;
int n, m, head[MAX_N], current, upward[MAX_N], s, t, dep[MAX_N], cur[MAX_N], tmpx, tmpy;
bool tag[MAX_N];
struct edge
{
    int to, nxt, weight;
} edges[6000 << 2];
void addpath(int src, int dst, int weight)
{
    edges[current].to = dst, edges[current].weight = weight;
    edges[current].nxt = head[src], head[src] = current++;
}
void add(int src, int dst, int w) { addpath(src, dst, w), addpath(dst, src, 0); }
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
            if (edges[i].weight > 0 && !dep[edges[i].to])
                q.push(edges[i].to), dep[edges[i].to] = dep[u] + 1;
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
            int to = edges[i].to, fl = dfs(to, min(edges[i].weight, flow));
            if (fl > 0)
            {
                upward[u] = edges[i].to;
                if (u != s)
                    tag[edges[i].to - n] = true;
                edges[i].weight -= fl, edges[i ^ 1].weight += fl;
                return fl;
            }
        }
    return 0;
}
int Dinic()
{
    int ans = 0;
    while (bfs())
    {
        for (int i = 1; i <= 2 * n + 2; i++)
            cur[i] = head[i];
        while (int fl = dfs(s, INF))
            ans += fl;
    }
    for (int i = 1; i <= n; i++)
        if (!tag[i])
        {
            int p = i;
            printf("%d ", p);
            while (upward[p] && upward[p] != t)
                printf("%d ", upward[p] - n), p = upward[p] - n;
            printf("\n");
        }
    return ans;
}
int main()
{
    memset(head, -1, sizeof(head));
    scanf("%d%d", &n, &m);
    s = n * 2 + 1, t = s + 1;
    for (int i = 1; i <= n; i++)
        add(s, i, 1), add(i + n, t, 1);
    for (int i = 1; i <= m; i++)
    {
        scanf("%d%d", &tmpx, &tmpy);
        add(tmpx, tmpy + n, 1);
    }
    printf("%d", n - Dinic());
    return 0;
}