// C.cpp
#include <bits/stdc++.h>
#define ll long long
#define pr pair<ll, int>

using namespace std;

const int MAX_N = 5e4 + 200, MAX_E = 220000;

int head[MAX_N], current, n, m, k, s, t, tag_pt[20], rev_id[MAX_N];
ll dist[20][MAX_N];
bool vis[MAX_N];

struct edge
{
    int to, nxt;
    ll weight;
} edges[MAX_E << 1];

void addpath(int src, int dst, ll weight)
{
    edges[current].to = dst, edges[current].nxt = head[src];
    edges[current].weight = weight, head[src] = current++;
}

void shortest_path(int id, int src)
{
    memset(dist[id], 0x3f, sizeof(dist[id]));
    memset(vis, false, sizeof(vis));
    priority_queue<pr> pq;
    pq.push(make_pair(0, src)), dist[id][src] = 0;
    while (!pq.empty())
    {
        int u = pq.top().second;
        pq.pop();
        if (vis[u])
            continue;
        vis[u] = true;
        for (int i = head[u]; i != -1; i = edges[i].nxt)
            if (dist[id][edges[i].to] > dist[id][u] + edges[i].weight)
                dist[id][edges[i].to] = dist[id][u] + edges[i].weight, pq.push(make_pair(-dist[id][edges[i].to], edges[i].to));
    }
}

int main()
{
    memset(head, -1, sizeof(head));
    scanf("%d%d%d%d%d", &n, &m, &k, &s, &t);
    for (int i = 1, u, v, w; i <= m; i++)
        scanf("%d%d%d", &u, &v, &w), addpath(u, v, w);
    for (int i = 1; i <= k; i++)
        scanf("%d", &tag_pt[i]), shortest_path(i, tag_pt[i]), rev_id[i] = i;
    shortest_path(0, s);
    tag_pt[0] = s, tag_pt[k + 1] = t, rev_id[k + 1] = k + 1;
    ll ans = 0x3f3f3f3f3f3f3f3f;
    do
    {
        ll gans = 0;
        for (int i = 0; i <= k; i++)
            gans += dist[rev_id[i]][tag_pt[rev_id[i + 1]]];
        ans = min(gans, ans);
    } while (next_permutation(rev_id + 1, rev_id + 1 + k));
    printf("%lld", ans == 0x3f3f3f3f3f3f3f3f ? -1 : ans);
    return 0;
}