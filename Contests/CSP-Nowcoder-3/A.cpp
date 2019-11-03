// A.cpp
#include <bits/stdc++.h>
#define ll long long

using namespace std;

const int MAX_N = 1e6 + 200;

int n, m, current, head[MAX_N], val[MAX_N];
ll glimit, gans;

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
    gans += 1LL * val[u];
    if (gans >= m)
        return;
    for (int i = head[u]; i != -1; i = edges[i].nxt)
        if (edges[i].to != fa && glimit >= edges[i].weight)
        {
            dfs(edges[i].to, u);
            if (gans >= m)
                return;
        }
}

bool check(int mid)
{
    glimit = mid, gans = 0;
    dfs(1, 0);
    return gans >= m;
}

int main()
{
    memset(head, -1, sizeof(head));
    scanf("%d%d", &n, &m);
    for (int i = 2; i <= n; i++)
        scanf("%d", &val[i]);
    for (int i = 1, u, v, w; i <= n - 1; i++)
        scanf("%d%d%d", &u, &v, &w), addpath(u, v, w), addpath(v, u, w);
    int l = 0, r = 1e9, ans = 0;
    while (l <= r)
    {
        int mid = (l + r) >> 1;
        if (check(mid))
            r = mid - 1, ans = mid;
        else
            l = mid + 1;
    }
    printf("%d", ans);
    return 0;
}