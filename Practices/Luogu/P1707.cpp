// P1707.cpp
#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

ll n, p, q, r, t, u, v, w, x, y, z, mod;

ll fmul(ll a, ll b)
{
    ll ret = 0;
    while (b)
    {
        if (b & 1)
            ret = (0LL + ret + a) % mod;
        a = (0LL + a + a) % mod;
        b >>= 1;
    }
    return ret;
}

struct matrix
{
    ll mat[11][11];
    void clear() { memset(mat, 0, sizeof(mat)); }
    ll *operator[](const int &idx) { return mat[idx]; }
    matrix operator*(const matrix &node)
    {
        matrix ret;
        ret.clear();
        for (int k = 0; k < 11; k++)
            for (int i = 0; i < 11; i++)
                if (mat[i][k])
                    for (int j = 0; j < 11; j++)
                        if (node.mat[k][j])
                            ret[i][j] = (1LL * ret[i][j] + fmul(mat[i][k], node.mat[k][j])) % mod;
        return ret;
    }
    matrix operator^(const ll &idx)
    {
        ll tim = idx;
        matrix ret, bas = *this;
        ret.clear();
        for (int i = 0; i < 11; i++)
            ret[i][i] = 1;
        for (; tim; tim >>= 1, bas = bas * bas)
            if (tim & 1)
                ret = ret * bas;
        return ret;
    }
} init, trans;

int main()
{
    scanf("%lld%lld%lld%lld%lld%lld%lld%lld%lld%lld%lld%lld", &n, &mod, &p, &q, &r, &t, &u, &v, &w, &x, &y, &z);
    // a_{i + 2};
    trans[0][0] = p, trans[1][0] = q, trans[2][0] = 1, trans[4][0] = 1;
    trans[6][0] = r, trans[7][0] = t, trans[10][0] = 1;
    // a_{i + 1};
    trans[0][1] = 1;
    // b_{i + 2};
    trans[2][2] = u, trans[3][2] = v, trans[0][2] = 1, trans[4][2] = 1, trans[9][2] = 1;
    // b_{i + 1};
    trans[2][3] = 1;
    // c_{i + 2};
    trans[4][4] = x, trans[5][4] = y, trans[0][4] = 1, trans[2][4] = 1, trans[8][4] = 1;
    trans[7][4] = 1, trans[10][4] = 2;
    // c_{i + 1};
    trans[4][5] = 1;
    // k^2;
    trans[6][6] = 1, trans[7][6] = 2, trans[10][6] = 1;
    // k;
    trans[7][7] = 1, trans[10][7] = 1;
    // z^k && w^k && 1;
    trans[8][8] = z, trans[9][9] = w, trans[10][10] = 1;
    init[0][0] = init[0][2] = init[0][4] = 3;
    init[0][1] = init[0][3] = init[0][5] = 1;
    init[0][6] = 1, init[0][7] = 1, init[0][8] = z, init[0][9] = w, init[0][10] = 1;
    init = init * (trans ^ (n - 1));
    printf("nodgd %lld\nCiocio %lld\nNicole %lld\n", init[0][1], init[0][3], init[0][5]);
    return 0;
}