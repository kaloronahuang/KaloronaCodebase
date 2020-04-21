// kaisou.cpp
#include <bits/stdc++.h>

using namespace std;

const int MAX_N = 55, mod = 998244353;

int n, limit, mat[MAX_N][MAX_N], poly_val[MAX_N], poly_coeff[MAX_N];
bool mp[MAX_N][MAX_N];

void fileIO(string src)
{
    freopen((src + ".in").c_str(), "r", stdin);
    freopen((src + ".out").c_str(), "w", stdout);
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

int gauss()
{
    int res = 1;
    for (int i = 0; i < n - 1; i++)
    {
        int key = i;
        for (int j = i; j < n - 1; j++)
            if (mat[j][i] != 0)
            {
                key = j;
                break;
            }
        if (key != i)
        {
            res = mod - res;
            for (int j = i; j < n - 1; j++)
                swap(mat[i][j], mat[key][j]);
        }
        int inv = fpow(mat[i][i], mod - 2);
        for (int j = i + 1; j < n - 1; j++)
        {
            int rate = 1LL * mat[j][i] * inv % mod;
            for (int k = i; k < n - 1; k++)
                mat[j][k] = (0LL + mat[j][k] + mod - 1LL * rate * mat[i][k] % mod) % mod;
        }
    }
    for (int i = 0; i < n - 1; i++)
        res = 1LL * res * mat[i][i] % mod;
    return res;
}

int main()
{
    // fileIO("kaisou");
    scanf("%d%d", &n, &limit);
    for (int i = 1, fa; i < n; i++)
        scanf("%d", &fa), mp[i][fa] = mp[fa][i] = true;
    for (int x = 1; x <= n; x++)
    {
        memset(mat, 0, sizeof(mat));
        for (int i = 0; i < n; i++)
            for (int j = 0; j < n; j++)
                if (i != j)
                    if (!mp[i][j])
                        mat[i][j] = mod - x, mat[i][i] += x;
                    else
                        mat[i][j] = mod - 1, mat[i][i]++;
        poly_val[x] = gauss();
    }
    memset(mat, 0, sizeof(mat));
    for (int i = 0; i < n; i++)
    {
        mat[i][0] = 1;
        for (int j = 1; j < n; j++)
            mat[i][j] = 1LL * mat[i][j - 1] * (i + 1) % mod;
        mat[i][n] = poly_val[i + 1];
    }
    for (int i = 0; i < n; i++)
    {
        int key = i;
        for (int j = i; j < n; j++)
            if (mat[j][i] > 0)
            {
                key = j;
                break;
            }
        if (key != i)
            for (int j = i; j <= n; j++)
                swap(mat[i][j], mat[key][j]);
        int inv = fpow(mat[i][i], mod - 2);
        for (int j = 0; j < n; j++)
            if (i != j)
            {
                int rate = 1LL * mat[j][i] * inv % mod;
                for (int k = i + 1; k <= n; k++)
                    mat[j][k] = (0LL + mat[j][k] + mod - 1LL * rate * mat[i][k] % mod) % mod;
            }
    }
    for (int i = 0; i < n; i++)
        poly_coeff[i] = 1LL * mat[i][n] * fpow(mat[i][i], mod - 2) % mod;
    int ans = 0;
    for (int i = 0; i <= limit; i++)
        ans = (0LL + ans + poly_coeff[i]) % mod;
    printf("%d\n", ans);
    return 0;
}