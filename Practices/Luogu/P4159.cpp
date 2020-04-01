// P4159.cpp
#include <bits/stdc++.h>

using namespace std;

const int MAX_N = 110, mod = 2009;

int n, siz, T;
char str[MAX_N];

struct matrix
{
    int mat[MAX_N][MAX_N];

    int *operator[](const int &idx) { return mat[idx]; }

    matrix operator*(const matrix &rhs)
    {
        matrix ret;
        memset(ret.mat, 0, sizeof(ret.mat));
        for (int i = 1; i <= siz; i++)
            for (int j = 1; j <= siz; j++)
                for (int k = 1; k <= siz; k++)
                    ret[i][j] = (0LL + ret[i][j] + 1LL * mat[i][k] * rhs.mat[k][j] % mod) % mod;
        return ret;
    }

    matrix operator^(const int &idx)
    {
        matrix ret, bas = *this;
        int tim = idx;
        memset(ret.mat, 0, sizeof(ret.mat));
        for (int i = 1; i <= siz; i++)
            ret[i][i] = 1;
        while (tim)
        {
            if (tim & 1)
                ret = ret * bas;
            bas = bas * bas;
            tim >>= 1;
        }
        return ret;
    }
} trans;

int getId(int x, int y) { return (x - 1) * n + y; }

int main()
{
    scanf("%d%d", &n, &T), siz = n * 10;
    for (int i = 1; i <= n; i++)
        for (int j = 1; j < 9; j++)
            trans[getId(j, i)][getId(j + 1, i)] = 1;
    for (int i = 1; i <= n; i++)
    {
        scanf("%s", str + 1);
        for (int j = 1; j <= n; j++)
            if (str[j] != '0')
                trans[getId(str[j] - '0', i)][getId(1, j)] = 1;
    }
    trans = trans ^ T;
    printf("%d\n", trans[getId(1, 1)][getId(1, n)]);
    return 0;
}