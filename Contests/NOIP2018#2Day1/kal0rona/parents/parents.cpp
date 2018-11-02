// parents.cpp
#include <iostream>
#include <cstdio>

using namespace std;

const int maxn = 300;
int N, M, K;
int limit;
int WX = 0;
int a[maxn][maxn];
bool b[maxn][maxn];

bool validiate(int x, int y)
{
    return !(!b[x][y] || (a[x][y] == 0 && K < 10) || a[x][y] == -1);
}

void check()
{
    if (K > limit)
        K = limit;
}

void open(int x, int y)
{
    b[x][y] = true;
    b[x - 1][y] = b[x + 1][y] = true;
    b[x][y + 1] = b[x][y - 1] = true;
    b[x - 1][y - 1] = b[x + 1][y - 1] = true;
    b[x - 1][y + 1] = b[x + 1][y + 1] = true;
}

bool exploit(int x, int y)
{
    if (!validiate(x, y))
        return false;
    if (a[x][y] == 0)
        // WX block;
        WX += 10, K -= 10;
    else
        K += a[x][y];
    a[x][y] = -1;
    open(x, y);
    check();
    return true;
}

int main()
{
    freopen("parents.in", "r", stdin);
    freopen("parents.out", "w", stdout);
    cin >> N >> M >> K;
    limit = K;
    for (int i = 1; i <= N; i++)
        for (int j = 1; j <= M; j++)
            cin >> a[i][j];
    for (int i = 1; i <= N; i++)
        for (int j = 1; j <= M; j++)
        {
            int inp;
            cin >> inp;
            b[i][j] = !(inp == 0);
        }
    int t;
    cin >> t;
    bool flag = false;
    for (int i = 0; i < t; i++)
    {
        int x, y;
        cin >> x >> y;
        if (!exploit(x, y))
            flag = true;
    }
    if (flag)
    {
        cout << -1 << " " << -1;
        return 0;
    }
    cout << K << " " << WX << endl;
    return 0;
}