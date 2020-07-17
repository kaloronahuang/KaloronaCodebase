// UOJ482.cpp
#include <bits/stdc++.h>

using namespace std;

const int MAX_N = 110, mod = 998244353;

int n, m, typ, ai[MAX_N], ans[MAX_N], f[MAX_N][MAX_N], inv[MAX_N], prob[MAX_N][MAX_N];
int trans[MAX_N][MAX_N], tmp[MAX_N][MAX_N], q;

void solve(int x, int y)
{
    memset(f, 0, sizeof(f)), memset(prob, 0, sizeof(prob));
    f[0][0] = 1;
    for (int i = 0; i <= x; i++)
        for (int j = 0; j <= y; j++)
        {
            if (i < x)
            {
                int v = 1LL * f[i][j] * inv[n - i - j] % mod * (x - i) % mod;
                f[i + 1][j] = (0LL + f[i + 1][j] + v) % mod;
                prob[i + 1][i + j + 1] = (0LL + prob[i + 1][i + j + 1] + v) % mod;
            }
            if (j < y)
            {
                int v = 1LL * f[i][j] * inv[n - i - j] % mod * (y - j) % mod;
                f[i][j + 1] = (0LL + f[i][j + 1] + v) % mod;
                prob[j + x + 1][i + j + 1] = (0LL + prob[j + x + 1][i + j + 1] + v) % mod;
            }
        }
    memcpy(tmp, trans, sizeof(tmp)), memset(trans, 0, sizeof(trans));
    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= n; j++)
            for (int k = 1; k <= n; k++)
                trans[i][j] = (0LL + trans[i][j] + 1LL * tmp[i][k] * prob[k][j] % mod) % mod;
}

int main()
{
    scanf("%d%d%d", &n, &m, &typ);
    for (int i = 1; i <= m; i++)
        scanf("%d", &ai[i]);
    for (int i = 1; i <= n; i++)
        trans[i][i] = 1;
    inv[0] = inv[1] = 1;
    for (int i = 2; i < MAX_N; i++)
        inv[i] = 1LL * (mod - mod / i) * inv[mod % i] % mod;
    for (int i = 1; i <= m; i++)
        solve(ai[i], n - ai[i]);
    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= n; j++)
            ans[i] = (0LL + ans[i] + 1LL * j * (typ == 1 ? 1 : j) % mod * trans[j][i] % mod) % mod;
    scanf("%d", &q);
    while (q--)
    {
        int x;
        scanf("%d", &x), printf("%d\n", ans[x]);
    }
    return 0;
}