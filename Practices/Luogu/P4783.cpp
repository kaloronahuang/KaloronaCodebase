// P4783.cpp
#include <bits/stdc++.h>

using namespace std;

const int MAX_N = 440, mod = 1e9 + 7;

int n, mat[MAX_N][MAX_N << 1];

int fpow(int bas, int tim)
{
    int ret = 1;
    while (tim)
    {
        if (tim & 1)
            ret = 1LL * ret * bas % mod;
        bas = 1LL * bas * bas % mod;
        tim >>= 1;
    }
    return ret;
}

void gauss_inverse()
{
    for (int i = 1; i <= n; i++)
    {
        int key = 0;
        for (int j = i; j <= n && key == 0; j++)
            if (mat[j][i] != 0)
                key = j;
        if (key != i)
        {
            if (key == 0)
                puts("No Solution"), exit(0);
            for (int j = i; j <= (n << 1); j++)
                swap(mat[i][j], mat[key][j]);
        }
        int inv = fpow(mat[i][i], mod - 2);
        for (int j = i; j <= (n << 1); j++)
            mat[i][j] = 1LL * mat[i][j] * inv % mod;
        for (int j = 1; j <= n; j++)
            if (i != j)
            {
                inv = mat[j][i];
                for (int k = i; k <= (n << 1); k++)
                    mat[j][k] = (0LL + mat[j][k] + mod - 1LL * inv * mat[i][k] % mod) % mod;
            }
    }
}

int main()
{
    scanf("%d", &n);
    for (int i = 1; i <= n; i++)
    {
        mat[i][n + i] = 1;
        for (int j = 1; j <= n; j++)
            scanf("%d", &mat[i][j]);
    }
    gauss_inverse();
    for (int i = 1; i <= n; i++, puts(""))
        for (int j = n + 1; j <= (n << 1); j++)
            printf("%d ", mat[i][j]);
    return 0;
}