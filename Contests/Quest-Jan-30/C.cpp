// C.cpp
#include <bits/stdc++.h>

using namespace std;

const int MAX_N = 10;

int n;

struct matrix
{
    int mat[MAX_N][MAX_N];

    void clear() { memset(mat, 0, sizeof(mat)); }

    int *operator[](const int &idx) { return mat[idx]; }

    matrix operator*(const matrix &rhs)
    {
        matrix ret;
        ret.clear();
        for (int i = 1; i <= n; i++)
            for (int j = 1; j <= n; j++)
                for (int k = 1; k <= n; k++)
                    ret[i][j] = (ret[i][j] + mat[i][k] * rhs.mat[k][j] % 2) % 2;
        return ret;
    }
} C, A, B;

matrix decode(int stat)
{
    matrix ret;
    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= n; j++)
        {
            int bit = (i - 1) * n + j - 1;
            ret[i][j] = ((stat >> bit) & 1);
        }
    return ret;
}

int encode(matrix &rhs)
{
    int stat = 0;
    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= n; j++)
        {
            int bit = (i - 1) * n + j - 1;
            stat |= (rhs[i][j] << bit);
        }
    return stat;
}

int main()
{
    scanf("%d", &n);
    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= n; j++)
            scanf("%d", &C[i][j]);
    int cCode = encode(C), ans = 0;
    for (int stat = 0; stat < (1 << (n * n * 2)); stat++)
    {
        int statA = (stat & ((1 << (n * n)) - 1)), statB = (stat >> (n * n));
        A = decode(statA), B = decode(statB);
        C = A * B;
        if (encode(C) == cCode)
            ans++;
    }
    printf("%d\n", ans);
    return 0;
}