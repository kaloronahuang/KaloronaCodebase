// B.cpp
#include <bits/stdc++.h>

using namespace std;

const int MAX_N = 15;

const int dirx[4] = {1, 0, -1, 0}, diry[4] = {0, 1, 0, -1};

int weight[MAX_N][MAX_N][MAX_N], h, n, m, ki[MAX_N], tag[MAX_N][MAX_N][MAX_N];
int f[MAX_N][MAX_N][1 << MAX_N], g[MAX_N][MAX_N][1 << MAX_N];
bool vis[MAX_N][MAX_N][1 << MAX_N];
struct node
{
    int x, y, status;
};
queue<node> q;

int main()
{
    /*
	freopen("treasure.in", "r", stdin);
	freopen("treasure.out", "w", stdout);
    */
    scanf("%d%d%d", &h, &n, &m);
    for (int i = 1; i <= h; i++)
        for (int j = 1; j <= n; j++)
            for (int k = 1; k <= m; k++)
                scanf("%d", &weight[i][j][k]);

    for (int i = 1; i <= h; i++)
    {
        scanf("%d", &ki[i]);
        for (int k = 1, x, y; k <= ki[i]; k++)
            scanf("%d%d", &x, &y), tag[i][x][y] = k;
    }

    int ans = 0x3f3f3f3f;

    for (int i = 1; i <= h; i++)
    {
        memcpy(g, f, sizeof(g));
        memset(f, 60, sizeof(f)), memset(vis, false, sizeof(vis));
        int INF = f[0][0][0];
        for (int j = 1; j <= n; j++)
            for (int k = 1; k <= m; k++)
            {
                f[j][k][1] = g[j][k][(1 << (ki[i - 1] + 1)) - 1] + weight[i][j][k];
                // printf("DBG : making f[%d][%d][%d] to %d, %d\n", j, k, 1, g[j][k][(1 << (ki[i - 1] + 1)) - 1] + weight[i][j][k], weight[i][j][k]);
                if (tag[i][j][k])
                {
                    f[j][k][1 << (tag[i][j][k])] = weight[i][j][k];
                    // printf("DBG : Tag[%d][%d][%d] is activated, f[%d][%d][%d] is %d\n", i, j, k, j, k, 1 << (tag[i][j][k]), f[j][k][1 << (tag[i][j][k])]);
                }
            }
        for (int stat = 1; stat < (1 << (ki[i] + 1)); stat++)
        {
            while (!q.empty())
                q.pop();
            for (int j = 1; j <= n; j++)
                for (int k = 1; k <= m; k++)
                {
                    for (int x = stat & (stat - 1); x; x = stat & (x - 1))
                        if (f[j][k][x] + f[j][k][stat ^ x] - weight[i][j][k] < f[j][k][stat])
                            f[j][k][stat] = f[j][k][x] + f[j][k][stat ^ x] - weight[i][j][k];
                    if (f[j][k][stat] < INF)
                        vis[j][k][stat] = true, q.push(node{j, k, stat});
                }
            while (!q.empty())
            {
                node curt = q.front();
                q.pop();
                int x = curt.x, y = curt.y, status = curt.status;
                for (int dir = 0; dir < 4; dir++)
                {
                    int dx = x + dirx[dir], dy = y + diry[dir];
                    if (dx != 0 && dy != 0 && dx <= n && dy <= m)
                    {
                        if (f[x][y][status] + weight[i][dx][dy] < f[dx][dy][status])
                        {
                            f[dx][dy][status] = f[x][y][status] + weight[i][dx][dy];
                            if (!vis[dx][dy][status])
                                vis[dx][dy][status] = true, q.push(node{dx, dy, status});
                        }
                    }
                }
                vis[x][y][status] = false;
            }
        }
    }
    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= m; j++)
            ans = min(ans, f[i][j][(1 << (ki[h] + 1)) - 1]);
    printf("%d", ans);
    return 0;
}