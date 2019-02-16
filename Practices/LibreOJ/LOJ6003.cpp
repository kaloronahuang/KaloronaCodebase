// LOJ6003.cpp
#include <bits/stdc++.h>
using namespace std;
const int MAX_N = 1e4 + 100, INF = 0x3f3f3f3f;
int head[MAX_N], current, s, t, dep[MAX_N], cur[MAX_N], n, tot, upward[MAX_N], tag[MAX_N], unit;
struct edge
{
    int to, nxt, weight;
} edges[500010];
void addpath(int src, int dst, int weight)
{
    edges[current].to = dst, edges[current].weight = weight;
    edges[current].nxt = head[src], head[src] = current++;
}
void add(int u, int v, int w) { addpath(u, v, w), addpath(v, u, 0); }
bool bfs()
{
    queue<int> q;
    q.push(s), memset(dep, 0, sizeof(dep));
    dep[s] = 1;
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
    for (int i = head[u]; i != -1; i = edges[i].nxt)
        if (dep[edges[i].to] == dep[u] + 1 && (edges[i].weight > 0))
        {
            int to = edges[i].to, fl = dfs(to, min(flow, edges[i].weight));
            if (fl > 0)
            {
                upward[u] = to;
                if (u != s)
                    tag[edges[i].to - unit] = true;
                edges[i].weight -= fl, edges[i ^ 1].weight += fl;
                return fl;
            }
        }
    return 0;
}
int dinic()
{
    memset(tag, false, sizeof(tag));
    int ans = 0;
    while (bfs())
    {
        for (int i = 0; i <= tot; i++)
            cur[i] = head[i];
        while (int f = dfs(s, INF))
            ans += f;
    }
    return ans;
}
bool check(int num)
{
    unit = num;
    tot = (num << 1) + 2, s = tot - 1, t = tot;
    memset(head, -1, sizeof(head)), current = 0;
    for (int i = 1; i <= num; i++)
        add(s, i, 1), add(i + num, t, 1);
    for (int i = 1; i <= num; i++)
        for (int j = 1; j * j - i <= num; j++)
            if (i < j * j - i)
                add(j * j - i, i + num, 1);
    return num - dinic() <= n;
}
int main()
{
    scanf("%d", &n);
    int l = 1, r = MAX_N - 2000, ans;
    while (l <= r)
    {
        int mid = (l + r) >> 1;
        if (check(mid))
            l = mid + 1, ans = mid;
        else
            r = mid - 1;
    }
    printf("%d\n", ans);
    check(ans);
    for (int i = 1; i <= ans; i++)
        if (!tag[i])
        {
            int p = i;
            printf("%d ", p);
            while (upward[p] && upward[p] != t && upward[p] - ans >= 0)
                printf("%d ", upward[p] - ans), p = upward[p] - ans;
            puts("");
        }
    return 0;
}