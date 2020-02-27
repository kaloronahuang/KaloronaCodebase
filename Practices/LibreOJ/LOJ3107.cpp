// LOJ3107.cpp
#include <bits/stdc++.h>

using namespace std;

const int MAX_N = 2e5 + 200;

typedef long long ll;
typedef pair<ll, int> pli;

int T, n, m, diff, head[MAX_N], current, tag[MAX_N];
ll dist[MAX_N];
bool vis[MAX_N];

struct edge
{
    int to, nxt, weight;
} edges[MAX_N * 20];

void addpath(int src, int dst, int weight)
{
    edges[current].to = dst, edges[current].nxt = head[src];
    edges[current].weight = weight, head[src] = current++;
}

void shortest_path(int src)
{
    memset(dist, 0x3f, sizeof(dist));
    memset(vis, false, sizeof(vis));
    priority_queue<pli> pq;
    dist[src] = 0, pq.push(make_pair(0, src));
    while (!pq.empty())
    {
        int u = pq.top().second;
        pq.pop();
        if (vis[u])
            continue;
        vis[u] = true;
        for (int i = head[u]; i != -1; i = edges[i].nxt)
            if (dist[edges[i].to] > dist[u] + edges[i].weight)
                dist[edges[i].to] = dist[u] + edges[i].weight, pq.push(make_pair(-dist[edges[i].to], edges[i].to));
    }
}

int getId(int cb, int x) { return (cb + diff) * n + x; }

int main()
{
    scanf("%d", &T);
    while (T--)
    {
        memset(head, -1, sizeof(head)), current = 0;
        scanf("%d%d%d", &n, &m, &diff);
        for (int i = 1; i <= n; i++)
            scanf("%d", &tag[i]), tag[i] = (tag[i] == 1 ? 1 : -1);
        for (int idx = 1, u, v, w; idx <= m; idx++)
        {
            scanf("%d%d%d", &u, &v, &w);
            for (int stat = -diff; stat <= diff; stat++)
            {
                int u_ = getId(stat, u), dst_stat = stat + tag[v];
                if (dst_stat <= diff && dst_stat >= -diff)
                {
                    int v_ = getId(dst_stat, v);
                    addpath(u_, v_, w);
                }
                u_ = getId(stat, v), dst_stat = stat + tag[u];
                if (dst_stat <= diff && dst_stat >= -diff)
                {
                    int v_ = getId(dst_stat, u);
                    addpath(u_, v_, w);
                }
            }
        }
        int A, B;
        scanf("%d%d", &A, &B);
        A = getId(tag[A], A), shortest_path(A);
        ll ans = 0x3f3f3f3f3f3f3f3f;
        for (int i = -diff; i <= diff; i++)
            ans = min(ans, dist[getId(i, B)]);
        printf("%lld\n", ans == 0x3f3f3f3f3f3f3f3f ? -1 : ans);
    }
    return 0;
}