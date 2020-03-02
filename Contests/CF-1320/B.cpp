// B.cpp
#include <bits/stdc++.h>

using namespace std;

const int MAX_N = 2e5 + 200;

typedef pair<int, int> pii;

int n, m, head[MAX_N], current, route[MAX_N], rtot, dist[MAX_N], deg[MAX_N];
pii org[MAX_N];

struct edge
{
    int to, nxt;
} edges[MAX_N << 1];

void addpath(int src, int dst)
{
    edges[current].to = dst, edges[current].nxt = head[src];
    head[src] = current++;
}

void bfs(int src)
{
    memset(dist, -1, sizeof(dist));
    queue<int> q;
    q.push(src), dist[src] = 0;
    while (!q.empty())
    {
        int u = q.front();
        q.pop();
        for (int i = head[u]; i != -1; i = edges[i].nxt)
            if (dist[edges[i].to] == -1)
                dist[edges[i].to] = dist[u] + 1, q.push(edges[i].to);
    }
}

int main()
{
    memset(head, -1, sizeof(head)), current = 0;
    scanf("%d%d", &n, &m);
    for (int i = 1, u, v; i <= m; i++)
        scanf("%d%d", &u, &v), addpath(v, u), org[i] = make_pair(u, v);
    scanf("%d", &rtot);
    for (int i = 1; i <= rtot; i++)
        scanf("%d", &route[i]);
    int start_pos = route[1], end_pos = route[rtot];
    bfs(end_pos);
    memset(head, -1, sizeof(head)), current = 0;
    for (int i = 1; i <= m; i++)
        if (dist[org[i].first] == dist[org[i].second] + 1)
            addpath(org[i].first, org[i].second), deg[org[i].second]++;
    int min_ans = 0, max_ans = 0;
    for (int i = 1; i < rtot; i++)
    {
        int pt = route[i], cnt1 = 0, cnt2 = 0;
        for (int e = head[pt]; e != -1; e = edges[e].nxt)
            if (edges[e].to != route[i + 1])
                cnt1++;
            else
                cnt2++;
        if (cnt2 == 0)
            min_ans++;
        if (cnt1 > 0 || cnt2 == 0)
            max_ans++;
    }
    printf("%d %d\n", min_ans, max_ans);
    return 0;
}