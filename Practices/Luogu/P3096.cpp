// P3096.cpp
#include <bits/stdc++.h>
typedef long long ll;
#define pr pair<ll, int>

using namespace std;

const int MAX_N = 2e4 + 200;
const ll INF = 0x3f3f3f3f3f3f3f3f;

int head[MAX_N], current, n, m, k, idx[MAX_N], q, ui[MAX_N], vi[MAX_N], wi[MAX_N];
ll dist[205][MAX_N], dist_opp[205][MAX_N];
bool vis[MAX_N];

const int SIZE = 100000;

inline char nc()
{
    static char buf[SIZE], *p1 = buf + SIZE, *p2 = buf + SIZE;
    if (p1 == p2)
        p2 = (p1 = buf) + fread(buf, 1, SIZE, stdin);
    return p1 == p2 ? -1 : *p1++;
}

int read()
{
    int x = 0, f = 1;
    char ch = nc();
    while (!isdigit(ch))
    {
        if (ch == '-')
            f = -1;
        ch = nc();
    }
    while (isdigit(ch))
        x = (x << 3) + (x << 1) + ch - '0', ch = nc();
    return x * f;
}

struct edge
{
    int to, nxt, weight;
} edges[MAX_N << 1];

void addpath(int src, int dst, int weight)
{
    edges[current].to = dst, edges[current].nxt = head[src];
    edges[current].weight = weight, head[src] = current++;
}

void shortest_path(int src_id)
{
    int src = idx[src_id];
    memset(vis, false, sizeof(vis));
    memset(dist[src_id], 0x3f, sizeof(dist[src_id]));
    priority_queue<pr> pq;
    pq.push(make_pair(0, src)), dist[src_id][src] = 0;
    while (!pq.empty())
    {
        int u = pq.top().second;
        pq.pop();
        if (vis[u])
            continue;
        vis[u] = true;
        for (int i = head[u]; i != -1; i = edges[i].nxt)
            if (dist[src_id][edges[i].to] > dist[src_id][u] + edges[i].weight)
                dist[src_id][edges[i].to] = dist[src_id][u] + edges[i].weight, pq.push(make_pair(-dist[src_id][edges[i].to], edges[i].to));
    }
}

int main()
{
    memset(head, -1, sizeof(head));
    n = read(), m = read(), k = read(), q = read();
    for (int i = 1, u, v, w; i <= m; i++)
        u = read(), v = read(), w = read(), addpath(v, u, w), ui[i] = u, vi[i] = v, wi[i] = w;
    for (int i = 1; i <= k; i++)
        idx[i] = read(), shortest_path(i);
    swap(dist_opp, dist);

    memset(head, -1, sizeof(head)), current = 0;
    for (int i = 1; i <= m; i++)
        addpath(ui[i], vi[i], wi[i]);
    for (int i = 1; i <= k; i++)
        shortest_path(i);
    int cnt = 0;
    ll acc = 0;
    while (q--)
    {
        int x, y;
        ll ret = INF;
        x = read(), y = read();
        for (int pt = 1; pt <= k; pt++)
            ret = min(dist_opp[pt][x] + dist[pt][y], ret);
        if (ret < INF)
            cnt++, acc += ret;
    }
    printf("%d\n%lld", cnt, acc);
    return 0;
}