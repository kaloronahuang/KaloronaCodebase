// CF1200D.cpp
#include <bits/stdc++.h>

using namespace std;

const int MAX_N = 2020;

int n, k, up[MAX_N], lower[MAX_N], lft[MAX_N], rig[MAX_N], ans[MAX_N][MAX_N];
char mat[MAX_N][MAX_N];

int main()
{
    memset(up, 0x3f, sizeof(up)), memset(lft, 0x3f, sizeof(lft));
    scanf("%d%d", &n, &k);
    for (int i = 1; i <= n; i++)
        scanf("%s", mat[i] + 1);
    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= n; j++)
            if (mat[i][j] == 'B')
            {
                up[j] = min(up[j], i), lower[j] = max(lower[j], i);
                lft[i] = min(lft[i], j), rig[i] = max(rig[i], j);
            }
    int pans = 0;
    for (int i = 1; i <= n; i++)
    {
        if (rig[i] == 0)
        {
            pans++;
            continue;
        }
        if (rig[i] - lft[i] + 1 <= k)
        {
            int x1 = i, y1 = max(1, rig[i] - k + 1);
            int x2 = min(i + k - 1, n), y2 = lft[i];
            ans[x1][y1]++, ans[x2 + 1][y2 + 1]++;
            ans[x1][y2 + 1]--, ans[x2 + 1][y1]--;
        }
    }
    for (int i = 1; i <= n; i++)
    {
        if (lower[i] == 0)
        {
            pans++;
            continue;
        }
        if (lower[i] - up[i] + 1 <= k)
        {
            int x1 = lower[i], y1 = max(1, i - k + 1);
            int x2 = min(n, up[i] + k - 1), y2 = i;
            ans[x1][y1]++, ans[x2 + 1][y2 + 1]++;
            ans[x1][y2 + 1]--, ans[x2 + 1][y1]--;
        }
    }
    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= n; j++)
            ans[i][j] += ans[i - 1][j] + ans[i][j - 1] - ans[i - 1][j - 1];
    int gans = 0;
    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= n; j++)
            gans = max(gans, ans[i][j]);
    printf("%d", gans + pans);
    return 0;
}