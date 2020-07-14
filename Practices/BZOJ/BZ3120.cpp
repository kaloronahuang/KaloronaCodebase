// BZ3120.cpp
#include <bits/stdc++.h>

using namespace std;

const int mod = 1e9 + 7;

typedef long long ll;

int n, p, q, binomial[110][110], stat2[30][30], stat3[30][30][30], ptot;
ll m;

struct matrix
{

    int mat[200][200];

    void clear() { memset(mat, 0, sizeof(mat)); }

    int *operator[](const int &idx) { return mat[idx]; }

    matrix operator*(const matrix &rhs)
    {
        matrix ret;
        ret.clear();
        for (int k = 1; k <= ptot; k++)
            for (int i = 1; i <= ptot; i++)
                if (mat[i][k])
                    for (int j = 1; j <= ptot; j++)
                        if (rhs.mat[k][j])
                            ret[i][j] = (0LL + ret[i][j] + 1LL * mat[i][k] * rhs.mat[k][j] % mod) % mod;
        return ret;
    }

    matrix operator^(const ll &rhs)
    {
        ll tim = rhs;
        matrix ret, bas = *this;
        ret.clear();
        for (int i = 1; i <= ptot; i++)
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
    scanf("%d%lld%d%d", &n, &m, &p, &q);
    if (p == 1)
        puts("1"), exit(0);
    for (int i = 0; i < 110; i++)
    {
        binomial[i][0] = 1;
        for (int j = 1; j <= i; j++)
            binomial[i][j] = (0LL + binomial[i - 1][j - 1] + binomial[i - 1][j]) % mod;
    }
    if (p == 2)
    {
        for (int a = 0; a <= n; a++)
            for (int b = 0; b <= q; b++)
                stat2[a][b] = ++ptot;
        for (int a = 0; a <= n; a++)
            for (int a1 = 0; a1 <= a; a1++)
            {
                int ra = n - a1;
                if (a1 < n)
                    for (int i = 0; i <= q; i++)
                        trans[stat2[a][i]][stat2[ra][i]] = binomial[a][a1];
                else
                    for (int i = 0; i < q; i++)
                        trans[stat2[a][i]][stat2[ra][i + 1]] = binomial[a][a1];
            }
        init[1][stat2[n][0]] = 1, init = init * (trans ^ m);
        int ans = 0;
        for (int i = 1; i <= ptot; i++)
            ans = (0LL + ans + init[1][i]) % mod;
        printf("%d\n", ans);
        return 0;
    }
    for (int a = 0; a <= n; a++)
        for (int b = 0; a + b <= n; b++)
            for (int c = 0; c <= q; c++)
                stat3[a][b][c] = ++ptot;
    for (int a = 0; a <= n; a++)
        for (int b = 0; a + b <= n; b++)
            for (int a1 = 0; a1 <= a; a1++)
                for (int b1 = 0; b1 <= b; b1++)
                {
                    int female = n - a1 - b1, male = a1;
                    if (a1 + b1 < n)
                        for (int i = 0; i <= q; i++)
                            trans[stat3[a][b][i]][stat3[female][male][i]] = 1LL * binomial[a][a1] * binomial[b][b1] % mod;
                    else
                        for (int i = 0; i < q; i++)
                            trans[stat3[a][b][i]][stat3[female][male][i + 1]] = 1LL * binomial[a][a1] * binomial[b][b1] % mod;
                }
    init[1][stat3[n][0][0]] = 1;
    init = init * (trans ^ m);
    int ans = 0;
    for (int i = 1; i <= ptot; i++)
        ans = (0LL + ans + init[1][i]) % mod;
    printf("%d\n", ans);
    return 0;
}