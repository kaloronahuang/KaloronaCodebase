// P4322.cpp
#include <bits/stdc++.h>

using namespace std;

const int MAX_N = 3030;
const double eps = 1e-5, INF = 1e9;

int head[MAX_N], current, pi[MAX_N], si[MAX_N], n, m, dfn[MAX_N], ptot, nb[MAX_N];
double dp[MAX_N][MAX_N], weight[MAX_N];

struct edge
{
    int to, nxt;
} edges[MAX_N << 1];

void addpath(int src, int dst)
{
    edges[current].to = dst, edges[current].nxt = head[src];
    head[src] = current++;
}

void dfs(int u)
{
    dfn[u] = ++ptot;
    for (int i = head[u]; i != -1; i = edges[i].nxt)
        dfs(edges[i].to);
    nb[dfn[u]] = ptot + 1;
}

bool check(double mid)
{
    for (int i = 2; i <= n; i++)
        weight[dfn[i]] = double(pi[i]) - double(mid * si[i]);
    weight[0] = 0;
    for (int i = 2; i <= n + 1; i++)
        for (int j = 0; j <= m; j++)
            dp[i][j] = -1e14;
    for (int i = 1; i <= n; i++)
        for (int j = 0; j <= m; j++)
            // check if it's valid;
            if (dp[i][j] > -1e9)
            {
                dp[i + 1][j + 1] = max(dp[i + 1][j + 1], dp[i][j] + weight[i]);
                dp[nb[i]][j] = max(dp[nb[i]][j], dp[i][j]);
            }
    return dp[n + 1][m] > eps;
}

int main()
{
    memset(head, -1, sizeof(head));
    scanf("%d%d", &m, &n), m++, n++;
    for (int i = 2, fa; i <= n; i++)
        scanf("%d%d%d", &si[i], &pi[i], &fa), addpath(++fa, i);
    for (int i = 1; i <= m; i++)
        dp[1][i] = -1e14;
    dp[1][0] = 0, dfs(1);
    double l = 0, r = 1e5, ans;
    while (l + eps < r)
    {
        double mid = (l + r) / 2.0;
        if (check(mid))
            l = mid, ans = mid;
        else
            r = mid;
    }
    printf("%.3lf\n", ans);
    return 0;
}