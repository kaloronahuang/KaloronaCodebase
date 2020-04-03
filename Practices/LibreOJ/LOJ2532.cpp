// LOJ2532.cpp
#include <bits/stdc++.h>

using namespace std;

const int MAX_N = 270, mod = 10007;

int n, m, mat[MAX_N][MAX_N];

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
    int ans = 1;
    for (int i = 2; i <= n; i++)
    {
        int key = i;
        for (; key <= n; key++)
            if (mat[key][i])
                break;
        if (key != i)
        {
            ans = mod - ans;
            for (int j = i; j <= n; j++)
                swap(mat[key][j], mat[i][j]);
        }
        int inv = fpow(mat[i][i], mod - 2);
        for (int j = i + 1; j <= n; j++)
        {
            int rate = 1LL * mat[j][i] * inv % mod;
            if (rate != 0)
                for (int k = i; k <= n; k++)
                    mat[j][k] = (0LL + mat[j][k] + mod - 1LL * rate * mat[i][k] % mod) % mod;
        }
    }
    for (int i = 2; i <= n; i++)
        ans = 1LL * ans * mat[i][i] % mod;
    return ans;
}

int main()
{
    scanf("%d%d", &n, &m);
    for (int i = 1, u, v; i <= m; i++)
    {
        scanf("%d%d", &u, &v);
        mat[u][u]++, mat[v][u]--;
    }
    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= n; j++)
            mat[i][j] = (0LL + mat[i][j] + mod) % mod;
    printf("%d\n", gauss());
    return 0;
}