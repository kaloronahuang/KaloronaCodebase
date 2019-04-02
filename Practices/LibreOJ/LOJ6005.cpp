// LOJ6005.cpp
#include <bits/stdc++.h>
using namespace std;
const int MAX_N = 6000, INF = 0x3f3f3f3f;
int b[MAX_N], arr[MAX_N], f[MAX_N], n, head[MAX_N << 2], current, dep[MAX_N], s, t, cur[MAX_N], k;
struct edge
{
    int to, weight, nxt;
} edges[MAX_N << 3];
void addpath(int src, int dst, int weight)
{
    edges[current].to = dst, edges[current].nxt = head[src];
    edges[current].weight = weight, head[src] = current++;
}
void add(int src, int dst, int weight) { addpath(src, dst, weight), addpath(dst, src, 0); }
bool bfs()
{
    queue<int> q;
    memset(dep, 0, sizeof(dep));
    dep[s] = 1, q.push(s);
    while (!q.empty())
    {
        int curt = q.front();
        q.pop();
        for (int i = head[curt]; i != -1; i = edges[i].nxt)
            if (!dep[edges[i].to] && edges[i].weight > 0)
                q.push(edges[i].to), dep[edges[i].to] = dep[curt] + 1;
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
            int fl = dfs(edges[i].to, min(edges[i].weight, flow));
            if (fl)
            {
                edges[i].weight -= fl, edges[i ^ 1].weight += fl;
                return fl;
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
        while (int fl = dfs(s, INF))
            ans += fl;
    }
    return ans;
}
int main()
{
    memset(head, -1, sizeof(head)), memset(b, 0x3f, sizeof(b));
    scanf("%d", &n);
    for (int i = 1; i <= n; scanf("%d", &arr[i]), i++)
        ;
    if (n == 1 && arr[1] == 1)
        printf("1\n1\n1\n"), exit(0);
    b[1] = arr[1], f[1] = 1;
    for (int i = 2; i <= n; i++)
    {
        int leg = upper_bound(b + 1, b + 1 + n, arr[i]) - b - 1;
        f[i] = leg + 1;
        if (arr[i] < b[leg + 1])
            b[leg + 1] = arr[i];
        k = max(k, leg + 1);
    }
    printf("%d\n", k);
    s = 0, t = 2 * n + 1;
    for (int i = 1; i <= n; i++)
    {
        if (f[i] == 1)
            add(s, i, 1);
        add(i, i + n, 1);
        if (f[i] == k)
            add(i + n, t, 1);
        for (int j = i + 1; j <= n; j++)
            if (f[j] == f[i] + 1 && arr[j] >= arr[i])
                add(i + n, j, 1);
    }
    printf("%d\n", dinic());
    memset(head, -1, sizeof(head)), current = 0;
    for (int i = 1; i <= n; i++)
    {
        if (f[i] == 1)
            add(s, i, i == 1 ? INF : 1);
        if (i == 1 || i == n)
            add(i, i + n, INF);
        else
            add(i, i + n, 1);
        if (f[i] == k)
            add(i + n, t, i == n ? INF : 1);
        for (int j = i + 1; j <= n; j++)
            if (f[j] == f[i] + 1 && arr[j] >= arr[i])
                add(i + n, j, 1);
    }
    printf("%d", dinic());
    return 0;
}