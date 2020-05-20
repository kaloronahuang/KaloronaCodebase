// CF1354E.cpp
#include <bits/stdc++.h>

using namespace std;

const int MAX_N = 5050, MAX_E = 2e5 + 200;

int n, m, ni[4], head[MAX_N], current, up[MAX_N], block_siz[MAX_N], block_root[MAX_N], tot;
int aff[MAX_N], cnt1[MAX_N], color[MAX_N], ans[MAX_N];
bool dp[MAX_N][MAX_N], stat[MAX_N];

struct edge
{
    int to, nxt;
} edges[MAX_E];

void addpath(int src, int dst)
{
    edges[current].to = dst, edges[current].nxt = head[src];
    head[src] = current++;
}

void dfs(int u, int fa, int col, int cur)
{
    aff[u] = col, cnt1[col] += cur, color[u] = cur, block_siz[col]++;
    for (int i = head[u]; i != -1; i = edges[i].nxt)
        if (aff[edges[i].to] == 0)
            dfs(edges[i].to, u, col, cur ^ 1);
}

int main()
{
    memset(head, -1, sizeof(head));
    scanf("%d%d%d%d%d", &n, &m, &ni[1], &ni[2], &ni[3]);
    for (int i = 1, u, v; i <= m; i++)
        scanf("%d%d", &u, &v), addpath(u, v), addpath(v, u);
    for (int i = 1; i <= n; i++)
        if (aff[i] == 0)
            dfs(i, 0, ++tot, 0), block_root[tot] = i;
    for (int u = 1; u <= n; u++)
        for (int i = head[u]; i != -1; i = edges[i].nxt)
            if (color[edges[i].to] == color[u])
                puts("NO"), exit(0);
    dp[0][0] = true;
    for (int i = 1; i <= tot; i++)
        for (int j = ni[2]; j >= 0; j--)
            dp[i][j] = (j >= cnt1[i] ? dp[i - 1][j - cnt1[i]] : false) || (j - (block_siz[i] - cnt1[i]) >= 0 ? dp[i - 1][j - (block_siz[i] - cnt1[i])] : false);
    if (!dp[tot][ni[2]])
        puts("NO"), exit(0);
    int tot_siz = ni[2];
    for (int i = tot; i >= 1; i--)
    {
        bool flag1 = (tot_siz >= cnt1[i] ? dp[i - 1][tot_siz - cnt1[i]] : false);
        // bool flag2 = (tot_siz - (block_siz[i] - cnt1[i]) >= 0 ? dp[tot_siz - (block_siz[i] - cnt1[i])] : false);
        if (flag1)
            stat[i] = true, tot_siz -= cnt1[i];
        else
            stat[i] = false, tot_siz -= (block_siz[i] - cnt1[i]);
    }
    puts("YES");
    for (int i = 1; i <= n; i++)
    {
        if ((color[i] == 1 && stat[aff[i]] == true) || (color[i] == 0 && stat[aff[i]] == false))
            ans[i] = 2;
        else if (ni[1] > 0)
            ans[i] = 1, ni[1]--;
        else
            ans[i] = 3, ni[3]--;
        printf("%d", ans[i]);
    }
    puts("");
    return 0;
}