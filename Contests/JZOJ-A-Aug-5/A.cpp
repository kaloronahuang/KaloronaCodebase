// A.cpp
#include <bits/stdc++.h>

using namespace std;

const int MAX_N = 1e6 + 200, mod = 1e9 + 7;

int row[MAX_N], col[MAX_N], n, m, k;
long long ans = 0;
char opt[20];

int main()
{
    scanf("%d%d%d", &n, &m, &k);
    for (int i = 1; i <= max(n, m); i++)
        row[i] = col[i] = 1;

    while (k--)
    {
        int x, y;
        scanf("%s%d%d", opt + 1, &x, &y);
        if (opt[1] == 'R')
            row[x] = 1LL * row[x] * y % mod;
        else
            col[x] = 1LL * col[x] * y % mod;
    }
    int colBatch = 0, batch = 0;
    for (int i = 1; i <= n; i++)
        colBatch = (1LL * colBatch + 1LL * (1LL * (i - 1) * m % mod + 1) % mod * row[i] % mod) % mod, batch = (1LL * batch + 1LL * row[i]) % mod;
    int current = colBatch;
    for (int j = 1; j <= m; j++)
        ans = (ans + 1LL * current * col[j] % mod) % mod, current = (1LL * current + 1LL * batch) % mod;
    printf("%lld", ans);
    return 0;
}