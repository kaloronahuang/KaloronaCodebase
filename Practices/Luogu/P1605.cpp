// P1605.cpp
#include <iostream>
#include <algorithm>
#include <cstring>

using namespace std;

int n, m, t;
int map[10][10];
bool vis[10][10];
int sx, sy, fx, fy;
int ans = 0;

void DFS(int x, int y)
{
    if (map[x][y] == 1)
        return;
    if (x == fx && y == fy)
    {
        ++ans;
        return;
    }
    vis[x][y] = true;
    if (x < n && !vis[x + 1][y])
        DFS(x + 1, y);
    if (x > 1 && !vis[x - 1][y])
        DFS(x - 1, y);
    if (y < m && !vis[x][y + 1])
        DFS(x, y + 1);
    if (y > 1 && !vis[x][y - 1])
        DFS(x, y - 1);
    vis[x][y] = false;
}

int main()
{
    cin >> n >> m >> t;
    memset(map, 0, sizeof(map));
    memset(vis, false, sizeof(map));
    cin >> sx >> sy >> fx >> fy;
    int x, y;
    for (int i = 0; i < t; i++)
        cin >> x >> y, map[x][y] = 1;
    DFS(sx, sy);
    cout << ans;
    return 0;
}