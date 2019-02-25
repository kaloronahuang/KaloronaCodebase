// C.cpp
#include <bits/stdc++.h>
using namespace std;
const int MAX_N = 5600, dirx[4] = {-1, 1, 0, 0}, diry[4] = {0, 0, -1, 1}, INF = 0x3f3f3f3f;
int n, m, sx, sy, ex, ey;
char mp[MAX_N][MAX_N];
int dang[MAX_N][MAX_N];
bool vis[MAX_N][MAX_N];
bool check(int mid)
{
    memset(vis, 0, sizeof(vis));
    queue<int> qx, qy;
    qx.push(sx), qy.push(sy);
    if (mid == 0)
        return true;
    if (dang[sx][sy] < mid)
        return false;
    while (!qx.empty())
    {
        int x = qx.front(), y = qy.front();
        qx.pop(), qy.pop();
        vis[x][y] = true;
        if (x == ex && y == ey)
            return true;
        if (x > n || y > m || x < 1 || y < 1)
            continue;
        for (int i = 0; i < 4; i++)
        {
            int dstx = x + dirx[i], dsty = y + diry[i];
            if (dang[dstx][dsty] < mid || dstx > n || dsty > m || dstx < 1 || dsty < 1 || vis[dstx][dsty])
                continue;
            qx.push(dstx), qy.push(dsty);
        }
    }
    return false;
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
        int x = qx.front(), y = qy.front(), d = qd.front();
        qx.pop(), qy.pop(), qd.pop();
        vis[x][y] = true;
        dang[x][y] = d;
        for (int i = 0; i < 4; i++)
        {
            int dstx = x + dirx[i], dsty = y + diry[i];
            if (dstx > 0 && dsty > 0 && dstx <= n && dsty <= m && !vis[dstx][dsty])
                qx.push(dstx), qy.push(dsty), qd.push(d + 1);
        }
    }
    int l = 0, r = 50, ans;
    while (l <= r)
    {
        int mid = (l + r) >> 1;
        if (check(mid))
            l = mid + 1, ans = mid;
        else
            r = mid - 1;
    }
    printf("%d", ans);
    return 0;
}