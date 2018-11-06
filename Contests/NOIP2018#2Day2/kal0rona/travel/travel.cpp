// cave.cpp
#include <iostream>
#include <algorithm>
#include <queue>
#include <cstdio>
#include <vector>
#include <queue>
#define ll long long
using namespace std;

ll read()
{
    ll x = 0, f = 1;
    char c = getchar();
    for (; c < '0' || c > '9'; c = getchar())
        if (c == '-')
            f = -1;
    for (; c >= '0' && c <= '9'; c = getchar())
        x = (x << 3) + (x << 1) + c - '0';
    return x * f;
}

const int mod = 998244353;
const int maxn = 1200000;
const int maxm = 1020000 << 2;
struct edge
{
    int src, to, next;
    ll w;
    bool operator<(const edge &e) const
    {
        return w > e.w;
    }
} edges[maxm];
int n, m;
int head[maxn], mem[maxn], deg[maxn];
int current = 0;
queue<edge> epool;
ll pow2[maxn];

int Find(int x)
{
    if (mem[x] == x)
        return x;
    return mem[x] = Find(mem[x]);
}

void Unite(int x, int y)
{
    if (Find(x) != Find(y))
        mem[Find(x)] = mem[Find(y)];
}

void addpath(int src, int dst, int weight)
{
    edges[current].src = src;
    edges[current].to = dst;
    edges[current].w = weight;
    edges[current].next = head[src];
    epool.push(edges[current]);
    head[src] = current++;
}

vector<edge> G[maxn];
int Fa[maxn];

void bfs()
{
    queue<int> pool;
    pool.push(1);
    while (!pool.empty())
    {
        int curt = pool.front();
        pool.pop();
        int siz = G[curt].size();
        for (int i = 0; i < siz; i++)
            if (G[curt][i].to != Fa[curt])
                Fa[G[curt][i].to] = curt, pool.push(G[curt][i].to);
    }
}

void MST()
{
    while (!epool.empty())
    {
        edge curt = epool.front();
        epool.pop();
        if (Find(curt.src) == Find(curt.to))
            continue;
        G[curt.src].push_back(curt);
        G[curt.to].push_back(edge{curt.to, curt.src, curt.next, curt.w});
        Unite(curt.src, curt.to);
    }
}

ll ans;

void DFS(int u)
{
    int siz = G[u].size();
    for (int i = 0; i < siz; i++)
        if (G[u][i].to != Fa[u])
            DFS(G[u][i].to);
    if (deg[u] % 2 == 1)
        for (int i = 0; i < siz; i++)
            if (G[u][i].to == Fa[u])
            {
                deg[G[u][i].to]++;
                ans = ans % mod + G[u][i].w % mod, ans %= mod;
                break;
            }
}

int main()
{
    n = read(), m = read();
    fill(head, head + n + 10, -1);
    for (int i = 0; i < m; i++)
        mem[i] = i;
    pow2[0] = 1;
    for (int i = 1; i <= m; i++)
        pow2[i] = pow2[i - 1] * 2 % mod;
    for (int i = 1; i <= m; i++)
    {
        ll s, d, w;
        s = read(), d = read();
        w = pow2[i];
        addpath(s, d, w), addpath(d, s, w);
        deg[s]++, deg[d]++;
        ans = ans % mod + w % mod, ans %= mod;
    }
    MST();
    bfs();
    DFS(1);
    cout << ans;
    return 0;
}