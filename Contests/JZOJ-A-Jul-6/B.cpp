// B.cpp
#include <bits/stdc++.h>

using namespace std;

const int MAX_N = 60, mod = 10000;

int n, m, start, ed, k, nfish, opt[10];

struct matrix
{
    int mat[MAX_N][MAX_N];

    matrix operator*(const matrix &target) const
    {
        matrix ans;
        memset(ans.mat, 0, sizeof(ans.mat));
        for (int i = 1; i <= n; i++)
            for (int j = 1; j <= n; j++)
                for (int k = 1; k <= n; k++)
                    (ans.mat[i][j] += mat[i][k] * target.mat[k][j]) %= mod;
        return ans;
    }
} maps[MAX_N], zero;

matrix quick_pow(matrix bas, int tim)
{
    matrix ans = zero;
    while (tim)
    {
        if (tim & 1)
            ans = ans * bas;
        bas = bas * bas;
        tim >>= 1;
    }
    return ans;
}

int main()
{
    scanf("%d%d%d%d%d", &n, &m, &start, &ed, &k);
    start++, ed++;
    for (int i = 1; i <= n; i++)
        zero.mat[i][i] = 1;
    for (int i = 1, tmpx, tmpy; i <= m; i++)
        scanf("%d%d", &tmpx, &tmpy), tmpx++, tmpy++, maps[0].mat[tmpx][tmpy] = maps[0].mat[tmpy][tmpx] = 1;
    for (int i = 1; i <= 12; i++)
        maps[i] = maps[0];
    scanf("%d", &nfish);
    for (int i = 1, t; i <= nfish; i++)
    {
        scanf("%d", &t);
        for (int j = 1; j <= t; j++)
            scanf("%d", &opt[j]), opt[j]++;
        for (int rd = 0; rd <= 11; rd++)
            for (int cur = 1; cur <= n; cur++)
                maps[rd].mat[cur][opt[rd % t + 1]] = 0;
    }
    for (int i = 2; i < 12; i++)
        maps[i] = maps[i - 1] * maps[i];
    maps[0] = maps[11] * maps[0];
    int tim = k / 12, md = k % 12;
    if (md == 0)
        printf("%d", quick_pow(maps[0], tim).mat[start][ed]);
    else
        printf("%d", (quick_pow(maps[0], tim) * maps[md]).mat[start][ed]);
    return 0;
}