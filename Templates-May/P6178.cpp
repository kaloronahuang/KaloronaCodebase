// P6178.cpp
#include <bits/stdc++.h>

using namespace std;

const int MAX_N = 330, mod = 1e9 + 7;

int n, m, t, mat[MAX_N][MAX_N];

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
    for (int i = 2; i <= n; i++)
    {
        int key = 0;
        for (int j = i; j <= n && key == 0; j++)
            if (mat[j][i] > 0)
                key = j;
        if (key != i)
        {
            if (key == 0)
                return 0;
            ret = mod - ret;
            for (int j = 2; j <= n; j++)
                swap(mat[i][j], mat[key][j]);
        }
        int inv = fpow(mat[i][i], mod - 2);
        for (int j = i + 1; j <= n; j++)
        {
            int rate = 1LL * mat[j][i] * inv % mod;
            for (int k = i; k <= n; k++)
                mat[j][k] = (0LL+ mat[j][k] + mod - 1LL * rate * mat[i][k] % mod) % mod;
        }
    }
    for (int i = 2; i <= n; i++)
        ret = 1LL * ret * mat[i][i] % mod;
    return ret;
}

int main()
{
    scanf("%d%d%d", &n, &m, &t);
    for (int i = 1, u, v, w; i <= m; i++)
    {
        scanf("%d%d%d", &u, &v, &w);
        if (t == 0)
        {
            mat[u][v] = (0LL + mat[u][v] + mod - w) % mod;
            mat[v][u] = (0LL + mat[v][u] + mod - w) % mod;
            mat[u][u] = (0LL + mat[u][u] + w) % mod;
            mat[v][v] = (0LL + mat[v][v] + w) % mod;
        }
        else
        {
            mat[v][v] = (0LL + mat[v][v] + w) % mod;
            mat[u][v] = (0LL + mat[u][v] + mod - w) % mod;
        }
    }
    printf("%d\n", det());
    return 0;
}