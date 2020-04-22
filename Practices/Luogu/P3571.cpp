// P3571.cpp
#include <bits/stdc++.h>

using namespace std;

#define int long long

const int MAX_N = 1e6 + 200;

int n, fa[MAX_N], head[MAX_N], current, dep[MAX_N], s[MAX_N], queries[MAX_N], dp[MAX_N], q[MAX_N << 1], front, back, qtot, mx_dep, query_max;

struct edge
{
    int to, nxt;
} edges[MAX_N << 1];

void addpath(int src, int dst)
{
    edges[current].to = dst, edges[current].nxt = head[src];
    head[src] = current++;
}

double slope(int x, int y) { return double(s[x + 1] - s[y + 1]) / double(x - y); }

void dfs(int u)
{
    dep[u] = dep[fa[u]] + 1, s[dep[u]]++, mx_dep = max(mx_dep, dep[u]);
    for (int i = head[u]; i != -1; i = edges[i].nxt)
        dfs(edges[i].to);
}

signed main()
{
    memset(head, -1, sizeof(head));
    scanf("%lld%lld", &n, &qtot);
    for (int i = 1; i <= qtot; i++)
        scanf("%lld", &queries[i]), query_max = max(query_max, queries[i]);
    for (int i = 2; i <= n; i++)
        scanf("%lld", &fa[i]), addpath(fa[i], i);
    dfs(1);
    for (int i = mx_dep; i >= 1; i--)
        s[i] += s[i + 1];
    for (int i = 1; i <= mx_dep; i++)
    {
        while (front < back && slope(q[back], i) > slope(q[back], q[back - 1]))
            back--;
        q[++back] = i;
    }
    for (int i = 1; i <= query_max; i++)
    {
        while (front < back && slope(q[front], q[front + 1]) > -i)
            front++;
        dp[i] = q[front] + (s[q[front] + 1] + i - 1) / i;
    }
    for (int i = 1; i <= qtot; i++)
        printf("%lld ", dp[queries[i]]);
    return 0;
}