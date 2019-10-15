// A.cpp
#include <bits/stdc++.h>

using namespace std;

int mod, n, T;

struct matrix
{
    int mat[5][5];
    void clear() { memset(mat, 0, sizeof(mat)); }
    int *operator[](const int &idx) { return mat[idx]; }
    matrix operator*(matrix &node)
    {
        matrix ret;
        ret.clear();
        for (int i = 1; i <= 4; i++)
            for (int j = 1; j <= 4; j++)
                for (int k = 1; k <= 4; k++)
                    ret[i][j] = (1LL * ret[i][j] + 1LL * mat[i][k] * node[k][j] % mod) % mod;
        return ret;
    }
    matrix operator^(const int &idx)
    {
        int tim = idx;
        matrix ret, bas = *this;
        ret.clear();
        for (int i = 1; i <= 4; i++)
            ret[i][i] = 1;
        for (; tim; tim >>= 1, bas = bas * bas)
            if (tim & 1)
                ret = ret * bas;
        return ret;
    }
} initial;

void init()
{
    initial.clear();
    initial[1][1] = 1, initial[1][2] = 5;
    initial[1][3] = 1, initial[1][4] = -1;
    initial[2][1] = 1, initial[3][2] = 1;
    initial[4][3] = 1;
}

int main()
{
    init(), scanf("%d", &T);
    while (T--)
    {
        scanf("%d%d", &n, &mod);
        if (n == 1)
            puts("1");
        else if (n == 2)
            puts("5");
        else if (n == 3)
            puts("11");
        else if (n == 4)
            puts("36");
        else
        {
            matrix now = initial;
            now = now ^ (n - 4);
            printf("%lld\n", ((now[1][1] + mod) % mod * 36 + (now[1][2] + mod) % mod * 11 + (now[1][3] + mod) % mod * 5 + (now[1][4] + mod) % mod) % mod);
        }
    }
    return 0;
}