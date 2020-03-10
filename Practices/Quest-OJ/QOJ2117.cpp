// QOJ2117.cpp
#include <bits/stdc++.h>

using namespace std;

const int MAX_N = 30, MAX_M = 1e5 + 200, mod = 12015858;

typedef pair<int, int> pii;

int n, upper, head[MAX_N], current, dp[MAX_N][MAX_M], pre[MAX_N][MAX_M];
pii xi[MAX_N], yi[MAX_N];

struct edge
{
    int to, nxt;
} edges[MAX_N << 1];

void addpath(int src, int dst)
{
    edges[current].to = dst, edges[current].nxt = head[src];
    head[src] = current++;
}

bool read(int &x)
{
    x = 0;
    char c = getchar();
    while ((c < '0' || c > '9') && (c < 'a' || c > 'z'))
        c = getchar();
    if (!isdigit(c))
        return (x = c - 'a' + 1, 1);
    while (isdigit(c))
        x = (x << 3) + (x << 1) + c - '0', c = getchar();
    return 0;
}

void dfs(int u)
{
    for (int i = head[u]; i != -1; i = edges[i].nxt)
        dfs(edges[i].to);
    int lft_bound = 1, rig_bound = upper;
    if (xi[u].first == 0)
        lft_bound = xi[u].second;
    if (yi[u].first == 0)
        rig_bound = yi[u].second;
    for (int j = lft_bound; j <= rig_bound; j++)
    {
        dp[u][j] = 1;
        for (int i = head[u]; i != -1; i = edges[i].nxt)
            if (xi[edges[i].to].first == 1)
                dp[u][j] = (0LL + 1LL * dp[u][j] * (pre[edges[i].to][yi[edges[i].to].second] + mod - pre[edges[i].to][j - 1]) % mod) % mod;
            else
                dp[u][j] = (0LL + 1LL * dp[u][j] * (pre[edges[i].to][j] + mod - pre[edges[i].to][xi[edges[i].to].second - 1]) % mod) % mod;
    }
    for (int i = 1; i <= upper; i++)
        pre[u][i] = (0LL + pre[u][i - 1] + dp[u][i]) % mod;
}

int main()
{
    memset(head, -1, sizeof(head));
    scanf("%d", &n);
    for (int i = 1; i <= n; i++)
        xi[i].first = read(xi[i].second), yi[i].first = read(yi[i].second);
    for (int i = 1; i <= n; i++)
    {
        if (xi[i].first == 0)
            upper = max(upper, xi[i].second);
        if (yi[i].first == 0)
            upper = max(upper, yi[i].second);
    }
    for (int i = 1; i <= n; i++)
        if (xi[i].first)
            addpath(xi[i].second, i);
        else if (yi[i].first)
            addpath(yi[i].second, i);
    int ans = 1;
    for (int i = 1; i <= n; i++)
        if (xi[i].first + yi[i].first == 0)
            dfs(i), ans = 1LL * ans * pre[i][upper] % mod;
    printf("%d\n", ans);
    return 0;
}