// CH2501.cpp
#include <iostream>
#include <cstdio>
#include <cstring>
#include <queue>
#define pr pair<int, int>
using namespace std;
const int maxn = 1010;
const int dx[4] = {0, 0, -1, 1}, dy[4] = {-1, 1, 0, 0};
char mat[maxn][maxn];
int res[maxn][maxn], N, M;
bool validiate(pr now) { return now.first > 0 && now.first <= N && now.second > 0 && now.second <= M; }
void bfs()
{
    queue<pr> qpool;
    memset(res, -1, sizeof(res));
    for (int i = 1; i <= N; i++)
        for (int j = 1; j <= M; j++)
            if (mat[i][j] == '1')
                qpool.push(make_pair(i, j)), res[i][j] = 0;
    while (!qpool.empty())
    {
        pr curt = qpool.front();
        qpool.pop();
        for (int dir = 0; dir < 4; dir++)
        {
            pr now = curt;
            now.first += dx[dir], now.second += dy[dir];
            if (!validiate(now))
                continue;
            if (res[now.first][now.second] == -1 ||
                res[now.first][now.second] > res[curt.first][curt.second] + 1)
                res[now.first][now.second] = res[curt.first][curt.second] + 1, qpool.push(now);
        }
    }
}
int main()
{
    scanf("%d%d", &N, &M);
    for (int i = 1; i <= N; i++)
        for (int j = 1; j <= M; j++)
            cin >> mat[i][j];
    bfs();
    for (int i = 1; i <= N; i++)
    {
        for (int j = 1; j <= M; j++)
            printf("%d ", res[i][j]);
        printf("\n");
    }
    return 0;
}