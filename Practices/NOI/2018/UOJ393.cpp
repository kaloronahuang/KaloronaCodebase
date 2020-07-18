// UOJ393.cpp
#include <bits/stdc++.h>

using namespace std;

const int MAX_N = 6e5 + 200, MAX_E = 4e5 + 200;

typedef pair<int, int> pii;

int T, n, m, head[MAX_N], current, lastans, dist[MAX_N], mem[MAX_N];
int prod[MAX_N], level[MAX_N], up[20][MAX_N];
bool vis[MAX_N];
vector<int> G[MAX_N];

inline char nc()
{
    static char buf[10000000], *p1 = buf, *p2 = buf;
    return p1 == p2 && (p2 = (p1 = buf) + fread(buf, 1, 10000000, stdin), p1 == p2) ? EOF : *p1++;
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
} edges[MAX_E << 1];

struct segment
{
    int u, v, l, a;
    bool operator<(const segment &rhs) const { return a < rhs.a; }
} segs[MAX_E];

int find(int x) { return mem[x] == x ? x : mem[x] = find(mem[x]); }

void addpath(int src, int dst, int weight)
{
    edges[current].to = dst, edges[current].nxt = head[src];
    edges[current].weight = weight, head[src] = current++;
}

void shortest_path()
{
    memset(dist, 0x7f, sizeof(dist));
    memset(vis, false, sizeof(vis));
    priority_queue<pii> pq;
    pq.push(make_pair(0, 1)), dist[1] = 0;
    while (!pq.empty())
    {
        int u = pq.top().second;
        pq.pop();
        if (vis[u])
            continue;
        vis[u] = true;
        for (int i = head[u]; i != -1; i = edges[i].nxt)
            if (dist[edges[i].to] == 0x7f7f7f7f || dist[edges[i].to] > dist[u] + edges[i].weight)
                dist[edges[i].to] = dist[u] + edges[i].weight, pq.push(make_pair(-dist[edges[i].to], edges[i].to));
    }
}

int main()
{
    // freopen("ex_return6.in", "r", stdin);
    T = read();
    while (T--)
    {
        memset(head, -1, sizeof(head));
        memset(prod, 0, sizeof(prod));
        memset(up, 0, sizeof(up)), memset(level, 0, sizeof(level));
        n = read(), m = read(), current = lastans = 0;
        for (int i = 1, u, v, l, a; i <= m; i++)
        {
            u = read(), v = read(), l = read(), a = read();
            addpath(u, v, l), addpath(v, u, l);
            segs[i] = segment{u, v, l, a};
        }
        shortest_path();
        sort(segs + 1, segs + 1 + m), reverse(segs + 1, segs + 1 + m);
        for (int i = 1; i <= n + m; i++)
            mem[i] = i, G[i].clear();
        for (int i = 1; i <= n; i++)
            prod[i] = dist[i], level[i] = 2e9;
        for (int i = 1; i <= m; i++)
        {
            int cpt = i + n;
            int u = find(segs[i].u), v = find(segs[i].v);
            G[cpt].push_back(u), G[cpt].push_back(v);
            prod[cpt] = min(prod[u], prod[v]), level[cpt] = segs[i].a;
            up[0][u] = up[0][v] = cpt;
            mem[u] = mem[v] = cpt;
        }
        for (int i = 1; i < 20; i++)
            for (int j = 1; j <= n + m; j++)
                up[i][j] = up[i - 1][up[i - 1][j]];
        int q = read(), k = read(), s = read();
        while (q--)
        {
            int u = read(), p = read();
            u = (0LL + u + 1LL * k * lastans - 1) % n + 1;
            p = (0LL + p + 1LL * k * lastans) % (s + 1);
            for (int i = 19; i >= 0; i--)
                if (level[up[i][u]] > p)
                    u = up[i][u];
            printf("%d\n", lastans = prod[u]);
        }
    }
    return 0;
}