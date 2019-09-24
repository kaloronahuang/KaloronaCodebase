// FOJ4791.cpp
#include <bits/stdc++.h>
#define ll long long

using namespace std;

const int MAX_N = 550;

int n, m, q;
ll matrix[MAX_N][MAX_N], r[MAX_N][MAX_N], l[MAX_N][MAX_N], sum[MAX_N][MAX_N];
char mp[MAX_N][MAX_N];

int main()
{
    scanf("%d%d", &n, &m);
    for (int i = 1; i <= n; i++)
        scanf("%s", mp[i] + 1);
    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= m; j++)
            if (mp[i][j] == '.')
                matrix[i][j]++;
    for (int i = 1; i <= n; i++)
        matrix[i][0] = 1;
    for (int i = 1; i <= m; i++)
        matrix[0][i] = 1;
    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= m; j++)
        {
            int cans = 0;
            l[i][j] = l[i - 1][j], r[i][j] = r[i][j - 1];
            if (matrix[i][j] && matrix[i - 1][j])
                r[i][j]++, cans++;
            if (matrix[i][j] && matrix[i][j - 1])
                l[i][j]++, cans++;
            sum[i][j] = sum[i - 1][j] + sum[i][j - 1] - sum[i - 1][j - 1] + cans;
        }
    scanf("%d", &q);
    while (q--)
    {
        int x0, y0, x, y;
        scanf("%d%d%d%d", &x0, &y0, &x, &y);
        printf("%lld\n", sum[x][y] - sum[x0 - 1][y] - sum[x][y0 - 1] + sum[x0 - 1][y0 - 1] - (r[x0][y] - r[x0][y0 - 1]) - (l[x][y0] - l[x0 - 1][y0]));
    }
    return 0;
}