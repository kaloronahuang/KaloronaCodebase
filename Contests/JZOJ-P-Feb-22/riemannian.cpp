// riemannian.cpp
#include <bits/stdc++.h>

using namespace std;

const int MAX_N = 3e7 + 200, mod = 998244353, B = 1e6 + 10;

int T, ans1, ans2;
long long n;

void fileIO()
{
	freopen("riemannian.in", "r", stdin);
	freopen("riemannian.out", "w", stdout);
}

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

    matrix operator^(const int &rhs)
    {
        int tim = rhs;
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
} trans[B + 1], transB[B + 1], init;

int main()
{
	fileIO();
    for (int i = 0; i < 3; i++)
        trans[0][i][i] = 1;
    trans[1][0][1] = 2, trans[1][0][2] = 1, trans[1][2][2] = 1;
    trans[1][1][0] = 1, trans[1][1][1] = 2, trans[1][1][2] = 2;
    transB[0] = trans[0], transB[1] = trans[1] ^ B;
    for (int i = 2; i <= B; i++)
        trans[i] = trans[i - 1] * trans[1], transB[i] = transB[i - 1] * transB[1];
    init[2][0] = 1;
    scanf("%d", &T);
    while (T--)
    {
        scanf("%lld", &n);
        long long seg = n / B, rem = n % B;
        matrix ans = transB[seg] * (trans[rem] * init);
        // printf("%d %d\n", ans[0][0], ans[1][0]);
        ans1 ^= ans[0][0], ans2 ^= ans[1][0];
    }
    printf("%d %d\n", ans1, ans2);
    return 0;
}