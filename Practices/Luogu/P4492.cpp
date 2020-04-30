// P4492.cpp
#include <bits/stdc++.h>

using namespace std;

const int MAX_N = 2020;

int n, binomial[MAX_N][MAX_N], mod, fac[MAX_N];

int main()
{
    scanf("%d%d", &n, &mod);
    binomial[0][0] = 1;
    for (int i = fac[0] = 1; i <= n; i++)
    {
        binomial[i][0] = binomial[i][i] = 1, fac[i] = 1LL * fac[i - 1] * i % mod;
        for (int j = 1; j < i; j++)
            binomial[i][j] = (0LL + binomial[i - 1][j - 1] + binomial[i - 1][j]) % mod;
    }
    int ans = 0;
    for (int id = 2; id <= n; id++)
        for (int siz = 1; siz <= n - id + 1; siz++)
            ans = (0LL + ans + 1LL * fac[siz] * binomial[n - id][siz - 1] % mod * siz % mod * (n - siz) % mod * (n - siz - 1 >= 0 ? fac[n - siz - 1] : 0) % mod * id % mod * (id - 1) % mod) % mod;
    printf("%d\n", ans);
    return 0;
}