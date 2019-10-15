// CF1244D.cpp
#include <bits/stdc++.h>
#define int long long
using namespace std;

const int MAX_N = 1e5 + 200;

int head[MAX_N], current, n, color[4][MAX_N], dp[MAX_N], deg[MAX_N], answer[MAX_N];

struct edge
{
    int to, nxt;
} edges[MAX_N << 1];

void addpath(int src, int dst)
{
    edges[current].to = dst, edges[current].nxt = head[src];
    head[src] = current++;
}

void dfs(int u, int fa, int A, int B)
{
    dp[u] = 0;
    for (int i = head[u]; i != -1; i = edges[i].nxt)
        if (edges[i].to != fa)
        {
            dfs(edges[i].to, u, B, A ^ B);
            dp[u] += dp[edges[i].to];
        }
    dp[u] += color[A ^ B][u];
}

void getAns(int u, int fa, int A, int B)
{
    answer[u] = A ^ B;
    for (int i = head[u]; i != -1; i = edges[i].nxt)
        if (edges[i].to != fa)
            getAns(edges[i].to, u, B, A ^ B);
}

signed main()
{
    memset(head, -1, sizeof(head));
    scanf("%lld", &n);
    for (int i = 1; i <= 3; i++)
        for (int j = 1; j <= n; j++)
            scanf("%lld", &color[i][j]);
    for (int i = 1, u, v; i < n; i++)
        scanf("%lld%lld", &u, &v), deg[u]++, deg[v]++, addpath(u, v), addpath(v, u);
    int pt = 0;
    bool flag = false;
    for (int i = 1; i <= n; i++)
        flag |= deg[i] > 2, pt = (deg[i] == 1 ? i : pt);
    if (flag)
        puts("-1"), exit(0);
    int ans = 1e18, oA, oB;
    for (int A = 1; A <= 3; A++)
        for (int B = 1; B <= 3; B++)
            if (A != B)
            {
                dfs(pt, 0, A, B);
                if (dp[pt] < ans)
                    oA = A, oB = B, ans = dp[pt];
            }
    getAns(pt, 0, oA, oB);
    printf("%lld\n", ans);
    for (int i = 1; i <= n; i++)
        printf("%lld ", answer[i]);
    return 0;
}