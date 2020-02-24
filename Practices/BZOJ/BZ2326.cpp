// BZ2326.cpp
#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

ll n;
int mod;

struct matrix
{
    int mat[3][3];

    void clear() { memset(mat, 0, sizeof(mat)); }

    int *operator[](const int &rhs) { return mat[rhs]; }

    matrix operator*(const matrix &rhs)
    {
        matrix ret;
        ret.clear();
        for (int i = 0; i < 3; i++)
            for (int j = 0; j < 3; j++)
                for (int k = 0; k < 3; k++)
                    ret[i][j] = (0LL + ret[i][j] + 1LL * mat[i][k] * rhs.mat[k][j] % mod) % mod;
        return ret;
    }

    matrix operator^(const ll &rhs)
    {
        ll tim = rhs;
        matrix ret, bas = *this;
        ret.clear();
        for (int i = 0; i < 3; i++)
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
} bas, trans;

int main()
{
    scanf("%lld%d", &n, &mod);
    bas[0][0] = 0, bas[1][0] = 0, bas[2][0] = 1;
    trans[0][0] = trans[0][1] = trans[0][2] = trans[1][1] = trans[1][2] = trans[2][2] = 1;
    for (ll bit = 1; bit - 1 <= n; bit *= 10)
    {
        ll current_pos = bit - 1;
        ll nxt = bit * 10 - 1, idx = min(n - current_pos, nxt - current_pos);
        trans[0][0] = 1LL * trans[0][0] * 10 % mod;
        bas = (trans ^ idx) * bas;
        if (idx == n - current_pos)
            break;
    }
    printf("%d\n", bas[0][0]);
    return 0;
}