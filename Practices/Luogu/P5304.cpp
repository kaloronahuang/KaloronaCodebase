// P5304.cpp
#include <bits/stdc++.h>

using namespace std;

const int MAX_N = 1e5 + 200, MAX_E = 7e5 + 200;

typedef long long ll;
typedef pair<ll, int> pli;

int T, n, m, kind, head[MAX_N], current, ui[MAX_E], vi[MAX_E], wi[MAX_E], start_pos, end_pos, pts[MAX_N];
bool vis[MAX_N];
ll dist[MAX_N];

struct edge
{
    int to, nxt, weight;
} edges[MAX_E];

void addpath(int src, int dst, int weight)
{
    edges[current].to = dst, edges[current].nxt = head[src];
    edges[current].weight = weight, head[src] = current++;
}

void shortest_path()
{
    memset(dist, 0x3f, sizeof(dist));
    memset(vis, false, sizeof(vis));
    priority_queue<pli> pq;
    pq.push(make_pair(0, start_pos)), dist[start_pos] = 0;
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

int main()
{
    scanf("%d", &T);
    while (T--)
    {
        scanf("%d%d%d", &n, &m, &kind);
        for (int i = 1; i <= m; i++)
            scanf("%d%d%d", &ui[i], &vi[i], &wi[i]);
        for (int i = 1; i <= kind; i++)
            scanf("%d", &pts[i]);
        ll ans = 2e18;
        for (int i = 0; (1 << i) <= kind; i++)
        {
            memset(head, -1, sizeof(head)), current = 0;
            for (int j = 1; j <= m; j++)
                addpath(ui[j], vi[j], wi[j]);
            start_pos = n + 1, end_pos = n + 2;
            for (int j = 1; j <= kind; j++)
                if (j & (1 << i))
                    addpath(start_pos, pts[j], 0);
                else
                    addpath(pts[j], end_pos, 0);
            shortest_path(), ans = min(ans, dist[end_pos]);
        }
        for (int i = 0; (1 << i) <= kind; i++)
        {
            memset(head, -1, sizeof(head)), current = 0;
            for (int j = 1; j <= m; j++)
                addpath(ui[j], vi[j], wi[j]);
            start_pos = n + 1, end_pos = n + 2;
            for (int j = 1; j <= kind; j++)
                if (!(j & (1 << i)))
                    addpath(start_pos, pts[j], 0);
                else
                    addpath(pts[j], end_pos, 0);
            shortest_path(), ans = min(ans, dist[end_pos]);
        }
        printf("%lld\n", ans);
    }
    return 0;
}