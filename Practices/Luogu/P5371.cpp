// P5371.cpp
#include <bits/stdc++.h>

using namespace std;

const int MAX_N = 1010, mod = 998244353;

typedef long long ll;

ll n, C, X;

struct matrix
{
    int mat[9][9];
    void clear() { memset(mat, 0, sizeof(mat)); }
    int *operator[](const int &rhs) { return mat[rhs]; }
    matrix operator*(const matrix &rhs)
    {
        matrix ret;
        ret.clear();
        for (int i = 0; i < 9; i++)
            for (int k = 0; k < 9; k++)
                if (mat[i][k])
                    for (int j = 0; j < 9; j++)
                        if (rhs.mat[k][j])
                            ret[i][j] = (0LL + ret[i][j] + 1LL * mat[i][k] * rhs.mat[k][j] % mod) % mod;
        return ret;
    }
    matrix operator^(const ll &rhs)
    {
        matrix ret, bas = *this;
        ll tim = rhs;
        ret.clear();
        for (int i = 0; i < 9; i++)
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
} trans, acc, curt;

int main()
{
    scanf("%lld%lld%lld", &n, &C, &X), acc[0][0] = 1;
    for (int j = 0; j < 3; j++)
        for (int k = 0; k < 3; k++)
            for (int l = 0; l < 3; l++)
                if (j + k + l <= C)
                    trans[j * 3 + k][k * 3 + l] = ((C - (j + k + l)) / 3) + 1;
    ll lx = 0;
    for (ll i = 1, x, y; i <= X; i++)
    {
        scanf("%lld%lld", &x, &y);
        acc = acc * (trans ^ (x - lx - 1)), curt.clear();
        for (int j = 0; j < 3; j++)
            for (int k = 0; k < 3; k++)
                for (int l = 0; l < 3; l++)
                {
                    ll s = j + k + l;
                    if (s < y)
                        s = y + ((s - y) % 3 + 3) % 3;
                    if (s <= C)
                        curt[j * 3 + k][k * 3 + l] = (C - s) / 3 + 1;
                }
        lx = x, acc = acc * curt;
    }
    acc = acc * (trans ^ (n - lx));
    printf("%d\n", acc[0][0]);
    return 0;
}