// C.cpp
#include <bits/stdc++.h>

using namespace std;

const int MAX_N = 301;

int n;
short upper[MAX_N][MAX_N][MAX_N], prefix[MAX_N][MAX_N], lower[MAX_N][MAX_N][MAX_N];
char mp[MAX_N][MAX_N];

short max(short x, int y) { return (x < y) ? y : x; }

int getSum(int x1, int y1, int x2, int y2) { return prefix[x2][y2] - prefix[x1 - 1][y2] - prefix[x2][y1 - 1] + prefix[x1 - 1][y1 - 1]; }

int main()
{
    scanf("%d", &n);
    for (int i = 1; i <= n; i++)
        scanf("%s", mp[i] + 1);
    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= n; j++)
            prefix[i][j] = prefix[i - 1][j] + prefix[i][j - 1] - prefix[i - 1][j - 1] + mp[i][j] == '.';
    for (int i = 1; i <= n; i++)
        for (int j = i; j <= n; j++)
            for (int k = 1; k <= n; k++)
            {
                if (getSum(k, i, k, j) == 0)
                    upper[i][j][k] = max(upper[i][j][k], 0);
                if (mp[k][i] == '.' && mp[k][j] == '.' && upper[i][j][k - 1] != -1)
                    upper[i][j][k] = max(upper[i][j][k], upper[i][j][k - 1] + 1);
                if (!(mp[k][i] == '.' && mp[k][j] == '.'))
                    upper[i][j][k] = -1;
            }
    for (int i = 1; i <= n; i++)
        for (int j = i; j <= n; j++)
            for (int k = 1; k <= n; k++)
                if (upper[i][j][k] > 1)
                    upper[i][j][k] = (j - i - 1) * (upper[i][j][k] - 1);
    for (int k = 1; k <= n; k++)
        for (int len = 2; len <= n; len++)
            for (int i = 1; i + len - 1 <= n; i++)
            {
                int j = i + len - 1;
                upper[i][j][k] = max(upper[i][j - 1][k], max(upper[i + 1][j][k], upper[i][j][k]));
            }
    long long ans = 0;
    for (int i = 1; i <= n; i++)
        for (int j = i; j <= n; j++)
            for (int k = n; k >= 1; k--)
            {
                if (getSum(k, i, k, j) == 0)
                    lower[i][j][k] = 0;
                if (mp[k][i] != '.' || mp[k][j] != '.')
                    lower[i][j][k] = -1;
                else
                    lower[i][j][k] = max(lower[i][j][k], (lower[i][j][k + 1] == -1 ? 0 : 1) + lower[i][j][k + 1]);
                if (lower[i][j][k] > 2)
                    ans = max(ans, 1LL * (j - i - 1) * (lower[i][j][k] - 2) * upper[i][j][k - 1]);
            }
    printf("%lld", ans);
    return 0;
}