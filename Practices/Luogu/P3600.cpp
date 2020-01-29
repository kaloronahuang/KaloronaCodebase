// P3600.cpp
#include <bits/stdc++.h>

using namespace std;

const int MAX_N = 2020, mod = 666623333;
typedef pair<int, int> pii;

int n, x, q, lft_most[MAX_N], rig_most[MAX_N], dp[MAX_N][MAX_N], sum[MAX_N][MAX_N], h[MAX_N], g[MAX_N];
pii seg[MAX_N], tmp[MAX_N];

int quick_pow(int bas, int tim)
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

bool compare(pii A, pii B) { return A.first < B.first || (A.first == B.first && A.second < B.second); }

void output()
{
    for (int i = 1; i <= n; i++, puts(""))
        for (int j = 1; j <= n; j++)
            printf("%d ", dp[i][j]);
}

int main()
{
    memset(lft_most, 0x3f, sizeof(lft_most)), memset(rig_most, 128, sizeof(rig_most));
    scanf("%d%d%d", &n, &x, &q), lft_most[0] = rig_most[0] = 0;
    for (int i = 1; i <= q; i++)
        scanf("%d%d", &tmp[i].first, &tmp[i].second);
    sort(tmp + 1, tmp + 1 + q, compare);
    int siz = q;
    q = 0;
    for (int i = 1; i <= siz; i++)
    {
        if (i > 1 && tmp[i].first == tmp[i - 1].first)
            continue;
        while (q && tmp[i].second <= seg[q].second)
            q--;
        seg[++q] = tmp[i];
    }
    for (int i = 1; i <= q; i++)
        for (int ptr = seg[i].first; ptr <= seg[i].second; ptr++)
            lft_most[ptr] = min(lft_most[ptr], i), rig_most[ptr] = max(rig_most[ptr], i);
    int rig_mst = 0;
    for (int i = 1; i <= n; i++)
        if (lft_most[i] == 0x3f3f3f3f)
            lft_most[i] = rig_mst + 1, rig_most[i] = rig_mst;
        else
            rig_mst = max(rig_mst, rig_most[i]);
    dp[0][0] = sum[0][0] = 1, rig_mst = 0;
    for (int i = 1; i <= n; i++)
    {
        while (rig_mst < i - 1 && rig_most[rig_mst] + 1 < lft_most[i])
            rig_mst++;
        for (int j = 1; j <= i; j++)
            dp[i][j] = (0LL + sum[i - 1][j - 1] - (rig_mst ? sum[rig_mst - 1][j - 1] : 0) + mod) % mod;
        for (int j = 0; j <= i; j++)
            sum[i][j] = (sum[i - 1][j] + 1LL * dp[i][j]) % mod;
    }
    for (int i = 1; i <= n; i++)
        if (rig_most[i] == q)
            for (int j = 1; j <= n; j++)
                h[j] = (1LL * dp[i][j] + h[j]) % mod;
    for (int i = 1; i <= x; i++)
        for (int j = 1; j <= n; j++)
            g[i] = (1LL * g[i] + 1LL * quick_pow(i, j) * quick_pow(x - i, n - j) % mod * h[j] % mod) % mod;
    int ans = 0, denominator = quick_pow(quick_pow(x, n), mod - 2);
    for (int i = x; i >= 1; i--)
        g[i] = (0LL + g[i] - g[i - 1] + mod) % mod;
    for (int i = 1; i <= x; i++)
        ans = (1LL * ans + 1LL * i * g[i] % mod * denominator % mod) % mod;
    printf("%d\n", ans);
    // output();
    return 0;
}