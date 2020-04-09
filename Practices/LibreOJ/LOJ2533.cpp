// LOJ2533.cpp
#include <bits/stdc++.h>

using namespace std;

const int MAX_N = 220;

int n, a, b, mod, fac[MAX_N], fac_inv[MAX_N], inv[MAX_N];

struct matrix
{
    int mat[MAX_N][MAX_N];

    void clear()
    {
        for (int i = 0; i < (a + b + 1) << 1; i++)
            for (int j = 0; j < (a + b + 1) << 1; j++)
                mat[i][j] = 0;
    }

    void init()
    {
        for (int i = 0; i < (a + b + 1) << 1; i++)
            mat[i][i] = 1;
    }

    int *operator[](const int &idx) { return mat[idx]; }

    matrix operator*(const matrix &rhs)
    {
        matrix ret;
        ret.clear();
        for (int i = 0; i < (a + b + 1) << 1; i++)
            for (int k = 0; k < (a + b + 1) << 1; k++)
                if (mat[i][k] != 0)
                    for (int j = 0; j < (a + b + 1) << 1; j++)
                        if (rhs.mat[k][j] != 0)
                            ret[i][j] = (0LL + ret[i][j] + 1LL * mat[i][k] * rhs.mat[k][j] % mod) % mod;
        return ret;
    }

    matrix operator^(const int &rhs)
    {
        int tim = rhs;
        matrix ret, bas = *this;
        ret.clear(), ret.init();
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

int binomial(int n_, int k_) { return 1LL * fac[n_] * fac_inv[k_] % mod * fac_inv[n_ - k_] % mod; }

int main()
{
    scanf("%d%d%d%d", &n, &a, &b, &mod);
    for (int i = fac[0] = 1; i <= (a + b + 1) << 1; i++)
        fac[i] = 1LL * fac[i - 1] * i % mod;
    inv[0] = inv[1] = fac_inv[0] = fac_inv[1] = 1;
    for (int i = 2; i <= (a + b + 1) << 1; i++)
        inv[i] = 1LL * inv[mod % i] * (mod - mod / i) % mod, fac_inv[i] = 1LL * fac_inv[i - 1] * inv[i] % mod;
    for (int i = 0; i < (a + b + 1); i++)
        trans[i][i + a + b + 1] = 1;
    for (int i = 0; i < (a + b + 1); i++)
        for (int j = 0; j <= i; j++)
            trans[j][i] = trans[j + a + b + 1][i] = binomial(i, j);
    trans = trans ^ n;
    int ans = 0, base = 1;
    for (int i = 0, opt = (b & 1) ? mod - 1 : 1; i <= b; i++, base = 1LL * base * n % mod, opt = mod - opt)
        ans = (0LL + ans + 1LL * binomial(b, i) * base % mod * opt % mod * (0LL + trans[0][a + b - i] + trans[0][a + b - i + a + b + 1]) % mod) % mod;
    printf("%d\n", ans);
    return 0;
}