// P4424.cpp
#include <bits/stdc++.h>

using namespace std;

const int MAX_N = 1010, MAX_M = 5050, mod = 1e9 + 7;

int n, m, q, bin[MAX_N], opt[MAX_M], *rk[2], rk_[2][MAX_M], res[MAX_M];
char str[MAX_M];

int main()
{
    scanf("%d%d%d", &n, &m, &q), bin[1] = 1;
    for (int i = 2; i <= n + 10; i++)
        bin[i] = 2LL * bin[i - 1] % mod;
    rk[0] = rk_[0], rk[1] = rk_[1];
    for (int i = 1; i <= m; i++)
        rk[0][i] = i;
    for (int i = 1; i <= n; i++)
    {
        scanf("%s", str + 1);
        int cnt[2] = {0, m};
        for (int j = 1; j <= m; j++)
            opt[j] = (0LL + opt[j] + (str[j] - '0') * bin[i]) % mod, cnt[str[j] - '0']++;
        cnt[1] = m;
        for (int j = m; j >= 1; j--)
            rk[1][cnt[str[rk[0][j]] - '0']--] = rk[0][j];
        swap(rk[0], rk[1]);
    }
    for (int i = 1; i <= m; i++)
        res[i] = opt[rk[0][i]];
    res[m + 1] = bin[n + 1];
    while (q--)
    {
        scanf("%s", str + 1);
        int up = m + 1, down = 0;
        for (int i = m; i >= 1 && down == 0; i--)
            if (str[rk[0][i]] == '0')
                down = i;
        for (int i = 1; i <= m && up == m + 1; i++)
            if (str[rk[0][i]] == '1')
                up = i;
        if (up < down)
            puts("0");
        else printf("%lld\n", (0LL + res[up] + mod - res[down]) % mod);
    }
    return 0;
}