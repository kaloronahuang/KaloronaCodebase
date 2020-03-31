// LOJ573.cpp
#include <bits/stdc++.h>

using namespace std;

const int MAX_N = 1e6 + 200, mod = 998244353;

int n, m, typ, last_ans, ai[MAX_N];

struct matrix
{

    int mat[2][2];

    int *operator[](const int &idx) { return mat[idx]; }

    matrix operator*(const matrix &rhs)
    {
        matrix ret;
        memset(ret.mat, 0, sizeof(ret.mat));
        for (int i = 0; i < 2; i++)
            for (int j = 0; j < 2; j++)
                for (int k = 0; k < 2; k++)
                    ret[i][j] = (0LL + ret[i][j] + 1LL * mat[i][k] * rhs.mat[k][j] % mod) % mod;
        return ret;
    }
} pre[MAX_N], pre_inv[MAX_N];

matrix generateCoeff(int a) { return matrix{{{a, 1}, {1, 0}}}; }

matrix generateCoeffInv(int a) { return matrix{{{0, 1}, {1, mod - a}}}; }

int main()
{
    scanf("%d%d%d", &n, &m, &typ);
    pre[0] = pre_inv[0] = matrix{{{1, 0}, {0, 1}}};
    for (int i = 1; i <= n; i++)
        scanf("%d", &ai[i]), pre[i] = pre[i - 1] * generateCoeff(ai[i]), pre_inv[i] = generateCoeffInv(ai[i]) * pre_inv[i - 1];
    while (m--)
    {
        int opt, x, y;
        scanf("%d%d", &opt, &x);
        if (opt == 1)
        {
            ai[++n] = x, ai[n] ^= typ * last_ans;
            pre[n] = pre[n - 1] * generateCoeff(ai[n]), pre_inv[n] = generateCoeffInv(ai[n]) * pre_inv[n - 1];
        }
        else
        {
            scanf("%d", &y), x ^= typ * last_ans, y ^= typ * last_ans;
            matrix ans = pre_inv[x - 1] * pre[y] * matrix{{{1, 0}, {0, 0}}};
            printf("%d %d\n", ans.mat[0][0], ans.mat[1][0]);
            last_ans = ans.mat[0][0] ^ ans.mat[1][0];
        }
    }
    return 0;
}