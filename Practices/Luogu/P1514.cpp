// P1514.cpp
#include <bits/stdc++.h>

using namespace std;

const int MAX_N = 550, dx[4] = {0, 1, 0, -1}, dy[4] = {1, 0, -1, 0};

int lft[MAX_N][MAX_N], rig[MAX_N][MAX_N];
int heights[MAX_N][MAX_N], n, m;
bool vis[MAX_N][MAX_N];

void dfs(int x, int y)
{
    vis[x][y] = true;
    for (int i = 0; i < 4; i++)
    {
        int dstx = x + dx[i], dsty = y + dy[i];
        if (dstx <= n && dstx >= 1 && dsty <= m && dsty >= 1 && heights[x][y] > heights[dstx][dsty])
        {
            if (!vis[dstx][dsty])
                dfs(dstx, dsty);
            lft[x][y] = min(lft[x][y], lft[dstx][dsty]);
            rig[x][y] = max(rig[x][y], rig[dstx][dsty]);
        }
    }
}

int main()
{
    memset(lft, 0x3f, sizeof(lft));
    scanf("%d%d", &n, &m);
    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= m; j++)
            scanf("%d", &heights[i][j]);
    for (int i = 1; i <= m; i++)
        lft[n][i] = rig[n][i] = i;
    for (int i = 1; i <= m; i++)
        if (!vis[1][i])
            dfs(1, i);
    int cnt = 0;
    for (int i = 1; i <= m; i++)
        if (!vis[n][i])
            cnt++;
    if (cnt != 0)
        printf("0\n%d", cnt), exit(0);
    // segment merging;
    cnt = 0;
    int ptrL = 1;
    while (ptrL <= m)
    {
        int j = 0;
        for (int i = 1; i <= m; i++)
            if (lft[1][i] <= ptrL)
                j = max(j, rig[1][i]);
        cnt++;
        ptrL = j + 1;
    }
    puts("1"), printf("%d", cnt);
    return 0;
}