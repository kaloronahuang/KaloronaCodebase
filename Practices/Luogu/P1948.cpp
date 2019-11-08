// P1948.cpp
#include <bits/stdc++.h>
#define pr pair<int, int>

using namespace std;

const int MAX_N = 1010;

int head[MAX_N], current, n, m, fa[MAX_N], k, dist[MAX_N];
bool vis[MAX_N];

struct edge
{
    int from, to, nxt, weight;
    bool operator<(const edge &nd) const { return weight < nd.weight; }
} edges[MAX_N * 20], org[MAX_N * 20];

void addpath(int src, int dst, int weight)
{
    edges[current].to = dst, edges[current].nxt = head[src];
    edges[current].weight = weight, head[src] = current++;
}

int find(int x) { return x == fa[x] ? x : fa[x] = find(fa[x]); }

void unite(int x, int y) { return (void)(find(x) == find(y) ? 0 : fa[find(y)] = find(x)); }

void shortest_path(int src)
{
    memset(dist, 0x3f, sizeof(dist));
    memset(vis, false, sizeof(vis));
    priority_queue<pr> pq;
    pq.push(make_pair(0, src)), dist[src] = 0;
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

bool check(int mid)
{
    memset(head, -1, sizeof(head)), current = 0;
    for (int i = 1; i <= m; i++)
        if (org[i].weight <= mid)
            addpath(org[i].from, org[i].to, 0), addpath(org[i].to, org[i].from, 0);
        else
            addpath(org[i].from, org[i].to, 1), addpath(org[i].to, org[i].from, 1);
    shortest_path(1);
    return dist[n] <= k;
}

int main()
{
    int r = 0;
    scanf("%d%d%d", &n, &m, &k);
    for (int i = 1; i <= n; i++)
        fa[i] = i;
    for (int i = 1; i <= m; i++)
    {
        scanf("%d%d%d", &org[i].from, &org[i].to, &org[i].weight);
        r = max(r, org[i].weight), unite(org[i].from, org[i].to);
    }
    if (find(1) != find(n))
        puts("-1"), exit(0);
    sort(org + 1, org + 1 + m);
    int l = 0, ans;
    while (l <= r)
    {
        int mid = (l + r) >> 1;
        if (check(mid))
            r = mid - 1, ans = mid;
        else
            l = mid + 1;
    }
    printf("%d", ans);
    return 0;
}