// P4768.cpp
#include <bits/stdc++.h>
#define pr pair<int, int>
using namespace std;

const int MAX_N = 4e5 + 2000, MAX_M = 4e5 + 2000, INF = 0x3f3f3f3f;

int T, n, m;
int head_graph[MAX_N], head_tree[MAX_N], current_graph, current_tree, buff[MAX_N];
int ptot, fa[20][MAX_N], val[MAX_N], smallest[MAX_N], dist[MAX_N];
bool vis[MAX_N];

struct edge
{
    int from, to, nxt, weight, height;
    bool operator<(const edge &e) const { return height > e.height; }
} source[MAX_M], edges[MAX_M << 1], tree[MAX_N];

int find(int x) { return x == buff[x] ? x : buff[x] = find(buff[x]); }

void addpath(int src, int dst, int weight, int height)
{
    edges[current_graph].to = dst, edges[current_graph].height = height;
    edges[current_graph].nxt = head_graph[src], edges[current_graph].weight = weight;
    head_graph[src] = current_graph++;
}

void addbranch(int src, int dst)
{
    tree[current_tree].to = dst, tree[current_tree].nxt = head_tree[src];
    head_tree[src] = current_tree++;
}

void djisktra()
{
    memset(dist, 0x3f, sizeof(dist)), memset(vis, false, sizeof(vis));
    priority_queue<pr> pq;
    pq.push(make_pair(0, 1)), dist[1] = 0;
    while (!pq.empty())
    {
        int u = pq.top().second;
        pq.pop();
        if (vis[u])
            continue;
        vis[u] = true;
        for (int i = head_graph[u]; i != -1; i = edges[i].nxt)
            if (!vis[edges[i].to] && dist[edges[i].to] > dist[u] + edges[i].weight)
                dist[edges[i].to] = dist[u] + edges[i].weight, pq.push(make_pair(-dist[edges[i].to], edges[i].to));
    }
}

void dfs(int u)
{
    smallest[u] = 0;
    if (u <= n)
        smallest[u] = u;
    for (int i = 1; i < 20; i++)
        fa[i][u] = fa[i - 1][fa[i - 1][u]];
    for (int i = head_tree[u]; i != -1; i = tree[i].nxt)
    {
        fa[0][tree[i].to] = u, dfs(tree[i].to);
        if (dist[smallest[u]] > dist[smallest[tree[i].to]])
            smallest[u] = smallest[tree[i].to];
    }
}

void kruskal()
{
    sort(source + 1, source + 1 + m);
    for (int i = 1; i <= m; i++)
    {
        int a = find(source[i].from), b = find(source[i].to);
        if (a != b)
        {
            int p = ++ptot;
            buff[a] = buff[b] = buff[p] = p, val[p] = source[i].height;
            fa[0][a] = fa[0][b] = p;
            addbranch(p, a), addbranch(p, b);
        }
    }
    dist[0] = INF, dfs(ptot);
}

int find_smallest(int u, int limit)
{
    for (int i = 19; i >= 0; i--)
        if (fa[i][u] && val[fa[i][u]] > limit)
            u = fa[i][u];
    return u;
}

int main()
{
    scanf("%d", &T);
    while (T--)
    {
        scanf("%d%d", &n, &m);
        memset(head_graph, -1, sizeof(head_graph)), memset(head_tree, -1, sizeof(head_tree));
        current_graph = current_tree = 0, ptot = n;
        memset(fa, 0, sizeof(fa)), memset(val, 0, sizeof(val)), memset(smallest, 0, sizeof(smallest));
        for (int i = 1; i <= 2 * n; i++)
            buff[i] = i;
        for (int i = 1; i <= m; i++)
        {
            scanf("%d%d%d%d", &source[i].from, &source[i].to, &source[i].weight, &source[i].height);
            addpath(source[i].from, source[i].to, source[i].weight, source[i].height);
            addpath(source[i].to, source[i].from, source[i].weight, source[i].height);
        }
        djisktra(), kruskal();
        int lastans = 0, q, k, s;
        scanf("%d%d%d", &q, &k, &s);
        while (q--)
        {
            int v, p;
            scanf("%d%d", &v, &p), v = (v + k * lastans - 1) % n + 1, p = (p + k * lastans) % (s + 1);
            int ans = find_smallest(v, p);
            printf("%d\n", lastans = dist[smallest[ans]]);
        }
    }
    return 0;
}