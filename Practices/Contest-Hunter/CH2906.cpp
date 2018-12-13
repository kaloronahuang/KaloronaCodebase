// CH2906.cpp
#include <cstdio>
#include <iostream>
#include <queue>
#include <cstring>
#define pr pair<int, int>
using namespace std;
const int maxn = 200;
const int dx[8] = {1, -1, -2, -2, -1, 1, 2, 2}, dy[8] = {2, 2, 1, -1, -2, -2, -1, 1};
int N, M;
pr dst;
char map[maxn][maxn];
int stat[maxn][maxn];
bool vis[maxn][maxn];
bool validiate(pr x)
{
    return x.first > 0 && x.first <= N && x.second > 0 && x.second <= M &&
           map[x.first][x.second] != '*';
}
int bfs()
{
    memset(stat, -1, sizeof(map));
    queue<pr> q;
    for (int i = 1; i <= N; i++)
        for (int j = 1; j <= M; j++)
            if (map[i][j] == 'K')
                q.push(make_pair(i, j)), stat[i][j] = 0;
            else if (map[i][j] == 'H')
                dst = make_pair(i, j);
    while (!q.empty())
    {
        pr curt = q.front();
        q.pop();
        if (curt == dst)
            return stat[curt.first][curt.second];
        if (vis[curt.first][curt.second])
            continue;
        vis[curt.first][curt.second] = true;
        for (int i = 0; i < 8; i++)
        {
            pr npr = make_pair(curt.first + dx[i], curt.second + dy[i]);
            if (validiate(npr))
            {
                stat[npr.first][npr.second] = stat[curt.first][curt.second] + 1;
                q.push(npr);
            }
        }
    }
    return -1;
}
int main()
{
    scanf("%d%d", &M, &N);
    for (int i = 1; i <= N; i++)
        scanf("%s", map[i] + 1);
    printf("%d", bfs());
    return 0;
}