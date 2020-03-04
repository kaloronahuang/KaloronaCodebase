// LOJ2259.cpp
#include <bits/stdc++.h>

using namespace std;

const int MAX_N = 3e4 + 200, INF = 0x3f3f3f3f;

typedef pair<int, int> pii;

int n, m, k, head[MAX_N], current, pre[MAX_N], dis[MAX_N], ans, sol, siz[MAX_N], dep[MAX_N], max_dist[MAX_N], dist[MAX_N], sols[MAX_N];
bool vis[MAX_N], tag[MAX_N];

struct edge
{
    int to, nxt, weight;
} edges[MAX_N << 2];

void addpath(int src, int dst, int weight)
{
    edges[current].to = dst, edges[current].nxt = head[src];
    edges[current].weight = weight, head[src] = current++;
}

void shortest_path(int src)
{
    memset(dis, 0x3f, sizeof(dis));
    memset(pre, -1, sizeof(pre));
    priority_queue<pii> pq;
    pq.push(make_pair(0, src)), dis[src] = 0;
    while (!pq.empty())
    {
        int u = pq.top().second;
        pq.pop();
        if (vis[u])
            continue;
        vis[u] = true;
        for (int i = head[u]; i != -1; i = edges[i].nxt)
            if (dis[edges[i].to] > dis[u] + edges[i].weight)
            {
                dis[edges[i].to] = dis[u] + edges[i].weight, pre[edges[i].to] = i;
                pq.push(make_pair(-dis[edges[i].to], edges[i].to));
            }
            else if (dis[edges[i].to] == dis[u] + edges[i].weight && pre[edges[i].to] > u)
                pre[edges[i].to] = i;
    }
}

int root, val;

int find_root(int u, int fa, int capacity)
{
    int s = 1, mx_part = 0;
    for (int i = head[u]; i != -1; i = edges[i].nxt)
        if (edges[i].to != fa && !tag[edges[i].to])
        {
            int tmp = find_root(edges[i].to, u, capacity);
            mx_part = max(mx_part, tmp), s += tmp;
        }
    if (max(capacity - s, mx_part) < val)
        root = u, val = max(capacity - s, mx_part);
    return s;
}

int find_root(int u, int capacity)
{
    val = INF, root = 0;
    find_root(u, 0, capacity);
    return root;
}

void dfs(int u, int fa)
{
    dep[u] = dep[fa] + 1, siz[u] = 1;
    if (dep[u] <= k && max_dist[k - dep[u]] != -1)
    {
        int d = max_dist[k - dep[u]] + dist[u];
        if (d > ans)
            ans = d, sol = sols[k - dep[u]];
        else if (d == ans)
            sol += sols[k - dep[u]];
    }
    for (int i = head[u]; i != -1; i = edges[i].nxt)
        if (edges[i].to != fa && !tag[edges[i].to])
        {
            dist[edges[i].to] = dist[u] + edges[i].weight;
            dfs(edges[i].to, u), siz[u] += siz[edges[i].to];
        }
}

void collect(int u, int fa)
{
    if (max_dist[dep[u]] < dist[u])
        sols[dep[u]] = 1, max_dist[dep[u]] = dist[u];
    else if (max_dist[dep[u]] == dist[u])
        sols[dep[u]]++;
    if (dep[u] < k)
        for (int i = head[u]; i != -1; i = edges[i].nxt)
            if (edges[i].to != fa && !tag[edges[i].to])
                collect(edges[i].to, u);
}

void solve(int u, int capacity)
{
    memset(max_dist, -1, sizeof(max_dist)), tag[u] = true, dep[u] = max_dist[0] = 0;
    memset(sols, 0, sizeof(sols)), sols[0] = 1;
    for (int i = head[u]; i != -1; i = edges[i].nxt)
        if (!tag[edges[i].to])
        {
            dist[edges[i].to] = edges[i].weight;
            dfs(edges[i].to, u), collect(edges[i].to, u);
        }
    for (int i = head[u]; i != -1; i = edges[i].nxt)
        if (!tag[edges[i].to])
            solve(find_root(edges[i].to, siz[edges[i].to]), siz[edges[i].to]);
}

int main()
{
    memset(head, -1, sizeof(head));
    scanf("%d%d%d", &n, &m, &k), k--;
    for (int i = 1, u, v, w; i <= m; i++)
        scanf("%d%d%d", &u, &v, &w), addpath(u, v, w), addpath(v, u, w);
    shortest_path(1), memset(head, -1, sizeof(head)), current = 0;
    for (int i = 1; i <= n; i++)
        if (pre[i] != -1)
            addpath(i, edges[pre[i] ^ 1].to, edges[pre[i] ^ 1].weight), addpath(edges[pre[i] ^ 1].to, i, edges[pre[i] ^ 1].weight);
    solve(find_root(1, n), n), printf("%d %d\n", ans, sol);
    return 0;
}