// P1434.cpp
#include <iostream>
#include <algorithm>
#include <queue>

using namespace std;

const int maxn = 20000;
int map[200][200];
int R, C;
int F[200][200];

int dfs(int x, int y)
{
    if (F[x][y] != 1)
        return F[x][y];
    int ret = 0;
    if (x > 1 && map[x - 1][y] < map[x][y])
        ret = max(dfs(x - 1, y) + 1, ret);
    if (x < R && map[x + 1][y] < map[x][y])
        ret = max(dfs(x + 1, y) + 1, ret);
    if (y > 1 && map[x][y - 1] < map[x][y])
        ret = max(dfs(x, y - 1) + 1, ret);
    if (y < C && map[x][y + 1] < map[x][y])
        ret = max(dfs(x, y + 1) + 1, ret);
    F[x][y] = max(F[x][y], ret);
    return ret;
}

int main()
{
    fill(F[0], F[0] + 200 * 200, 1);
    cin >> R >> C;
    for (int i = 1; i <= R; i++)
        for (int j = 1; j <= C; j++)
            cin >> map[i][j];
    int ans = 0;
    for (int i = 1; i <= R; i++)
        for (int j = 1; j <= C; j++)
            ans = max(ans, dfs(i, j));
    cout << ans + 1;
    return 0;
}