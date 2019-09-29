// B.cpp
#include <bits/stdc++.h>

using namespace std;

const int MAX_N = 1010, mod = 1000000007;

int n, m, mat[MAX_N][MAX_N], ni[MAX_N], mi[MAX_N];

int quick_pow(int bas, int tim)
{
    int ans = 1;
    while (tim)
    {
        if (tim & 1)
            ans = 1LL * ans * bas % mod;
        bas = 1LL * bas * bas % mod;
        tim >>= 1;
    }
    return ans;
}

void godie() { puts("0"), exit(0); }

int main()
{
    scanf("%d%d", &n, &m);
    for (int i = 1; i <= n; i++)
        scanf("%d", &ni[i]);
    for (int i = 1; i <= m; i++)
        scanf("%d", &mi[i]);
    bool flag = true;
    for (int i = 1; i <= n; i++)
    {
        for (int j = 1; j <= ni[i]; j++)
        {
            if (mat[i][j] != 0 && mat[i][j] != 1)
                godie();
            mat[i][j] = 1;
        }
        if (mat[i][ni[i] + 1] != 0 && mat[i][ni[i] + 1] != -1)
            godie();
        mat[i][ni[i] + 1] = -1;
    }
    for (int i = 1; i <= m; i++)
    {
        for (int j = 1; j <= mi[i]; j++)
        {
            if (mat[j][i] != 0 && mat[j][i] != 1)
                godie();
            mat[j][i] = 1;
        }
        if (mat[mi[i] + 1][i] != 0 && mat[mi[i] + 1][i] != -1)
            godie();
        mat[mi[i] + 1][i] = -1;
    }
    int ans = 0;
    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= m; j++)
            ans += (mat[i][j] == 0);
    printf("%d", quick_pow(2, ans));
    return 0;
}