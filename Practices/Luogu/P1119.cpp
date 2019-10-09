// P1119.cpp
#include <bits/stdc++.h>
#define pr pair<int, int>

using namespace std;

const int MAX_N = 220, INF = 0x3f3f3f3f;

int n, m, dist[MAX_N][MAX_N], g_time, ti[MAX_N], q;

int main()
{
    memset(dist, 0x3f, sizeof(dist));
    scanf("%d%d", &n, &m);
    for (int i = 1; i <= n; i++)
        scanf("%d", &ti[i]), dist[i][i] = 0;
    for (int i = 1, u, v, w; i <= m; i++)
    {
        scanf("%d%d%d", &u, &v, &w), u++, v++;
        dist[u][v] = dist[v][u] = min(dist[u][v], w);
    }
    scanf("%d", &q);
    int cur = 1;
    while (q--)
    {
        int x, y;
        scanf("%d%d%d", &x, &y, &g_time), x++, y++;
        while (ti[cur] <= g_time && cur <= n)
        {
            for (int i = 1; i <= n; i++)
                for (int j = 1; j <= n; j++)
                    dist[i][j] = dist[j][i] = min(dist[i][j], dist[i][cur] + dist[j][cur]);
            cur++;
        }
        if (ti[x] > g_time || ti[y] > g_time)
            puts("-1");
        else if (dist[x][y] >= INF)
            printf("-1\n");
        else
            printf("%d\n", dist[x][y]);
    }
    return 0;
}