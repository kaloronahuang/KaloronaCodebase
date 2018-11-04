// travel.cpp
#include <iostream>
#include <algorithm>
#include <cstdio>
using namespace std;

const int maxn = 500100;
const int mod = 998244353;

struct edge
{
    int to, weight, next;
} edges[maxn << 1];
int head[maxn];
int current = 1;
int n, m;

int read()
{
    int x = 0, f = 1;
    char c = getchar();
    for (; c < '0' || c > '9'; c = getchar())
        if (c == '-')
            f = -1;
    for (; c >= '0' && c <= '9'; c = getchar())
        x = (x << 3) + (x << 1) + c - '0';
    return x * f;
}

void addpath(int src, int dst, int w)
{
    edges[current].to = dst;
    edges[current].next = head[src];
    edges[current].weight = (edges[w - 1].weight * 2) % mod;
    head[src] = current++;
}

int ans = 0x7fffffff;
bool vis[maxn];
int real = 0;

bool validiate()
{
    for (int i = 1; i <= m; i++)
        if (!vis[i])
            return false;
    return true;
}

void dfs(int u, int prev)
{
    if (real > 3 * m)
        return;
    if (prev > ans)
        return;
    if (u == 1 && validiate())
    {
        ans = min(ans, prev);
        return;
    }
    for (int i = head[u]; i != -1; i = edges[i].next)
    {
        real++;
        vis[i] = true;
        dfs(edges[i].to, prev + edges[i].weight);
        vis[i] = false;
        real--;
    }
}

int main()
{
    freopen("travel.in", "r", stdin);
    freopen("travel.out", "w", stdout);
    fill(head, head + maxn, -1);
    edges[0].weight = 1;
    n = read(), m = read();
    for (int i = 1; i <= m; i++)
    {
        int src = read();
        int dst = read();
        addpath(src, dst, i);
        addpath(dst, src, i);
    }
    dfs(1, 0);
    cout << ans;
    return 0;
}