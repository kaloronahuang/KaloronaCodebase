// F.cpp
#include <bits/stdc++.h>

using namespace std;

const int MAX_N = 660;

int head[MAX_N], current, n, m;
double dp[MAX_N];
bool vis[MAX_N];

struct edge
{
    int to, nxt;
    bool tag;
} edges[MAX_N * MAX_N << 1];

void addpath(int src, int dst)
{
    edges[current].to = dst, edges[current].nxt = head[src];
    head[src] = current++;
}

void process(int block)
{
    for (int u = n - 1; u >= 1; u--)
    {
        int deg = 0;
        double max_son = 0, sum = 0;
        for (int i = head[u]; i != -1; i = edges[i].nxt)
            sum += dp[edges[i].to], max_son = max(max_son, dp[edges[i].to]), deg++;
        if (block == u && deg >= 2)
            deg--, sum -= max_son;
        dp[u] = sum / deg + 1;
    }
}

int main()
{
    memset(head, -1, sizeof(head));
    scanf("%d%d", &n, &m);
    for (int i = 1, u, v; i <= m; i++)
        scanf("%d%d", &u, &v), addpath(u, v);
    double ans = 0x3f3f3f3f;
    for (int i = 0; i <= n - 1; i++)
        process(i), ans = min(ans, dp[1]);
    printf("%.8lf", ans);
    return 0;
}