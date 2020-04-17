// bracelet.cpp
#include <bits/stdc++.h>

using namespace std;

const int mod = 1e9 + 7;

int n, kind, dp[1010][2][2];

void fileIO()
{
    freopen("bracelet.in", "r", stdin);
    freopen("bracelet.out", "w", stdout);
}

struct matrix
{
    int mat[2][2];
    int *operator[](const int &idx) { return mat[idx]; }
    void clear() { memset(mat, 0, sizeof(mat)); }
    matrix operator*(const matrix &rhs)
    {
        matrix ret;
        ret.clear();
        for (int i = 0; i < 2; i++)
            for (int k = 0; k < 2; k++)
                if (mat[i][k])
                    for (int j = 0; j < 2; j++)
                        if (rhs.mat[k][j])
                            ret[i][j] = (0LL + ret[i][j] + 1LL * mat[i][k] * rhs.mat[k][j] % mod) % mod;
        return ret;
    }
    matrix operator^(const int &idx)
    {
        int tim = idx;
        matrix ret, bas = *this;
        ret.clear(), ret[0][0] = ret[1][1] = 1;
        while (tim)
        {
            if (tim & 1)
                ret = ret * bas;
            bas = bas * bas;
            tim >>= 1;
        }
        return ret;
    }
} trans, init;

matrix getFn(int x) { return init * (trans ^ x); }

int phi(int x)
{
    int ret = x;
    for (int i = 2; 1LL * i * i <= x; i++)
        if (x % i == 0)
        {
            ret -= ret / i;
            while (x % i == 0)
                x /= i;
        }
    if (x != 1)
        ret -= ret / x;
    return ret % mod;
}

int fpow(int bas, int tim)
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

const int inv2 = fpow(2, mod - 2);

int solve(int x)
{
    if (x == 1)
        return phi(n / x);
    matrix c = getFn(x - 2);
    int pans = 1LL * kind * c[0][0] % mod;
    c = c * trans;
    pans = (0LL + pans + c[0][0] + c[0][1]) % mod;
    pans = 1LL * pans * phi(n / x) % mod;
    return pans;
}

int main()
{
    // fileIO();
    scanf("%d%d", &n, &kind), init[0][0] = 1, trans[0][0] = trans[1][0] = 1, trans[0][1] = kind;
    int ans = 0;
    for (int i = 1; 1LL * i * i <= n; i++)
        if (n % i == 0)
            ans = (0LL + ans + solve(i) + ((1LL * i * i == n) ? 0 : solve(n / i))) % mod;
    printf("%lld\n", 1LL * ans * fpow(n, mod - 2) % mod);
    return 0;
}