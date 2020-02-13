// farm.cpp
#include <bits/stdc++.h>

using namespace std;

const int MAX_N = 3300;

int n, m, T, mat[MAX_N][MAX_N], idx[MAX_N][MAX_N], stk[MAX_N], w[MAX_N];
int down[MAX_N][MAX_N], lft[MAX_N][MAX_N], rig[MAX_N][MAX_N], up[MAX_N][MAX_N];

void fileIO()
{
    freopen("farm.in", "r", stdin);
    freopen("farm.out", "w", stdout);
}

int main()
{
    // fileIO();
    scanf("%d%d%d", &n, &m, &T), n++, m++;
    for (int i = 1, x, y; i <= T; i++)
        scanf("%d%d", &x, &y), idx[x + 1][y + 1]++;
    for (int i = 1; i <= m; i++)
        for (int j = 1; j <= n; j++)
            mat[i][j] = mat[i - 1][j] + mat[i][j - 1] - mat[i - 1][j - 1] + idx[i][j];
    for (int i = 1; i <= m; i++)
        for (int j = 1; j <= n; j++)
        {
            if (idx[i][j])
                up[i][j] = i;
            else
                up[i][j] = up[i - 1][j];
            if (i == 1)
                up[i][j] = i;
        }
    int ans = 0;
    for (int lower = 2; lower <= m; lower++)
    {
        int tail = 0;

        for (int i = 1; i <= n + 1; i++)
        {
            int height = lower - up[lower - 1][i] + 1;
            if (height > stk[tail])
                stk[++tail] = height, w[tail] = 1;
            else
            {
                int len = 0;
                while (tail && stk[tail] >= height)
                    len += w[tail], ans = max(ans, 2 * (stk[tail--] + len));
                stk[++tail] = height, w[tail] = 1 + len;
            }
        }
    }
    printf("%d\n", ans);
    return 0;
}