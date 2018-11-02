// P1649.cpp
#include <iostream>

using namespace std;

char map[110][110];
bool mak[110][110];
int n;
bool gotIt = false;

struct point
{
    int x, y;
    point() {}
    point(int a, int b) : x(a), y(b) {}
    point operator+(const point &p) const
    {
        return point(x + p.x, y + p.y);
    }
} pa, pb;

void init()
{
    cin >> n;
    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= n; j++)
        {
            cin >> map[i][j];
            mak[i][j] = false;
            if (map[i][j] == 'A')
                pa = point(i, j);
            if (map[i][j] == 'B')
                pb = point(i, j);
        }
}

int ans = 0x7fffffff;
point ps[4] = {point(1, 0), point(0, 1), point(-1, 0), point(0, -1)};

bool check(point a)
{
    return !(a.x > n || a.x < 1 || a.y > n || a.y < 1 || map[a.x][a.y] == 'x' || mak[a.x][a.y]);
}

void DFS(point pos, int tot, int prev)
{
    if (tot >= ans)
        return;
    if (pos.x == pb.x && pos.y == pb.y)
    {
        ans = min(ans, tot);
        gotIt = true;
        return;
    }
    int key = ((prev == -1) ? 0 : 1);
    point up = ps[2] + pos;
    point down = ps[0] + pos;
    point right = ps[1] + pos;
    point left = ps[3] + pos;
    mak[pos.x][pos.y] = true;
    if (check(down))
        DFS(down, tot + ((prev == 1) ? 0 : key), 1);
    if (check(up))
        DFS(up, tot + ((prev == 1) ? 0 : key), 1);
    if (check(left))
        DFS(left, tot + ((prev == 2) ? 0 : key), 2);
    if (check(right))
        DFS(right, tot + ((prev == 2) ? 0 : key), 2);
    mak[pos.x][pos.y] = false;
}

int main()
{
    init();
    DFS(pa, 0, -1);
    if (gotIt)
        cout << ans;
    else
        cout << -1;
    return 0;
}