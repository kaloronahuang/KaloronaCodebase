// P4878.cpp
#include <bits/stdc++.h>
typedef long long ll;

using namespace std;

const int MAX_N = 10100, MAX_E = 1e5 + 200;
const ll INF = 0x3f3f3f3f3f3f3f3f;

int head[MAX_N], current, n, m1, m2, cnt[MAX_N];
ll dist[MAX_N];
bool vis[MAX_N];

struct edge
{
    int to, nxt, weight;
} edges[MAX_N << 1];

void addpath(int src, int dst, int weight)
{
    edges[current].to = dst, edges[current].nxt = head[src];
    edges[current].weight = weight, head[src] = current++;
}

bool spfa(int src)
{
    memset(dist, 0x3f, sizeof(dist)), memset(cnt, 0, sizeof(cnt));
    memset(vis, false, sizeof(vis));
    queue<int> q;
    q.push(src), dist[src] = 0, vis[src] = true, cnt[src] = 1;
    while (!q.empty())
    {
        int u = q.front();
        q.pop();
        vis[u] = false;
        if (++cnt[u] > n)
            return false;
        for (int i = head[u]; i != -1; i = edges[i].nxt)
            if (dist[edges[i].to] > dist[u] + edges[i].weight)
            {
                dist[edges[i].to] = dist[u] + edges[i].weight;
                if (vis[edges[i].to] == false)
                    vis[edges[i].to] = true, q.push(edges[i].to);
            }
    }
    return true;
}

int main()
{
    memset(head, -1, sizeof(head));
    scanf("%d%d%d", &n, &m1, &m2);
    for (int i = 1, u, v, d; i <= m1; i++)
        scanf("%d%d%d", &u, &v, &d), addpath(u, v, d);
    for (int i = 1, u, v, d; i <= m2; i++)
        scanf("%d%d%d", &u, &v, &d), addpath(v, u, -d);
    for (int i = 1; i <= n; i++)
        addpath(0, i, 0);
    if (!spfa(0))
        puts("-1"), exit(0);
    spfa(1);
    if (dist[n] == INF)
        puts("-2");
    else
        printf("%lld", dist[n]);
    return 0;
}