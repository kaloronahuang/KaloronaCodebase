// P3457.cpp
#include <bits/stdc++.h>
#define pr pair<int, int>

using namespace std;

const int MAX_N = 2020, dx[4] = {0, 0, 1, -1}, dy[4] = {1, -1, 0, 0};

int n, m, mat[MAX_N][MAX_N], water[MAX_N][MAX_N], tot, answer;
bool vis[MAX_N][MAX_N];

struct city
{
    int x, y, val;
    bool operator<(const city &rhs) const { return val < rhs.val; }
} cities[MAX_N * MAX_N];

void floodfill(int orgx, int orgy)
{
    answer++, vis[orgx][orgy] = true;
    deque<pr> q;
    q.push_back(make_pair(orgx, orgy)), water[orgx][orgy] = abs(mat[orgx][orgy]);
    while (!q.empty())
    {
        int x = q.front().first, y = q.front().second;
        q.pop_front();
        for (int dir = 0; dir < 4; dir++)
        {
            int dstx = x + dx[dir], dsty = y + dy[dir];
            if (dstx <= n && dstx >= 1 && dsty <= m && dsty >= 1 && (mat[dstx][dsty] <= 0 || water[x][y] <= mat[dstx][dsty]))
            {
                int h = max(water[x][y], abs(mat[dstx][dsty]));
                if (h < water[dstx][dsty])
                {
                    water[dstx][dsty] = h;
                    if (!vis[dstx][dsty])
                    {
                        vis[dstx][dsty] = true;
                        if (!q.empty() && water[dstx][dsty] <= water[q.front().first][q.front().second])
                            q.push_front(make_pair(dstx, dsty));
                        else
                            q.push_back(make_pair(dstx, dsty));
                    }
                }
            }
        }
        vis[x][y] = false;
    }
}

int main()
{
    memset(water, 0x3f, sizeof(water));
    scanf("%d%d", &n, &m);
    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= m; j++)
        {
            scanf("%d", &mat[i][j]);
            if (mat[i][j] > 0)
                cities[++tot] = city{i, j, mat[i][j]};
        }
    sort(cities + 1, cities + 1 + tot);
    for (int i = 1; i <= tot; i++)
        if (water[cities[i].x][cities[i].y] > abs(mat[cities[i].x][cities[i].y]))
            floodfill(cities[i].x, cities[i].y);
    printf("%d\n", answer);
    return 0;
}