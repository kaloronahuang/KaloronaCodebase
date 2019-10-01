// P1951.cpp
#include <bits/stdc++.h>
#define ll long long
#define pr pair<ll, int>

using namespace std;

const int MAX_N = 10010, MAX_E = 5 * MAX_N;

int head[MAX_N], current, n, m;
ll dist[MAX_N], S, T, capacity, dot[MAX_N];
bool vis[MAX_N];

struct edge
{
    int to, nxt, weight;
} edges[MAX_E << 1];

void addpath(int src, int dst, int weight)
{
    edges[current].to = dst, edges[current].nxt = head[src];
    edges[current].weight = weight, head[src] = current++;
}

bool check(ll mid)
{
    memset(dist, 0x3f, sizeof(dist));
    memset(vis, false, sizeof(vis));
    priority_queue<pr> pq;
    pq.push(make_pair(0, S)), dist[S] = 0;
    while (!pq.empty())
    {
        int u = pq.top().second;
        pq.pop();
        if (vis[u])
            continue;
        vis[u] = true;
        for (int i = head[u]; i != -1; i = edges[i].nxt)
            if (dot[edges[i].to] <= mid && dist[edges[i].to] > dist[u] + edges[i].weight)
                dist[edges[i].to] = dist[u] + edges[i].weight, pq.push(make_pair(-dist[edges[i].to], edges[i].to));
    }
    return dist[T] <= capacity;
}

int main()
{
    memset(head, -1, sizeof(head));
    scanf("%d%d%lld%lld%lld", &n, &m, &S, &T, &capacity);
    ll r = 0;
    for (int i = 1; i <= n; i++)
        scanf("%lld", &dot[i]), r = max(r, dot[i]);
    for (ll i = 1, u, v, w; i <= m; i++)
        scanf("%lld%lld%lld", &u, &v, &w), addpath(u, v, w), addpath(v, u, w);
    ll l = max(dot[S], dot[T]), ans = -1;
    while (l <= r)
    {
        ll mid = (l + r) >> 1;
        if (check(mid))
            r = mid - 1, ans = mid;
        else
            l = mid + 1;
    }
    printf("%lld", ans);
    return 0;
}