// P5303.cpp
#include <bits/stdc++.h>

using namespace std;

const int MAX_N = 5, mod = 1e9 + 7;

int T, n;

struct matrix
{
    int mat[MAX_N][MAX_N];
    int *operator[](const int &rhs) { return mat[rhs]; }
    void clear() { memset(mat, 0, sizeof(mat)); }
    matrix operator*(const matrix &rhs)
    {
        matrix ret;
        ret.clear();
        for (int k = 0; k < 5; k++)
            for (int i = 0; i < 5; i++)
                if (mat[i][k])
                    for (int j = 0; j < 5; j++)
                        if (rhs.mat[k][j])
                            ret[i][j] = (0LL + ret[i][j] + 1LL * mat[i][k] * rhs.mat[k][j] % mod) % mod;
        return ret;
    }

    matrix operator^(const int &rhs)
    {
        matrix ret, bas = *this;
        int tim = rhs;
        ret.clear();
        for (int i = 0; i < 5; i++)
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
} init, trans;

int main()
{
    init[0][2] = 1, init[0][3] = init[0][4] = 2;
    trans[0][1] = trans[1][0] = trans[1][1] = trans[2][3] = trans[3][2] = trans[3][3] = trans[4][4] = 1;
    trans[3][1] = 2, trans[4][1] = mod - 1;
    scanf("%d", &T);
    while (T--)
    {
        scanf("%d", &n);
        if (n < 3)
            puts("0");
        else
            printf("%d\n", (init * (trans ^ (n - 2)))[0][1]);
    }
    return 0;
}