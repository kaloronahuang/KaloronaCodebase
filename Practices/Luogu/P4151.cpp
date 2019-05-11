// P4151.cpp
#include <bits/stdc++.h>
#define ll long long
using namespace std;

const int MAX_N = 55000, MAX_M = 210000;

int head[MAX_N], current, n, m;
ll dist[MAX_N], linear_base[70];
bool vis[MAX_N];

struct edge
{
    int to, nxt;
    ll weight;
} edges[MAX_M << 1];

void addpath(int src, int dst, ll weight)
{
    edges[current].to = dst, edges[current].nxt = head[src];
    edges[current].weight = weight, head[src] = current++;
}

void insert(ll num)
{
    for (int i = 63; i >= 0; i--)
        if ((num >> i) & 1)
        {
            if (linear_base[i] == 0)
                return (void)(linear_base[i] = num);
            num ^= linear_base[i];
        }
}

ll query(ll x)
{
    for (int i = 63; i >= 0; i--)
        if ((x ^ linear_base[i]) > x)
            x ^= linear_base[i];
    return x;
}

void dfs(int u, ll acc)
{
    dist[u] = acc, vis[u] = true;

    for (int i = head[u]; i != -1; i = edges[i].nxt)
        if (!vis[edges[i].to])
            dfs(edges[i].to, acc ^ edges[i].weight);
        else
            insert(acc ^ edges[i].weight ^ dist[edges[i].to]);
}

int main()
{
    memset(head, -1, sizeof(head));
    scanf("%d%d", &n, &m);
    for (ll i = 1, x, y, z; i <= m; i++)
        scanf("%lld%lld%lld", &x, &y, &z), addpath(x, y, z), addpath(y, x, z);
    dfs(1, 0);
    printf("%lld", query(dist[n]));
    return 0;
}