// P4828.cpp
#include <bits/stdc++.h>

using namespace std;

const int MAX_N = 1e6 + 200, mod = 998244353;

int seq[MAX_N], C[2020][2020], n, q;

int main()
{
    C[1][1] = 1;
    for (int i = 2; i < 2020; i++)
    {
        C[i][1] = C[i][i] = 1;
        for (int j = 2; j < i; j++)
            C[i][j] = (C[i - 1][j - 1] + C[i - 1][j]) % mod;
    }
    scanf("%d", &n);
    for (int i = 1; i <= n; i++)
        scanf("%d", &seq[i]);
    scanf("%d", &q);
    while (q--)
    {
        int x, y, ans = 0;
        scanf("%d%d", &x, &y), x++;
        for (int p = 0; p < x; p++)
            ans = (1LL * ans + 1LL * C[x][p + 1] * seq[(y + (p - 1)) % n + 1] % mod) % mod;
        printf("%d\n", ans);
    }
    return 0;
}