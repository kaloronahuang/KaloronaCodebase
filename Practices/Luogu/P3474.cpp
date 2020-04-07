// P3474.cpp
#include <bits/stdc++.h>

using namespace std;

const int MAX_N = 2020;

typedef long long ll;

int n, k, mat[MAX_N][MAX_N], up[MAX_N][MAX_N], lft[MAX_N][MAX_N], rig[MAX_N][MAX_N];
ll pre[MAX_N][MAX_N];

ll calc(int x, int y, int ox, int oy) { return pre[ox][oy] - pre[x - 1][oy] - pre[ox][y - 1] + pre[x - 1][y - 1]; }

int main()
{
    scanf("%d%d", &k, &n);
    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= n; j++)
        {
            scanf("%d", &mat[i][j]), pre[i][j] = pre[i - 1][j] + pre[i][j - 1] - pre[i - 1][j - 1] + mat[i][j];
            if (mat[i][j] >= k && mat[i][j] <= (k << 1))
                printf("%d %d %d %d\n", j, i, j, i), exit(0);
        }
    for (int i = 1; i <= n; i++)
    {
        for (int j = 1; j <= n; j++)
            if (mat[i][j] <= k)
                up[i][j] = up[i - 1][j] + 1;
        for (int j = 1; j <= n; j++)
            if (mat[i][j] <= k)
                lft[i][j] = lft[i][j - 1] + 1;
        for (int j = n; j >= 1; j--)
            if (mat[i][j] <= k)
                rig[i][j] = rig[i][j + 1] + 1;
        for (int j = 1; j <= n; j++)
            if (up[i][j] > 1)
                lft[i][j] = min(lft[i - 1][j], lft[i][j]);
        for (int j = n; j >= 1; j--)
            if (up[i][j] > 1)
                rig[i][j] = min(rig[i - 1][j], rig[i][j]);
    }
    int ix = -1, iy, ox, oy;
    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= n; j++)
            if (mat[i][j] <= k && calc(i - up[i][j] + 1, j - lft[i][j] + 1, i, j + rig[i][j] - 1) >= k)
                ix = i - up[i][j] + 1, iy = j - lft[i][j] + 1, ox = i, oy = j + rig[i][j] - 1;
    if (ix == -1)
        puts("NIE"), exit(0);
    while (calc(ix, iy, ox, oy) > (k << 1))
        if (ox > ix)
            if (calc(ix, iy, ox - 1, oy) < k)
                ox = ix;
            else
                ox--;
        else
            oy--;
    printf("%d %d %d %d\n", iy, ix, oy, ox);
    return 0;
}