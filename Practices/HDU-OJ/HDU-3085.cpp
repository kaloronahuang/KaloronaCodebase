// HDU-3085.cpp
#include <iostream>
#include <cstdio>
#include <queue>
#include <cmath>
#include <cstring>
#define pr pair<int, int>
using namespace std;
const int maxn = 810;
int N, M;
bool statb[maxn][maxn], statg[maxn][maxn];
char map[maxn][maxn];
const int dx[4] = {0, 0, -1, 1}, dy[4] = {-1, 1, 0, 0};
pr ghs[2];
int getDist(pr pt1, pr pt2)
{
    return abs(pt1.first - pt2.first) + abs(pt1.second - pt2.second);
}
bool validiate(pr pt, int tim)
{
    if (pt.first <= 0 || pt.first > N || pt.second <= 0 || pt.second > M)
        return false;
    if (abs(pt.first - ghs[0].first) + abs(pt.second - ghs[0].second) <= 2 * tim)
        return false;
    if (abs(pt.first - ghs[1].first) + abs(pt.second - ghs[1].second) <= 2 * tim)
        return false;
    if (map[pt.first][pt.second] == 'X')
        return false;
    return true;
}
int bfs()
{
    int cnt = 0;
    memset(statb, false, sizeof(statb)), memset(statg, false, sizeof(statg));
    // go to parse;
    queue<pr> boys, girls;
    for (int i = 1; i <= N; i++)
        for (int j = 1; j <= M; j++)
            if (map[i][j] == 'M')
                boys.push(make_pair(i, j)), statb[i][j] = true;
            else if (map[i][j] == 'G')
                girls.push(make_pair(i, j)), statg[i][j] = true;
            else if (map[i][j] == 'Z')
                ghs[cnt++] = make_pair(i, j);
    int tim = 0;
    while ((!boys.empty()) || (!girls.empty()))
    {
        tim++;
        // process seperately;
        int bsiz;
        int tims = 3;
        while (tims--)
        {
            bsiz = boys.size();
            while (bsiz--)
            {
                pr tp = boys.front();
                boys.pop();
                int x = tp.first, y = tp.second;
                if (!validiate(make_pair(x, y), tim))
                    continue;
                for (int dir = 0; dir < 4; dir++)
                    if (validiate(make_pair(x + dx[dir], y + dy[dir]), tim) && !statb[x + dx[dir]][y + dy[dir]])
                    {
                        statb[x + dx[dir]][y + dy[dir]] = true;
                        boys.push(make_pair(x + dx[dir], y + dy[dir]));
                    }
            }
        }
        int gsiz = girls.size();
        while (gsiz--)
        {
            pr tp = girls.front();
            girls.pop();
            int x = tp.first, y = tp.second;
            if (!validiate(make_pair(x, y), tim))
                continue;
            for (int dir = 0; dir < 4; dir++)
                if (validiate(make_pair(x + dx[dir], y + dy[dir]), tim) && !statg[x + dx[dir]][y + dy[dir]])
                {
                    if (statb[x + dx[dir]][y + dy[dir]])
                        return tim;
                    statg[x + dx[dir]][y + dy[dir]] = true;
                    girls.push(make_pair(x + dx[dir], y + dy[dir]));
                }
        }
    }
    return -1;
}
int main()
{
    int T;
    scanf("%d", &T);
    while (T--)
    {
        scanf("%d%d", &N, &M);
        for (int i = 1; i <= N; i++)
            scanf("%s", map[i] + 1);
        printf("%d\n", bfs());
    }
    return 0;
}