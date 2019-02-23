// C.cpp
#include <bits/stdc++.h>
using namespace std;
const int MAX_N = 560, dirx[4] = {-1, 1, 0, 0}, diry[4] = {0, 0, -1, 1}, INF = 0x3f3f3f3f;
int n, m, sx, sy, ex, ey;
char mp[MAX_N][MAX_N];
int dang[MAX_N][MAX_N], ans = 0;
bool vis[MAX_N][MAX_N];
void dfs(int x, int y, int acc)
{
    if (ans > acc)
        return;
    if (x > n || y > m || x < 1 || y < 1)
        return;
    acc = min(acc, dang[x][y]);
    vis[x][y] = true;
    if (x == ex && y == ey)
    {
        ans = max(acc, ans), vis[x][y] = false;
        return;
    }
    int tx, ty, key = -1;
    for (int i = 0; i < 4; i++)
    {
        int dstx = x + dirx[i], dsty = y + diry[i];
        if (dang[dstx][dsty] > key && !vis[dstx][dsty] && !((dstx > n || dsty > m || dstx < 1 || dsty < 1)))
            tx = dstx, ty = dsty, key = dang[dstx][dsty];
    }
    if (key != -1)
        dfs(tx, ty, acc);
    for (int i = 0; i < 4; i++)
    {
        int dstx = x + dirx[i], dsty = y + diry[i];
        if (dstx != tx && dsty != ty && !vis[dstx][dsty] && !((dstx > n || dsty > m || dstx < 1 || dsty < 1)))
            dfs(dstx, dsty, acc);
    }
    vis[x][y] = false;
}
int main()
{
    memset(dang, 0x3f, sizeof(dang));
    scanf("%d%d", &n, &m);
    for (int i = 1; i <= n; i++)
        scanf("%s", mp[i] + 1);
    queue<int> qx, qy, qd;
    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= m; j++)
            if (mp[i][j] == '+')
                qx.push(i), qy.push(j), qd.push(0);
            else if (mp[i][j] == 'V')
                sx = i, sy = j;
            else if (mp[i][j] == 'J')
                ex = i, ey = j;
    while (!qx.empty())
    {
        int x = qx.front(), y = qy.front(), z = qd.front();
        qx.pop(), qy.pop(), qd.pop();
        if (dang[x][y] < z || (x > n || y > m || x < 1 || y < 1))
            continue;
        dang[x][y] = z;
        for (int i = 0; i < 4; i++)
        {
            int dstx = x + dirx[i], dsty = y + diry[i];
            if (dstx > n || dsty > m || dstx < 1 || dsty < 1)
                continue;
            qx.push(dstx), qy.push(dsty), qd.push(z + 1);
        }
    }
    dfs(sx, sy, INF);
    printf("%d", ans);
    return 0;
}