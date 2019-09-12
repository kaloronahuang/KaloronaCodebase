// B.cpp
#include <bits/stdc++.h>

using namespace std;

const int MAX_N = 2300, MAX_P = 500010, DOM = 1010;

int n, k, q, lb, ub, dist[MAX_N][MAX_N], pts[MAX_N * MAX_N][2];

inline int getId(int x, int y) { return (x - 1) * n + y; }

int main()
{
    scanf("%d%d%d", &n, &k, &q);
    for (int i = 1, x, y; i <= k; i++)
        scanf("%d%d", &x, &y), dist[x + y][x - y + n]++;
    for (int x = 1; x <= n; x++)
        for (int y = 1; y <= n; y++)
            pts[getId(x, y)][0] = x + y, pts[getId(x, y)][1] = x - y + n;
    for (int i = 1; i <= 2 * n; i++)
        for (int j = 1; j <= 2 * n; j++)
            dist[i][j] += dist[i - 1][j] + dist[i][j - 1] - dist[i - 1][j - 1];
    for (int s, i = 1; i <= q; i++)
    {
        scanf("%d", &s);
        if (s > n + 1)
            printf("%d\n", k);
        else
        {
            int ans = 0;
            for (int i = 0, x0, y0, x1, y1; i <= getId(n, n); i++)
            {
                x0 = max(pts[i][0] - s - 1, 0), y0 = max(pts[i][1] - s - 1, 0);
                x1 = min(pts[i][0] + s, n << 1), y1 = min(pts[i][1] + s, n << 1);
                ans = max(ans, dist[x1][y1] - dist[x0][y1] - dist[x1][y0] + dist[x0][y0]);
            }
            printf("%d\n", ans);
        }
    }
    return 0;
}