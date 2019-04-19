// CF24D.cpp
#include <bits/stdc++.h>
using namespace std;
const int MAX_N = 2020;
double mat[MAX_N][MAX_N], c[MAX_N], dp[MAX_N][MAX_N];
int n, m, sx, sy;

void solve()
{
    for (int i = 1; i <= m; i++)
    {
        double w = 1.0 / mat[i][i];
        mat[i][i] *= w, mat[i][m + 1] *= w;
        if (i == m)
            break;
        mat[i][i + 1] *= w;
        w = mat[i + 1][i] / mat[i][i];
        mat[i + 1][i] -= w * mat[i][i];
        mat[i + 1][i + 1] -= w * mat[i][i + 1];
        mat[i + 1][m + 1] -= w * mat[i][m + 1];
    }
    for (int i = m - 1; i; i--)
        mat[i][m + 1] -= mat[i + 1][m + 1] * mat[i][i + 1];
}

int main()
{
    scanf("%d%d%d%d", &n, &m, &sx, &sy);
    for (int i = n - 1; i >= sx; i--)
    {
        mat[1][1] = mat[m][m] = -2.0 / 3.0;
        mat[1][2] = mat[m][m - 1] = 1.0 / 3.0;
        for (int j = 2; j < m; j++)
        {
            mat[j][m + 1] = -dp[i + 1][j] / 4.0 - 1;
            mat[j][j] = -3.0 / 4.0;
            mat[j][j - 1] = mat[j][j + 1] = 1.0 / 4.0;
        }
        if (m == 1)
            mat[1][1] = -1.0 / 2.0;
        mat[1][m + 1] = -dp[i + 1][1] / 3.0 - 1;
        mat[m][m + 1] = -dp[i + 1][m] / 3.0 - 1;
        if (m == 1)
            mat[m][m + 1] = -dp[i + 1][m] / 2.0 - 1;
        solve();
        for (int j = 1; j <= m; j++)
            dp[i][j] = mat[j][m + 1];
    }
    printf("%.10f\n", dp[sx][sy]);
    return 0;
}