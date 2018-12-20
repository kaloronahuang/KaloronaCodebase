// P1522.cpp
#include <iostream>
#include <algorithm>
#include <queue>
#include <cstdio>
#include <cmath>
#include <cstring>
#include <vector>
#define pr pair<int, int>
#define dpr pair<double, int>
using namespace std;
const int MX_N = 200, INF = 0x3f3f3f3f;
int n;
char mat[MX_N][MX_N];
double G[MX_N][MX_N], ripe[MX_N][MX_N];
pr points[MX_N];
bool vis[MX_N];
double pow2(double num) { return num * num; }
double getDist(pr a, pr b) { return sqrt(pow2(a.first - b.first) + pow2(a.second - b.second)); }
double dfs(int u)
{
    if (vis[u])
        return 0;
    vis[u] = true;
    double res = 0;
    for (int i = 1; i <= n; i++)
        if (ripe[u][i] != INF && i != u)
            res = max(res, max(ripe[u][i], dfs(i)));
    return res;
}
int main()
{
    scanf("%d", &n);
    int x, y;
    for (int i = 1; i <= n; i++)
        scanf("%d%d", &x, &y), points[i] = make_pair(x, y);
    for (int i = 1; i <= n; i++)
    {
        scanf("%s", mat[i] + 1);
        for (int j = 1; j <= n; j++)
            if (mat[i][j] == '1')
                G[i][j] = getDist(points[i], points[j]);
            else if (i != j)
                G[i][j] = (double)INF;
    }
    for (int k = 1; k <= n; k++)
        for (int i = 1; i <= n; i++)
            for (int j = 1; j <= n; j++)
                G[i][j] = min(G[i][j], G[i][k] + G[k][j]);
    double ans = (double)INF;
    for (int i = 1; i <= n; i++)
        for (int j = i + 1; j <= n; j++)
            if (i != j && G[i][j] == INF)
            {
                memcpy(ripe, G, sizeof(G));
                memset(vis, false, sizeof(vis));
                ripe[i][j] = ripe[j][i] = getDist(points[i], points[j]);
                for (int a = 1; a <= n; a++)
                    for (int b = 1; b <= n; b++)
                        ripe[a][b] = min(ripe[a][b], ripe[a][i] + ripe[i][j] + ripe[j][b]);
                double res = dfs(i);
                ans = min(ans, res);
            }
    printf("%.6f", ans);
    return 0;
}