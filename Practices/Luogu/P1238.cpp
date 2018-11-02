// P1238.cpp
#include <iostream>
#include <sstream>
#include <vector>
#include <cstring>

using namespace std;

const int maxn = 20;
int m, n;
int map[maxn][maxn];
bool vis[maxn][maxn];
int sx, sy;
int ex, ey;

vector<string> ans;

string toString(int a)
{
    stringstream ss;
    ss << a;
    return ss.str();
}

string helper_func(int a, int b) { return "(" + toString(a) + "," + toString(b) + ")"; }

void DFS(int x, int y, string prev)
{
    if (x == ex && y == ey)
    {
        ans.push_back(prev + helper_func(ex, ey));
        return;
    }
    vis[x][y] = true;
    string key = helper_func(x, y) + "->";
    // left;
    if (y > 1 && !vis[x][y - 1] && map[x][y - 1] == 1)
        DFS(x, y - 1, prev + key);
    // up;
    if (x > 1 && !vis[x - 1][y] && map[x - 1][y] == 1)
        DFS(x - 1, y, prev + key);
    // right;
    if (y < n && !vis[x][y + 1] && map[x][y + 1] == 1)
        DFS(x, y + 1, prev + key);
    // down;
    if (x < m && !vis[x + 1][y] && map[x + 1][y] == 1)
        DFS(x + 1, y, prev + key);
    vis[x][y] = false;
}

int main()
{
    memset(vis, false, sizeof(vis));
    ios::sync_with_stdio(false);
    cin >> m >> n;
    for (int i = 1; i <= m; i++)
        for (int j = 1; j <= n; j++)
            cin >> map[i][j];
    cin >> sx >> sy >> ex >> ey;
    DFS(sx, sy, "");
    int siz = ans.size();
    if (siz == 0)
        cout << "-1" << endl;
    else
        for (int i = 0; i < siz; i++)
            cout << ans[i] << endl;
    return 0;
}