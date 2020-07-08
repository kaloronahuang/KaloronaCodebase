// CF506E.cpp
#include <bits/stdc++.h>

using namespace std;

const int MAX_N = 330, mod = 1e4 + 7;

int n, m, idx, f[MAX_N][MAX_N][MAX_N], g[MAX_N];
char str[MAX_N];

struct matrix
{
    int mat[MAX_N][MAX_N];
    void clear() { memset(mat, 0, sizeof(mat)); }
    int *operator[](const int &rhs) { return mat[rhs]; }
    matrix operator*(const matrix &rhs)
    {
        matrix ret;
        ret.clear();
        for (int i = 0; i <= m; i++)
            for (int j = i; j <= m; j++)
                for (int k = i; k <= j; k++)
                    ret[i][j] = (0LL + ret[i][j] + 1LL * mat[i][k] * rhs.mat[k][j] % mod) % mod;
        return ret;
    }
    matrix operator^(const int &rhs)
    {
        int tim = rhs;
        matrix ret, bas = *this;
        ret.clear();
        for (int i = 0; i <= m; i++)
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
    scanf("%s%d", str, &idx), n = strlen(str);
    f[0][n - 1][0] = 1;
    for (int i = 0; i < n; i++)
        for (int j = n - 1; j >= i; j--)
            for (int k = 0; k < n + i - j; k++)
                if (str[i] == str[j])
                    if (i + 1 < j)
                        f[i + 1][j - 1][k] = (0LL + f[i + 1][j - 1][k] + f[i][j][k]) % mod;
                    else
                        g[k] = (0LL + g[k] + f[i][j][k]) % mod;
                else
                {
                    f[i + 1][j][k + 1] = (0LL + f[i + 1][j][k + 1] + f[i][j][k]) % mod;
                    f[i][j - 1][k + 1] = (0LL + f[i][j - 1][k + 1] + f[i][j][k]) % mod;
                }
    m = n + ((n + 1) >> 1) + 1, init[0][1] = 1, init[0][m - ((n + 1) >> 1)] = g[0], trans[m][m] = 26;
    for (int i = 1; i <= n; i++)
    {
        trans[i][i] = 24, trans[i][m - ((n - i + 1) >> 1)] = g[i];
        if (i != n)
            trans[i][i + 1] = 1;
    }
    for (int i = n + 1; i < m; i++)
        trans[i][i + 1] = 1, trans[i][i] = 25;
    if ((n + idx) & 1)
    {
        matrix ret = init * (trans ^ ((n + idx + 1) >> 1));
        int ans = ret[0][m];
        // printf("%d\n", ans);
        init.clear(), trans.clear();
        memset(g, 0, sizeof(g));
        for (int i = 0; i < n - 1; i++)
            if (str[i] == str[i + 1])
                for (int k = 0; k <= n; k++)
                    g[k] = (0LL + g[k] + f[i][i + 1][k]) % mod;
        /*
        for (int i = 0; i <= n; i++)
            printf("%d ", g[i]);
        puts("");
        */
        init[0][1] = 1, init[0][m - ((n + 1) >> 1)] = g[0];
        for (int i = 1; i <= n; i++)
        {
            trans[i][i] = 24, trans[i][m - ((n - i + 1) >> 1)] = g[i];
            if (i != n)
                trans[i][i + 1] = 1;
        }
        for (int i = n + 1; i < m; i++)
            trans[i][i + 1] = 1, trans[i][i] = 25;
        ret = init * (trans ^ ((n + idx + 1) >> 1));
        // printf("%d\n", ret[0][m]);
        printf("%lld\n", (0LL + ans + mod - ret[0][m]) % mod);
    }
    else
    {
        matrix ret = init * (trans ^ ((n + idx) >> 1));
        printf("%d\n", ret[0][m]);
    }
    return 0;
}