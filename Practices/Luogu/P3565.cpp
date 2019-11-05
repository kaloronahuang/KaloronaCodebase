// P3565.cpp
#include <bits/stdc++.h>
typedef long long ll;
using namespace std;

const int MAX_N = 5e3 + 200;

int head[MAX_N], current, n, dep[MAX_N], bucket[MAX_N], mx_dep, tot1[MAX_N], tot2[MAX_N];
int deg[MAX_N];
ll gans;

struct edge
{
    int to, nxt;
} edges[MAX_N << 1];

void addpath(int src, int dst)
{
    edges[current].to = dst, edges[current].nxt = head[src];
    head[src] = current++;
}

void dfs(int u, int fa)
{
    dep[u] = dep[fa] + 1, bucket[dep[u]]++, mx_dep = max(mx_dep, dep[u]);
    for (int i = head[u]; i != -1; i = edges[i].nxt)
        if (edges[i].to != fa)
            dfs(edges[i].to, u);
}

void process(int u)
{
    memset(tot1, 0, sizeof(tot1)), memset(tot2, 0, sizeof(tot2));
    dep[u] = 0, mx_dep = 0;
    for (int i = head[u]; i != -1; i = edges[i].nxt)
    {
        memset(bucket, 0, sizeof(bucket));
        dfs(edges[i].to, u);
        for (int j = 1; j <= mx_dep; j++)
        {
            gans += bucket[j] * tot2[j];
            tot2[j] += tot1[j] * bucket[j];
            tot1[j] += bucket[j];
        }
    }
}

int main()
{
    memset(head, -1, sizeof(head));
    scanf("%d", &n);
    for (int i = 1, u, v; i <= n - 1; i++)
        scanf("%d%d", &u, &v), addpath(u, v), addpath(v, u), deg[u]++, deg[v]++;
    for (int i = 1; i <= n; i++)
        if (deg[i] >= 3)
            process(i);
    printf("%lld", gans);
    return 0;
}