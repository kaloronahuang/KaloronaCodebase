// FOJ1915.cpp
#include <bits/stdc++.h>

using namespace std;

const int MAX_N = 150, mod = 19921107;

int p, q, stats[MAX_N], stat_tot;

struct matrix
{
    int mat[MAX_N][MAX_N];

    void clear() { memset(mat, 0, sizeof(mat)); }

    int *operator[](const int &rhs) { return mat[rhs]; }

    matrix operator*(const matrix &rhs)
    {
        matrix ret;
        ret.clear();
        for (int i = 1; i <= stat_tot; i++)
            for (int j = 1; j <= stat_tot; j++)
                for (int k = 1; k <= stat_tot; k++)
                    ret[i][j] = (1LL * ret[i][j] + 1LL * mat[i][k] * rhs.mat[k][j] % mod) % mod;
        return ret;
    }

    matrix operator^(const int &rhs)
    {
        int tim = rhs;
        matrix ret, bas = *this;
        ret.clear();
        for (int i = 1; i <= stat_tot; i++)
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
} A, trans;

int main()
{
    scanf("%d%d", &p, &q);
    // process the stats;
    for (int i = 0; i < (1 << p); i++)
    {
        bool flag = true;
        for (int j = 1; j < p; j++)
            if ((i & (1 << (j - 1))) && (i & (1 << j)))
            {
                flag = false;
                break;
            }
        if (p != 1)
            flag &= (!((i & 1) && (i & (1 << (p - 1)))));
        if (flag)
            stats[++stat_tot] = i;
    }
    if (q == 1)
        printf("%d\n", stat_tot), exit(0);
    int ans = 0;
    trans.clear();
    for (int i = 1; i <= stat_tot; i++)
    {
        A[i][i] = 1;
        for (int j = 1; j <= stat_tot; j++)
            if (!(stats[i] & stats[j]))
                trans[i][j] = 1;
    }
    A = A * (trans ^ (q - 1));
    for (int i = 1; i <= stat_tot; i++)
        for (int j = 1; j <= stat_tot; j++)
            if (!(stats[i] & stats[j]))
                ans = (1LL * ans + A[i][j]) % mod;
    printf("%d\n", ans);
    return 0;
}