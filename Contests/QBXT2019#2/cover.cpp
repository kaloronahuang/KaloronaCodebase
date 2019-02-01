// cover.cpp
#include <bits/stdc++.h>
#define pr pair<int, int>
#define ll long long
using namespace std;
const int MAX_N = 1010, MAX_M = 50010, INF = 0x3f3f3f3f, mod = 998244353;
int head[MAX_N], current, n, m, tmpx, tmpy, tmpz, vis[MAX_N], dist[MAX_N][MAX_N];
ll ans[MAX_N];
int st[MAX_N], cur = 0;
struct edge
{
    int to, nxt, weight;
} edges[MAX_M];
void addpath(int u, int v, int w)
{
    edges[current].to = v, edges[current].nxt = head[u];
    edges[current].weight = w, head[u] = current++;
}
void djisktra(int src)
{
    memset(vis, 0, sizeof(vis));
    priority_queue<pr, vector<pr>, greater<pr>> q;
    q.push(make_pair(0, src)), dist[src][src] = 0;
    while (!q.empty())
    {
        pr now = q.top();
        q.pop();
        int u = now.second;
        vis[u] = true;
        for (int i = head[u]; i != -1; i = edges[i].nxt)
            if (dist[src][edges[i].to] > dist[src][u] + edges[i].weight)
            {
                dist[src][edges[i].to] = dist[src][u] + edges[i].weight;
                if (!vis[edges[i].to])
                    q.push(make_pair(dist[src][edges[i].to], edges[i].to));
            }
    }
}
void spread(int u, int remain, int dst)
{
    if (remain == 0 && u == dst)
    {
        for (int i = 1; i <= cur; i++)
            ans[st[i]] = (ans[st[i]] + 1) % mod;
        return;
    }
    if (remain < 0 || dist[u][dst] > remain)
        return;
    for (int i = head[u]; i != -1; i = edges[i].nxt)
    {
        st[++cur] = edges[i].to;
        spread(edges[i].to, remain - edges[i].weight, dst);
        cur--;
    }
}
int main()
{
    freopen("cover.in", "r", stdin);
    freopen("cover.out", "w", stdout);
    memset(head, -1, sizeof(head)), memset(dist, 0x3f, sizeof(dist));
    scanf("%d%d", &n, &m);
    for (int i = 1; i <= m; i++)
    {
        scanf("%d%d%d", &tmpx, &tmpy, &tmpz);
        if (tmpx != tmpy)
            addpath(tmpx, tmpy, tmpz);
    }
    for (int i = 1; i <= n; i++)
        djisktra(i);
    fill(ans, ans + MAX_N - 1, 1);
    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= n; j++)
            if (i != j && dist[i][j] != INF)
                st[++cur] = i, spread(i, dist[i][j], j), cur--;
    for (int i = 1; i <= n; i++)
        printf("%d\n", ans[i] % mod);
    return 0;
}