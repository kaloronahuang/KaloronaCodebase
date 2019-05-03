// P4111.cpp
#include <bits/stdc++.h>
using namespace std;

const int MAX_N = 108, mod = 1e9;
char mp[MAX_N][MAX_N];
int mat[MAX_N][MAX_N], ans, n, m, tot, idx[MAX_N][MAX_N];

void connect(int src, int dst)
{
    mat[src][dst]--, mat[dst][src]--, mat[src][src]++, mat[dst][dst]++;
}

int solve(int rg)
{
    int ans = 1;
    for (int i = 1; i <= rg; ++i)
    {
        for (int k = i + 1; k <= rg; ++k)
        {
            while (mat[k][i])
            {
                int d = mat[i][i] / mat[k][i];
                for (int j = i; j <= rg; ++j)
                    mat[i][j] = (mat[i][j] - 1LL * d * mat[k][j] % mod + mod) % mod;
                std::swap(mat[i], mat[k]), ans = -ans;
            }
        }
        ans = 1LL * ans * mat[i][i] % mod, ans = (ans + mod) % mod;
    }
    return ans;
}

int main()
{
    scanf("%d%d", &n, &m);
    for (int i = 1; i <= n; i++)
        scanf("%s", mp[i] + 1);
    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= m; j++)
            if (mp[i][j] == '.')
                idx[i][j] = ++tot;
    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= m; j++)
            if (mp[i][j] == '.')
            {
                if (idx[i - 1][j])
                    connect(idx[i][j], idx[i - 1][j]);
                if (idx[i][j - 1])
                    connect(idx[i][j], idx[i][j - 1]);
            }
    printf("%d\n", solve(tot - 1));
    return 0;
}