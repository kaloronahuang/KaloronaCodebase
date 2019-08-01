// P2324.cpp
#include <bits/stdc++.h>

using namespace std;

const int MAX_N = 6;
const int dirx[8] = {-1, -1, 1, 1, 2, 2, -2, -2}, diry[8] = {-2, 2, -2, 2, -1, 1, -1, 1};

int T, mp[MAX_N][MAX_N], n = 5, px, py, org[MAX_N][MAX_N];

bool ida_star(int dep, int est, int limit, int x, int y)
{
    if (dep + est > limit)
        return false;
    if (dep == limit)
        return true;
    for (int dir = 0; dir < 8; dir++)
    {
        int dstx = x + dirx[dir], dsty = y + diry[dir];
        if (dstx <= n && dstx >= 1 && dsty <= n && dsty >= 1)
        {
            int tmp = -((mp[x][y] != org[x][y]) + (mp[dstx][dsty] != org[dstx][dsty]));
            swap(mp[x][y], mp[dstx][dsty]);
            tmp += (mp[x][y] != org[x][y]) + (mp[dstx][dsty] != org[dstx][dsty]);
            if (ida_star(dep + 1, est + tmp, limit, dstx, dsty))
                return true;
            swap(mp[x][y], mp[dstx][dsty]);
        }
    }
    return false;
}

int main()
{
    scanf("%d", &T), getchar(), getchar();
    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= n; j++)
            if (i == 3 && j == 3)
                org[i][j] = -1;
            else
                org[i][j] = (float(i) / float(j) > 1.0) ? 0 : 1;
    org[4][4] = org[5][5] = 0;
    while (T--)
    {
        int h = 0;
        // input;
        for (int i = 1; i <= n; i++)
        {
            for (int j = 1; j <= n; j++)
            {
                mp[i][j] = getchar();
                if (mp[i][j] == '*')
                    px = i, py = j, mp[i][j] = -1;
                else
                    mp[i][j] -= '0';
            }
            getchar(), getchar();
        }
        for (int i = 1; i <= n; i++)
            for (int j = 1; j <= n; j++)
                if (mp[i][j] != org[i][j])
                    h++;
        bool flag = true;
        for (int limit = 0; limit <= 15; limit++)
            if (ida_star(0, h - 1, limit, px, py))
            {
                printf("%d\n", limit), flag = false;
                break;
            }
        if (flag)
            puts("-1");
    }
    return 0;
} // P2324.cpp