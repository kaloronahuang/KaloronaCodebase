// P1613.cpp
#include <bits/stdc++.h>

using namespace std;

const int MAX_N = 55;

int dist[MAX_N][MAX_N], n, m;
bool stat[64][MAX_N][MAX_N];

int main()
{
    scanf("%d%d", &n, &m);
    memset(dist, 0x3f, sizeof(dist));
    for (int i = 1, u, v; i <= m; i++)
        scanf("%d%d", &u, &v), dist[u][v] = 1, stat[0][u][v] = true;
    for (int bit = 1; bit < 64; bit++)
        for (int k = 1; k <= n; k++)
            for (int i = 1; i <= n; i++)
                for (int j = 1; j <= n; j++)
                    if (stat[bit - 1][i][k] && stat[bit - 1][k][j])
                        dist[i][j] = 1, stat[bit][i][j] = true;
    for (int k = 1; k <= n; k++)
        for (int i = 1; i <= n; i++)
            for (int j = 1; j <= n; j++)
                dist[i][j] = min(dist[i][k] + dist[k][j], dist[i][j]);
    printf("%d", dist[1][n]);
    return 0;
}