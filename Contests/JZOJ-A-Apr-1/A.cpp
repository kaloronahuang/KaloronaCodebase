// A.cpp
#include <bits/stdc++.h>
#define pr pair<int, int>

using namespace std;

const int MAX_N = 10;
const int dirx[4] = {0, 0, -1, 1}, diry[4] = {-1, 1, 0, 0};

int n, mp[MAX_N][MAX_N], tail;
bool connected[MAX_N][MAX_N], col[MAX_N];

pr q[MAX_N << 15];

void bfs(int color)
{
    for (int i = 1; i <= tail; i++)
    {
        int x = q[i].first, y = q[i].second;
        for (int dir = 0; dir < 4; dir++)
        {
            int dstx = x + dirx[dir], dsty = y + diry[dir];
            if (dstx <= n && dstx >= 1 && dsty <= n && dsty >= 1 && mp[dstx][dsty] == color && connected[dstx][dsty] == false)
            {
                connected[dstx][dsty] = true;
                q[++tail] = make_pair(dstx, dsty);
            }
        }
    }
}

bool dfs(int dep, int limit)
{
    if (tail == n * n)
        return true;
    memset(col, 0, sizeof(col));
    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= n; j++)
            if (connected[i][j] == false)
                col[mp[i][j]] = true;
    int tt = 0;
    for (int i = 0; i <= 5; i++)
        if (col[i])
            tt++;
    if (tt + dep > limit)
        return false;
    int tp = tail;
    for (int i = 0; i <= 5; i++)
    {
        bfs(i);
        if (tail == tp)
            continue;
        if (dfs(dep + 1, limit))
            return true;
        for (int j = tp + 1; j <= tail; j++)
            connected[q[j].first][q[j].second] = false;
        tail = tp;
    }
    return false;
}

int main()
{
    while (scanf("%d", &n) && n != 0)
    {
        for (int i = 1; i <= n; i++)
            for (int j = 1; j <= n; j++)
                scanf("%d", &mp[i][j]);
        bool flag = true;
        for (int limit = 0; limit <= 64; limit++)
        {
            memset(connected, 0, sizeof(connected));
            q[1] = make_pair(1, 1);
            connected[1][1] = true;
            tail = 1;
            bfs(mp[1][1]);
            if (dfs(0, limit))
            {
                printf("%d\n", limit);
                break;
            }
        }
    }
    return 0;
}