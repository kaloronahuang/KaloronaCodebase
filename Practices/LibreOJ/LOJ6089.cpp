// LOJ6089.cpp
#include <bits/stdc++.h>

using namespace std;

const int MAX_N = 1e5 + 200, mod = 23333333, BLOCK = 500;

int n, f[BLOCK][MAX_N], bsiz, g[BLOCK][MAX_N], S[MAX_N];

int main()
{
    scanf("%d", &n), bsiz = sqrt(n);
    f[0][0] = 1;
    for (int i = 1; i <= bsiz; i++)
        for (int j = 0; j < i; j++)
        {
            int tot = 0;
            for (int k = j; k <= n; k += i)
                S[++tot] = f[i - 1][k];
            for (int k = 1; k <= tot; k++)
                S[k] = (0LL + S[k] + S[k - 1]) % mod;
            for (int k = j, id = 1; k <= n; k += i, id++)
                f[i][k] = (0LL + f[i][k] + S[id] + mod - S[max(0, id - i - 1)]) % mod;
        }
    memset(S, 0, sizeof(S));
    g[0][0] = S[0] = 1;
    for (int i = 1; i <= bsiz; i++)
        for (int j = 0; j <= n; j++)
        {
            if (j >= i)
                g[i][j] = (0LL + g[i][j] + g[i][j - i]) % mod;
            if (j >= bsiz + 1)
                g[i][j] = (0LL + g[i][j] + g[i - 1][j - (bsiz + 1)]) % mod;
            S[j] = (0LL + S[j] + g[i][j]) % mod;
        }
    int ans = 0;
    for (int i = 0; i <= n; i++)
        ans = (0LL + ans + 1LL * f[bsiz][i] * S[n - i] % mod) % mod;
    printf("%d\n", ans);
    return 0;
}