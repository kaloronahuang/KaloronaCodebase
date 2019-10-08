// P5024.cpp
#include <bits/stdc++.h>
#define ll long long

using namespace std;

const int MAX_N = 1e5 + 200;
const ll INF = 0x3f3f3f3f3f3f3f3f;

int head[MAX_N], current, n, q, val[MAX_N], dep[MAX_N], fa[20][MAX_N], m;
ll f[2][2][20][MAX_N], dp[MAX_N][2];
char typ[10];

struct edge
{
    int to, nxt;
} edges[MAX_N << 1];

void addpath(int src, int dst)
{
    edges[current].to = dst, edges[current].nxt = head[src];
    head[src] = current++;
}

// checked;
// at predfs(int);
void predfs(int u)
{
    dep[u] = dep[fa[0][u]] + 1, dp[u][1] = val[u], f[0][0][0][u] = INF;
    for (int i = 1; i <= 19; i++)
        fa[i][u] = fa[i - 1][fa[i - 1][u]];
    for (int i = head[u]; i != -1; i = edges[i].nxt)
        if (edges[i].to != fa[0][u])
        {
            fa[0][edges[i].to] = u;
            predfs(edges[i].to);
            dp[u][0] += dp[edges[i].to][1];
            dp[u][1] += min(dp[edges[i].to][0], dp[edges[i].to][1]);
        }
}

void dfs(int u)
{
    // not selecting the node u but the father node;
    f[1][0][0][u] = dp[fa[0][u]][0] - dp[u][1];
    f[0][1][0][u] = f[1][1][0][u] = dp[fa[0][u]][1] - min(dp[u][0], dp[u][1]);
    // to process the chains bypassing the LCA:
    for (int i = 1; (1 << i) < dep[u]; i++)
    {
        // merging two chains from 2 situations: mid point chosen or not;
        int mid_point = fa[i - 1][u];
        f[0][0][i][u] = min(f[0][0][i - 1][u] + f[0][0][i - 1][mid_point], f[0][1][i - 1][u] + f[1][0][i - 1][mid_point]);
        f[0][1][i][u] = min(f[0][0][i - 1][u] + f[0][1][i - 1][mid_point], f[0][1][i - 1][u] + f[1][1][i - 1][mid_point]);
        f[1][0][i][u] = min(f[1][0][i - 1][u] + f[0][0][i - 1][mid_point], f[1][1][i - 1][u] + f[1][0][i - 1][mid_point]);
        f[1][1][i][u] = min(f[1][0][i - 1][u] + f[0][1][i - 1][mid_point], f[1][1][i - 1][u] + f[1][1][i - 1][mid_point]);
    }

    for (int i = head[u]; i != -1; i = edges[i].nxt)
        if (edges[i].to != fa[0][u])
            dfs(edges[i].to);
}

ll query(int x, int y, bool togA, bool togB)
{
    if (dep[x] < dep[y])
        swap(x, y), swap(togA, togB);
    ll x_enable = INF, y_enable = INF;
    ll x_disable = INF, y_disable = INF, answer;
    ll ans0 = INF, ans1 = INF;
    int lca;

    if (togA)
        x_enable = dp[x][1];
    else
        x_disable = dp[x][0];

    if (togB)
        y_enable = dp[y][1];
    else
        y_disable = dp[y][0];

    for (int i = 19; i >= 0; i--)
        if (dep[fa[i][x]] >= dep[y])
        {
            ll xdis = x_disable, xen = x_enable;
            x_disable = min(xdis + f[0][0][i][x], xen + f[1][0][i][x]);
            x_enable = min(xdis + f[0][1][i][x], xen + f[1][1][i][x]);
            x = fa[i][x];
        }
    if (x == y)
        lca = x, togB ? ans1 = x_enable : ans0 = x_disable;
    else
    {
        for (int i = 19; i >= 0; i--)
            if (fa[i][x] != fa[i][y])
            {
                ll xdis = x_disable, xen = x_enable;
                ll ydis = y_disable, yen = y_enable;
                x_disable = min(xdis + f[0][0][i][x], xen + f[1][0][i][x]);
                x_enable = min(xdis + f[0][1][i][x], xen + f[1][1][i][x]);
                y_disable = min(ydis + f[0][0][i][y], yen + f[1][0][i][y]);
                y_enable = min(ydis + f[0][1][i][y], yen + f[1][1][i][y]);
                x = fa[i][x], y = fa[i][y];
            }
        lca = fa[0][x];
        ans0 = dp[lca][0] - dp[x][1] - dp[y][1] + x_enable + y_enable;
        ans1 = dp[lca][1] - min(dp[x][1], dp[x][0]) - min(dp[y][0], dp[y][1]) + min(x_enable, x_disable) + min(y_enable, y_disable);
    }
    if (lca == 1)
        answer = min(ans1, ans0);
    else
    {
        for (int i = 19; i >= 0; i--)
            if (dep[lca] - (1 << i) > 1)
            {
                ll tmp0 = ans0, tmp1 = ans1;
                ans0 = min(tmp0 + f[0][0][i][lca], tmp1 + f[1][0][i][lca]);
                ans1 = min(tmp0 + f[0][1][i][lca], tmp1 + f[1][1][i][lca]);
                lca = fa[i][lca];
            }
        answer = min(dp[1][0] - dp[lca][1] + ans1, dp[1][1] - min(dp[lca][0], dp[lca][1]) + min(ans1, ans0));
    }
    return answer >= INF ? -1 : answer;
}

int main()
{
    memset(head, -1, sizeof(head));
    scanf("%d%d%s", &n, &m, typ + 1);
    for (int i = 1; i <= n; i++)
        scanf("%d", &val[i]);
    for (int i = 1, u, v; i <= n - 1; i++)
        scanf("%d%d", &u, &v), addpath(u, v), addpath(v, u);

    predfs(1), dfs(1);
    while (m--)
    {
        int u, v, x, y;
        scanf("%d%d%d%d", &u, &x, &v, &y);
        printf("%lld\n", query(u, v, x, y));
    }
    return 0;
}