// B.cpp
#include <bits/stdc++.h>
#define ll long long

using namespace std;

const int MAX_N = 101000;

int head[MAX_N], current, siz[MAX_N], n, dep[MAX_N], dist[MAX_N], mxdep;
int root_val, root, current_stat[MAX_N];
ll f[MAX_N << 1][2], g[MAX_N << 1][2], answer;
bool tag[MAX_N];

struct edge
{
    int to, nxt, weight;
} edges[MAX_N << 1];

void addpath(int src, int dst, int weight)
{
    edges[current].nxt = head[src], edges[current].weight = weight;
    edges[current].to = dst, head[src] = current++;
}

void __find_root(int u, int fa, int capacity)
{
    int mx_val = 0;
    siz[u] = 1;
    for (int i = head[u]; i != -1; i = edges[i].nxt)
        if (edges[i].to != fa && !tag[edges[i].to])
            __find_root(edges[i].to, u, capacity), siz[u] += siz[edges[i].to], mx_val = max(mx_val, siz[edges[i].to]);
    mx_val = max(mx_val, capacity - siz[u]);
    if (mx_val < root_val)
        root_val = mx_val, root = u;
}

int find_root(int u, int capacity)
{
    root_val = capacity, root = 0;
    __find_root(u, 0, capacity);
    return root;
}

void dfs1(int u, int fa, int dep, int way)
{
    mxdep = max(mxdep, dep);
    if (current_stat[way] > 0)
        f[way][1]++;
    else
        f[way][0]++;
    current_stat[way]++;
    for (int i = head[u]; i != -1; i = edges[i].nxt)
        if (edges[i].to != fa && !tag[edges[i].to])
            dfs1(edges[i].to, u, dep + 1, way + edges[i].weight);
    current_stat[way]--;
}

void dq(int u, int capacity)
{
    int mx = 0;
    tag[u] = true, g[MAX_N][0] = 1;
    for (int i = head[u]; i != -1; i = edges[i].nxt)
        if (!tag[edges[i].to])
        {
            mxdep = 1;
            dfs1(edges[i].to, u, 1, MAX_N + edges[i].weight);
            mx = max(mx, mxdep);
            answer += (g[MAX_N][0] - 1) * f[MAX_N][0];
            for (int d = -mxdep; d <= mxdep; d++)
                answer += (g[MAX_N - d][1] * f[MAX_N + d][1]) + (g[MAX_N - d][0] * f[MAX_N + d][1]) + (g[MAX_N - d][1] * f[MAX_N + d][0]);
            for (int d = MAX_N - mxdep; d <= MAX_N + mxdep; d++)
            {
                g[d][0] += f[d][0];
                g[d][1] += f[d][1];
                f[d][0] = f[d][1] = 0;
            }
        }
    for (int d = MAX_N - mx; d <= MAX_N + mx; d++)
        g[d][0] = g[d][1] = 0;
    for (int i = head[u]; i != -1; i = edges[i].nxt)
        if (!tag[edges[i].to])
        {
            int capacity_ = siz[edges[i].to];
            dq(find_root(edges[i].to, capacity_), capacity_);
        }
}

int main()
{
    memset(head, -1, sizeof(head));
    scanf("%d", &n);
    for (int i = 1, u, v, len; i <= n - 1; i++)
        scanf("%d%d%d", &u, &v, &len), addpath(u, v, len == 0 ? -1 : 1), addpath(v, u, len == 0 ? -1 : 1);
    dq(find_root(1, n), n);
    printf("%lld", answer);
    return 0;
}