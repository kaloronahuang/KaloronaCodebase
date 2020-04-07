// LOJ3226.cpp
#include <bits/stdc++.h>

using namespace std;

const int MAX_N = 330, MAX_M = MAX_N * MAX_N >> 1;

typedef long long ll;

int n, m, seg[MAX_N][MAX_N][MAX_N], dp[MAX_N][MAX_N];

int gmax(int &a, int b) { return a = max(a, b); }

int main()
{
    // freopen("2.in", "r", stdin);
    scanf("%d%d", &n, &m);
    for (int i = 1, l, r, w; i <= m; i++)
    {
        scanf("%d%d%d", &w, &l, &r);
        for (int j = l; j <= r; j++)
            seg[l][r][j] = max(seg[l][r][j], w);
    }
    for (int len = 1; len <= n; len++)
        for (int i = 1; i + len - 1 <= n; i++)
        {
            int j = i + len - 1;
            for (int k = i; k <= j; k++)
                gmax(dp[i][j], dp[i][k - 1] + dp[k + 1][j] + gmax(seg[i][j][k], max(seg[i + 1][j][k], seg[i][j - 1][k])));
        }
    printf("%d\n", dp[1][n]);
    return 0;
}