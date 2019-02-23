// CH3803.cpp
#include <bits/stdc++.h>
using namespace std;
const int INF = 0x3f3f3f3f;
int A, B, C, D;
bool vis[20][20][20][20][5][5];
double f[20][20][20][20][5][5];
void util(int opt, int &a, int &b, int &c, int &d)
{
    if (opt == 1)
        a++;
    else if (opt == 2)
        b++;
    else if (opt == 3)
        c++;
    else if (opt == 4)
        d++;
}
double dfs(int a, int b, int c, int d, int x, int y)
{
    if (vis[a][b][c][d][x][y])
        return f[a][b][c][d][x][y];
    vis[a][b][c][d][x][y] = true;
    double &ans = f[a][b][c][d][x][y] = 0;
    int na = a, nb = b, nc = c, nd = d;
    util(x, na, nb, nc, nd), util(y, na, nb, nc, nd);
    if (na >= A && nb >= B && nc >= C && nd >= D)
        return 0;
    int w = 54 - na - nb - nc - nd;
    if (w <= 0)
        return INF;
    if (a < 13)
        ans += dfs(a + 1, b, c, d, x, y) * (13 - a) / w;
    if (b < 13)
        ans += dfs(a, b + 1, c, d, x, y) * (13 - b) / w;
    if (c < 13)
        ans += dfs(a, b, c + 1, d, x, y) * (13 - c) / w;
    if (d < 13)
        ans += dfs(a, b, c, d + 1, x, y) * (13 - d) / w;
    if (!x)
        ans += min(dfs(a, b, c, d, 1, y), min(dfs(a, b, c, d, 2, y), min(dfs(a, b, c, d, 3, y), dfs(a, b, c, d, 4, y)))) / w;
    if (!y)
        ans += min(dfs(a, b, c, d, x, 1), min(dfs(a, b, c, d, x, 2), min(dfs(a, b, c, d, x, 3), dfs(a, b, c, d, x, 4)))) / w;
    return ++ans;
}
int main()
{
    scanf("%d%d%d%d", &A, &B, &C, &D);
    double ans = dfs(0, 0, 0, 0, 0, 0);
    if (ans >= 100)
        puts("-1.000");
    else
        printf("%.3lf", ans);
    return 0;
}