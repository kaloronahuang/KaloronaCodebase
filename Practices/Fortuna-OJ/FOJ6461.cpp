// FOJ6461.cpp
#include <bits/stdc++.h>

using namespace std;

void fileIO(string str)
{
    freopen((str + ".in").c_str(), "r", stdin);
    freopen((str + ".out").c_str(), "w", stdout);
}

const int MAX_N = 45, MAX_M = 1e5 + 200, mod = 1e9 + 7;

int n, m, x, y, mat[MAX_N][MAX_N], ai[MAX_N][MAX_N], org[MAX_N][MAX_N][3], poly[MAX_N][MAX_N], X[MAX_N], Y[MAX_N], inv[MAX_N];

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

int det()
{
    int ret = 1;
    for (int i = 1; i <= n - 1; i++)
    {
        int key = 0;
        for (int j = i; j <= n - 1; j++)
            if (mat[j][i] > mat[key][i])
                key = j;
        if (key != i)
        {
            ret = (mod - ret) % mod;
            if (mat[key][i] == 0)
                return 0;
            for (int j = 1; j <= n - 1; j++)
                swap(mat[i][j], mat[key][j]);
        }
        int inv = fpow(mat[i][i], mod - 2);
        for (int j = 1; j <= n - 1; j++)
            if (i != j)
            {
                int rate = 1LL * mat[j][i] * inv % mod;
                for (int k = 1; k <= n - 1; k++)
                    mat[j][k] = (0LL + mat[j][k] + mod - 1LL * rate * mat[i][k] % mod) % mod;
            }
    }
    for (int i = 1; i <= n - 1; i++)
        ret = 1LL * ret * mat[i][i] % mod;
    return ret;
}

void buildMatrix(int a, int b)
{
    memset(mat, 0, sizeof(mat));
    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= n; j++)
            mat[i][j] = (0LL + mod - org[i][j][0] + mod - 1LL * org[i][j][1] * a % mod + mod - 1LL * org[i][j][2] * b % mod) % mod;
    for (int i = 1; i <= n; i++)
    {
        mat[i][i] = 0;
        for (int j = 1; j <= n; j++)
            mat[i][i] = (0LL + mat[i][i] + org[i][j][0] + 1LL * org[i][j][1] * a % mod + 1LL * org[i][j][2] * b % mod) % mod;
    }
}

int main()
{
    // fileIO("tree");
    scanf("%d%d%d%d", &n, &m, &x, &y);
    for (int i = 1, u, v, c; i <= m; i++)
        scanf("%d%d%d", &u, &v, &c), c--, org[u][v][c]++, org[v][u][c]++;
    for (int i = 1; i <= n; i++)
        inv[i] = fpow(i, mod - 2);
    for (int a = 1; a <= n; a++)
        for (int b = 1; b <= n; b++)
        {
            buildMatrix(a, b), ai[a][b] = det();
            memset(X, 0, sizeof(X)), memset(Y, 0, sizeof(Y));
            X[0] = Y[0] = 1;
            int dotval = ai[a][b], len = 0;
            for (int i = 1; i <= n; i++)
                if (i != a)
                {
                    dotval = 1LL * dotval * inv[abs(a - i)] % mod * ((a > i) ? 1 : mod - 1) % mod;
                    for (int j = ++len; j >= 1; j--)
                        X[j] = (0LL + mod - 1LL * X[j] * i % mod + X[j - 1]) % mod;
                    X[0] = (0LL + mod - 1LL * X[0] * i % mod) % mod;
                }
            len = 0;
            for (int i = 1; i <= n; i++)
                if (i != b)
                {
                    dotval = 1LL * dotval * inv[abs(b - i)] % mod * ((b > i) ? 1 : mod - 1) % mod;
                    for (int j = ++len; j >= 1; j--)
                        Y[j] = (0LL + mod - 1LL * Y[j] * i % mod + Y[j - 1]) % mod;
                    Y[0] = (0LL + mod - 1LL * Y[0] * i % mod) % mod;
                }
            for (int i = 0; i < n; i++)
                for (int j = 0; j < n; j++)
                    poly[i][j] = (0LL + poly[i][j] + 1LL * X[i] * Y[j] % mod * dotval % mod) % mod;
        }
    int ans = 0;
    for (int i = 0; i <= x; i++)
        for (int j = 0; j <= y; j++)
            ans = (0LL + ans + poly[i][j]) % mod;
    printf("%d\n", ans);
    return 0;
}