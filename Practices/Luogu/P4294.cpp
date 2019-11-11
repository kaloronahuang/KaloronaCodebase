// P4294.cpp
#include <bits/stdc++.h>
#define pr pair<int, int>

using namespace std;

const int MAX_N = 11, INF = 0x3f3f3f3f, dx[4] = {0, 0, 1, -1}, dy[4] = {1, -1, 0, 0};

int mat[MAX_N * MAX_N], n, m, k, dp[MAX_N * MAX_N][(1 << MAX_N)], root;
bool vis[MAX_N * MAX_N], ans[MAX_N][MAX_N];

int getId(int x, int y) { return x * m + y; }

struct node
{
    int x, y, subset;
} pre[MAX_N * MAX_N][1 << MAX_N];
queue<pr> q;

bool vaildate(int x, int y) { return x < n && x >= 0 && y < m && y >= 0; }

void spfa(int stat)
{
    while (!q.empty())
    {
        pr u = q.front();
        q.pop(), vis[getId(u.first, u.second)] = false;
        for (int dir = 0; dir < 4; dir++)
        {
            int dstx = u.first + dx[dir], dsty = u.second + dy[dir];
            if (vaildate(dstx, dsty) && dp[getId(dstx, dsty)][stat] > dp[getId(u.first, u.second)][stat] + mat[getId(dstx, dsty)])
            {
                dp[getId(dstx, dsty)][stat] = dp[getId(u.first, u.second)][stat] + mat[getId(dstx, dsty)];
                if (!vis[getId(dstx, dsty)])
                    vis[getId(dstx, dsty)], q.push(make_pair(dstx, dsty));
                pre[getId(dstx, dsty)][stat] = node{u.first, u.second, stat};
            }
        }
    }
}

void dfs(int x, int y, int stat)
{
    if (pre[getId(x, y)][stat].subset == 0)
        return;
    ans[x][y] = true;
    if (pre[getId(x, y)][stat].x == x && pre[getId(x, y)][stat].y == y)
        dfs(x, y, stat ^ pre[getId(x, y)][stat].subset);
    dfs(pre[getId(x, y)][stat].x, pre[getId(x, y)][stat].y, pre[getId(x, y)][stat].subset);
}

int main()
{
    scanf("%d%d", &n, &m);
    memset(dp, 0x3f, sizeof(dp));
    for (int i = 0; i < n; i++)
        for (int j = 0; j < m; j++)
        {
            scanf("%d", &mat[getId(i, j)]);
            if (mat[getId(i, j)] == 0)
                dp[getId(i, j)][1 << (k++)] = 0, root = getId(i, j);
        }
    for (int stat = 1; stat < (1 << k); stat++)
    {
        for (int i = 0; i < n; i++)
            for (int j = 0; j < m; j++)
            {
                int id = getId(i, j);
                for (int substat = stat & (stat - 1); substat; substat = stat & (substat - 1))
                    if (dp[id][stat] > dp[id][substat] + dp[id][stat ^ substat] - mat[id])
                    {
                        dp[id][stat] = dp[id][substat] + dp[id][stat ^ substat] - mat[id];
                        pre[getId(i, j)][stat] = node{i, j, substat};
                    }
                if (dp[id][stat] < INF)
                    q.push(make_pair(i, j)), vis[getId(i, j)] = true;
            }
        spfa(stat);
    }
    printf("%d\n", dp[root][(1 << k) - 1]);
    dfs(root / m, root % m, (1 << k) - 1);
    for (int i = 0; i < n; i++, puts(""))
        for (int j = 0; j < m; j++)
        {
            int id = getId(i, j);
            if (mat[id] == 0)
                putchar('x');
            else
                putchar(ans[i][j] ? 'o' : '_');
        }
    return 0;
}