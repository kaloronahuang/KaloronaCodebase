// LOJ6223.cpp
#include <bits/stdc++.h>

using namespace std;

typedef long long ll;
typedef pair<ll, int> pli;

const int MAX_N = 2e5 + 200, dx[4] = {0, 0, -1, 1}, dy[4] = {-1, 1, 0, 0};

int n, max_dep, A, B, C, head[MAX_N], current, mp[110][110];
ll dist[MAX_N];
bool vis[MAX_N];

struct edge
{
    int to, nxt, weight;
} edges[MAX_N << 4];

void addpath(int src, int dst, int weight)
{
    edges[current].to = dst, edges[current].nxt = head[src];
    edges[current].weight = weight, head[src] = current++;
}

int getId(int depth, int x, int y) { return depth * n * n + (x - 1) * n + y; }

void shortest_path(int src)
{
    memset(dist, 0x3f, sizeof(dist));
    priority_queue<pli> pq;
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

int main()
{
    memset(head, -1, sizeof(head));
    scanf("%d%d%d%d%d", &n, &max_dep, &A, &B, &C);
    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= n; j++)
            scanf("%d", &mp[i][j]);
    // build graph;
    for (int ptx = 1; ptx <= n; ptx++)
        for (int pty = 1; pty <= n; pty++)
            for (int d = 0; d < 4; d++)
                for (int rem = 1; rem <= max_dep; rem++)
                {
                    // just drive there;
                    int id = getId(rem, ptx, pty);
                    int dstx = ptx + dx[d], dsty = pty + dy[d];
                    if (dstx > n || dstx < 1 || dsty > n || dsty < 1)
                        continue;
                    int dst_id, cost = 0;
                    if (mp[dstx][dsty])
                        dst_id = getId(max_dep, dstx, dsty), cost += A;
                    else
                        dst_id = getId(rem - 1, dstx, dsty);
                    if (dstx < ptx || dsty < pty)
                        cost += B;
                    addpath(id, dst_id, cost);

                    // drive there with new station set;
                    dst_id = getId(max_dep, dstx, dsty), cost = A + C;
                    if (dstx < ptx || dsty < pty)
                        cost += B;
                    addpath(id, dst_id, cost);
                }

    shortest_path(getId(max_dep, 1, 1));
    ll ans = 0x7fffffffffffffff;
    for (int i = 0; i <= max_dep; i++)
        ans = min(ans, dist[getId(i, n, n)]);
    printf("%lld\n", ans);
    return 0;
}