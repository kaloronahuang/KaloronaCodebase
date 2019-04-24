// CH5E01.cpp
#include <bits/stdc++.h>
using namespace std;

const int MAX_N = 360, MAX_M = 50;
int dp[MAX_N][MAX_M][MAX_M][MAX_M], ai[MAX_N], bi[MAX_N], cnt[5];
int n, m;

int main()
{
    scanf("%d%d", &n, &m);
    for (int i = 1; i <= n; i++)
        scanf("%d", &ai[i]);
    for (int i = 1; i <= m; i++)
        scanf("%d", &bi[i]), cnt[bi[i]]++;
    dp[1][0][0][0] = ai[1];
    for (int i = 1; i <= n; i++)
        for (int a = 0; a <= cnt[1]; a++)
            for (int b = 0; b <= cnt[2]; b++)
                for (int c = 0; c <= cnt[3]; c++)
                    if (i - 1 - a - 2 * b - 3 * c >= 0 && (i - 1 - a - 2 * b - 3 * c) % 4 == 0)
                    {
                        int d = (i - 1 - a - 2 * b - 3 * c) / 4;
                        if (d > cnt[4])
                            continue;
                        dp[i + 1][a + 1][b][c] = max(dp[i + 1][a + 1][b][c], dp[i][a][b][c] + ai[i + 1]);
                        dp[i + 2][a][b + 1][c] = max(dp[i + 2][a][b + 1][c], dp[i][a][b][c] + ai[i + 2]);
                        dp[i + 3][a][b][c + 1] = max(dp[i + 3][a][b][c + 1], dp[i][a][b][c] + ai[i + 3]);
                        dp[i + 4][a][b][c] = max(dp[i + 4][a][b][c], dp[i][a][b][c] + ai[i + 4]);
                    }
    int ans = 0;
    for (int a = 0; a <= cnt[1]; a++)
        for (int b = 0; b <= cnt[2]; b++)
            for (int c = 0; c <= cnt[3]; c++)
                if (n - 1 - a - 2 * b - 3 * c >= 0 && (n - 1 - a - 2 * b - 3 * c) % 4 == 0)
                    ans = max(dp[n][a][b][c], ans);
    printf("%d", ans);
    return 0;
}