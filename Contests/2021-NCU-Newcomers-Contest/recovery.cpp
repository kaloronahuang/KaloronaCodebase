// recovery.cpp
#include <bits/stdc++.h>

using namespace std;

const int mod = 1e9 + 7;

typedef long long ll;

struct matrix
{
    int mat[4][4];

    void clear() { memset(mat, 0, sizeof(mat)); }

    matrix operator*(const matrix &rhs) const
    {
        matrix ret;
        ret.clear();
        for (int i = 0; i < 4; i++)
            for (int j = 0; j < 4; j++)
                for (int k = 0; k < 4; k++)
                    ret.mat[i][j] = (0LL + ret.mat[i][j] + 1LL * mat[i][k] * rhs.mat[k][j] % mod) % mod;
        return ret;
    }

    matrix operator^(const ll &rhs)
    {
        matrix ret, bas = *this;
        ret.clear();
        for (int i = 0; i < 4; i++)
            ret.mat[i][i] = 1;
        ll tim = rhs;
        while (tim)
        {
            if (tim & 1)
                ret = bas * ret;
            bas = bas * bas;
            tim >>= 1;
        }
        return ret;
    }
};

int fpow(int bas, ll tim)
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

int main()
{
    ll m, k1, k2, a1, x, p, q;
    scanf("%lld%lld%lld%lld%lld%lld%lld", &m, &k1, &k2, &a1, &x, &p, &q);
    x = (0LL + x % mod + mod) % mod;
    a1 = (0LL + a1 % mod + mod) % mod;
    k1 = (0LL + k1 % mod + mod) % mod;
    k2 = (0LL + k2 % mod + mod) % mod;
    matrix vec;
    vec.clear();
    vec.mat[0][0] = 0, vec.mat[1][0] = 1;
    vec.mat[2][0] = 1, vec.mat[3][0] = 0;
    matrix trans;
    trans.clear();
    trans.mat[0][0] = trans.mat[1][1] = k2;
    trans.mat[0][2] = trans.mat[1][3] = k1;
    trans.mat[2][0] = trans.mat[3][1] = 1;
    matrix ttrans = trans ^ (m - 2), finalvec = ttrans * vec;
    int a2 = 1LL * ((0LL + x + mod - 1LL * a1 * finalvec.mat[0][0]) % mod) * fpow(finalvec.mat[1][0], mod - 2) % mod;

    matrix ftrans;
    ftrans.clear(), ftrans.mat[0][0] = ftrans.mat[2][1] = 1;
    ftrans.mat[0][1] = ftrans.mat[1][1] = k2;
    ftrans.mat[0][2] = ftrans.mat[1][2] = k1;
    matrix fvec;
    fvec.clear(), fvec.mat[0][0] = (0LL + a1 + a2) % mod, fvec.mat[1][0] = a2, fvec.mat[2][0] = a1;
    int pp = 0, qp = 0;
    if (p == 1)
        pp = 0;
    else if (p == 2)
        pp = a1;
    else if (p == 3)
        pp = (0LL + a1 + a2) % mod;
    else
    {
        matrix ptrans = ftrans ^ (p - 3);
        matrix pfinal = ptrans * fvec;
        pp = pfinal.mat[0][0];
    }
    q--;
    if (q == 1)
        qp = a1;
    else if (q == 2)
        qp = (0LL + a1 + a2) % mod;
    else
    {
        matrix qtrans = ftrans ^ (q - 2);
        matrix qfinal = qtrans * fvec;
        qp = qfinal.mat[0][0];
    }
    printf("%lld\n", (0LL + mod + qp - pp) % mod);
    return 0;
}