// P1369.cpp
#include <bits/stdc++.h>

using namespace std;

const int MAX_N = 110;

int mat[MAX_N][MAX_N], n, prefix[MAX_N][MAX_N];

int main()
{
    scanf("%d", &n);
    for (int i = 1, x, y; i <= n; i++)
        scanf("%d%d", &x, &y), mat[x][y]++;
    int gans = 0;
    for (int upperLine = 1; upperLine < MAX_N; upperLine++)
    {
        memset(prefix, 0, sizeof(prefix));
        for (int j = 1; j <= upperLine; j++)
            for (int i = 1; i < MAX_N; i++)
                prefix[i][j] = prefix[i][j - 1] + mat[i][j];
        for (int lowerLine = 1; lowerLine < upperLine; lowerLine++)
        {
            // baseline;
            int upperSiz = 0, lowerSiz = 0, lowest_pt = 0x3f3f3f3f;
            for (int k = 1; k < MAX_N; k++)
            {
                gans = max(gans, upperSiz + lowerSiz + prefix[k][upperLine] - prefix[k][lowerLine - 1] - lowest_pt);
                lowest_pt = min(lowest_pt, upperSiz + lowerSiz - (prefix[k][upperLine] - prefix[k][lowerLine - 1]));
                upperSiz += mat[k][upperLine], lowerSiz += mat[k][lowerLine];
            }
        }
    }
    printf("%d", gans);
    return 0;
}