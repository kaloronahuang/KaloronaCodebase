// P2491.cpp
#include <bits/stdc++.h>

using namespace std;

const int MAX_N = 3e5 + 200;

typedef long long ll;

int n, S, head[MAX_N], current, dist[MAX_N], A, B, up[MAX_N];
ll sdist[MAX_N];
bool vis[MAX_N];
vector<int> chain;

struct edge
{
    int to, nxt, weight;
} edges[MAX_N << 1];

void addpath(int src, int dst, int weight)
{
    edges[current].to = dst, edges[current].nxt = head[src];
    edges[current].weight = weight, head[src] = current++;
}

void dfs(int u, int fa)
{
    up[u] = fa;
    for (int i = head[u]; i != -1; i = edges[i].nxt)
        if (edges[i].to != fa)
        {
            dist[edges[i].to] = dist[u] + edges[i].weight;
            dfs(edges[i].to, u);
        }
}

ll sdfs(int u, int fa)
{
    ll ret = 0;
    for (int i = head[u]; i != -1; i = edges[i].nxt)
        if (edges[i].to != fa && !vis[edges[i].to])
            ret = max(ret, sdfs(edges[i].to, u) + edges[i].weight);
    return ret;
}

bool check(ll threshold)
{
    int lptr = 0, siz = chain.size(), rptr;
    while (lptr + 1 < siz && dist[chain[lptr + 1]] <= threshold)
        lptr++;
    rptr = lptr;
    while (rptr + 1 < siz && dist[chain[rptr + 1]] - dist[chain[lptr]] <= S)
        rptr++;
    return dist[chain[siz - 1]] - dist[chain[rptr]] <= threshold;
}

int main()
{
    memset(head, -1, sizeof(head));
    scanf("%d%d", &n, &S);
    for (int i = 1, u, v, w; i <= n - 1; i++)
        scanf("%d%d%d", &u, &v, &w), addpath(u, v, w), addpath(v, u, w);
    dist[1] = 0, dfs(1, 0), A = max_element(dist + 1, dist + 1 + n) - dist;
    dist[A] = 0, dfs(A, 0), B = max_element(dist + 1, dist + 1 + n) - dist;
    int u = B;
    while (u)
        vis[u] = true, chain.push_back(u), u = up[u];
    for (int v : chain)
        sdist[v] = sdfs(v, 0);
    reverse(chain.begin(), chain.end());
    ll l = *max_element(sdist + 1, sdist + 1 + n), r = dist[B], res;
    while (l <= r)
    {
        ll mid = (l + r) >> 1;
        if (check(mid))
            r = mid - 1, res = mid;
        else
            l = mid + 1;
    }
    printf("%lld\n", res);
    return 0;
}