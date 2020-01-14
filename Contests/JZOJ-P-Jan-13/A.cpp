// A.cpp
#include <bits/stdc++.h>

using namespace std;

const int MAX_N = 2e5 + 200;
typedef long long ll;
const ll INF = 0x3f3f3f3f3f3f3f3f;

int n, m, head[MAX_N], current, dep[MAX_N], T, START, END, deg[MAX_N];
int pre[MAX_N], flow[MAX_N];
ll dist[MAX_N];
bool vis[MAX_N];

struct edge
{
    int to, nxt, weight, cost;
} edges[MAX_N << 2];

struct path
{
    int u, v, d;
} paths[MAX_N];

vector<edge> G[MAX_N];

void fileIO()
{
    freopen("tree.in", "r", stdin);
    freopen("tree.out", "w", stdout);
}

inline char nc()
{
    static char buf[1000000], *p1 = buf, *p2 = buf;
    return p1 == p2 && (p2 = (p1 = buf) + fread(buf, 1, 1000000, stdin), p1 == p2) ? EOF : *p1++;
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

void addpath(int src, int dst, int weight, int cost)
{
    edges[current].to = dst, edges[current].nxt = head[src];
    edges[current].weight = weight, edges[current].cost = cost;
    head[src] = current++;
}

void addtube(int src, int dst, int weight, int cost)
{
    addpath(src, dst, weight, cost);
    addpath(dst, src, 0, -cost);
}

bool spfa_min(int src)
{
    memset(dist, 0x3f, sizeof(dist));
    memset(vis, false, sizeof(vis));
    memset(flow, 0, sizeof(flow));
    queue<int> q;
    q.push(src), vis[src] = true, dist[src] = 0;
    flow[src] = 0x3f3f3f3f;
    while (!q.empty())
    {
        int u = q.front();
        q.pop();
        vis[u] = false;
        for (int i = head[u]; i != -1; i = edges[i].nxt)
            if (dist[edges[i].to] > dist[u] + edges[i].cost && edges[i].weight > 0)
            {
                dist[edges[i].to] = dist[u] + edges[i].cost;
                flow[edges[i].to] = min(edges[i].weight, flow[u]);
                pre[edges[i].to] = i;
                if (!vis[edges[i].to])
                    q.push(edges[i].to), vis[edges[i].to] = true;
            }
    }
    return flow[END] != 0;
}

ll mcmf()
{
    ll ans = 0;
    while (spfa_min(START))
    {
        ans += dist[END] * flow[END];
        int pt = END, i = pre[pt];
        while (pt != START)
        {
            edges[i].weight -= flow[END], edges[i ^ 1].weight += flow[END];
            pt = edges[i ^ 1].to, i = pre[pt];
        }
    }
    return ans;
}

void dfs(int u, int fa)
{
    dep[u] = dep[fa] + 1;
    for (int i = 0, siz_ = G[u].size(); i < siz_; i++)
        if (G[u][i].to != fa)
            dfs(G[u][i].to, u), addtube(G[u][i].to, u, G[u][i].weight, 0);
}

void initialize()
{
    memset(head, -1, sizeof(head)), current = 0;
    for (int i = 1; i <= n; i++)
        G[i].clear();
    START = 0, END = n + 1, memset(deg, 0, sizeof(deg));
}

int main()
{
    T = read();
    while (T--)
    {
        n = read(), m = read();
        initialize();
        for (int i = 1, u, v, w; i <= n - 1; i++)
        {
            u = read(), v = read(), w = read();
            G[u].push_back(edge{v, 0, w, 0}), G[v].push_back(edge{u, 0, w, 0});
        }
        dfs(1, 0);
        ll answer = 0;
        for (int i = 1, u, v, w; i <= m; i++)
        {
            u = read(), v = read(), w = read();
            if (dep[u] < dep[v])
                swap(u, v);
            answer += w, addtube(u, v, 1, w);
            addtube(START, u, 1, 0), addtube(v, END, 1, 0);
        }
        printf("%lld\n", answer - mcmf());
    }
    return 0;
}