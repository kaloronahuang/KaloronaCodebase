// LOJ3247.cpp
#include <bits/stdc++.h>

using namespace std;

const int MAX_N = 5e4 + 200, mod = 1e9 + 7;

int n, limit, q, ai[MAX_N];

struct matrix
{
    int mat[21][21];
    int *operator[](const int &idx) { return mat[idx]; }
    matrix operator*(const matrix &rhs)
    {
        matrix ret;
        memset(ret.mat, 0, sizeof(ret.mat));
        for (int i = 1; i <= limit; i++)
            for (int k = 1; k <= limit; k++)
                if (mat[i][k])
                    for (int j = 1; j <= limit; j++)
                        ret.mat[i][j] = (0LL + ret.mat[i][j] + 1LL * mat[i][k] * rhs.mat[k][j] % mod) % mod;
        return ret;
    }
    void output()
    {
        for (int i = 1; i <= limit; i++, puts(""))
            for (int j = 1; j <= limit; j++)
                printf("%d ", mat[i][j]);
    }
} trans[MAX_N], trans_inv[MAX_N], base, unit[MAX_N], unit_inv[MAX_N];

int fpow(int bas, int tim)
{
    int ret = 1;
    for (; tim; tim >>= 1, bas = 1LL * bas * bas % mod)
        if (tim & 1)
            ret = 1LL * ret * bas % mod;
    return ret;
}

matrix getInv(matrix u)
{
    matrix ret = base;
    for (int i = 1; i <= limit; i++)
    {
        int key = -1;
        for (int j = i; j <= limit; j++)
            if (u[j][i] > 0)
            {
                key = j;
                break;
            }
        if (key != i)
            for (int j = 1; j <= limit; j++)
                swap(u[key][j], u[i][j]), swap(ret[key][j], ret[i][j]);
        int inv = fpow(u[i][i], mod - 2);
        for (int j = 1; j <= limit; j++)
            u[i][j] = 1LL * u[i][j] * inv % mod, ret[i][j] = 1LL * ret[i][j] * inv % mod;
        for (int j = 1; j <= limit; j++)
            if (i != j && u[j][i])
            {
                int rate = (mod - u[j][i]) % mod;
                for (int k = 1; k <= limit; k++)
                    u[j][k] = (0LL + u[j][k] + 1LL * rate * u[i][k] % mod) % mod, ret[j][k] = (0LL + ret[j][k] + 1LL * rate * ret[i][k] % mod) % mod;
            }
    }
    return ret;
}

int main()
{
    scanf("%d%d", &n, &limit);
    for (int i = 1; i <= n; i++)
        scanf("%d", &ai[i]);
    for (int i = 1; i <= limit; i++)
        base.mat[i][i] = 1;
    for (int i = 1; i <= limit; i++)
    {
        unit[i] = base;
        for (int j = 1; j <= i; j++)
            unit[i].mat[j][i]++;
        unit_inv[i] = getInv(unit[i]);
    }
    trans[0] = trans_inv[0] = base;
    for (int i = 1; i <= n; i++)
    {
        trans[i] = trans[i - 1] * unit[ai[i]];
        trans_inv[i] = unit_inv[ai[i]] * trans_inv[i - 1];
    }
    scanf("%d", &q);
    while (q--)
    {
        int l, r;
        scanf("%d%d", &l, &r);
        int pans = 0;
        for (int i = 1; i <= limit; i++)
            for (int j = 1; j <= limit; j++)
                pans = (0LL + pans + 1LL * trans_inv[l - 1][1][i] * trans[r][i][j] % mod) % mod;
        printf("%d\n", pans);
    }
    return 0;
}