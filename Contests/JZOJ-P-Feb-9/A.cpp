// A.cpp
#include <bits/stdc++.h>

using namespace std;

const int MAX_N = 2e5 + 200, mod = 1e9 + 7;

int n, m, q, coeff_c[20], coeff_d[20], ai[MAX_N], bi[MAX_N], S[20][20], binomial[20][20], fac[MAX_N], fac_inv[MAX_N];
int pre_pow[20][MAX_N];
char cmdlet[20];

struct fenwick_tree
{

    int nodes[MAX_N];

    inline int lowbit(int x) { return x & (-x); }

    void update(int x, int d)
    {
        for (; x <= max(n, m); x += lowbit(x))
            nodes[x] = (0LL + nodes[x] + d) % mod;
    }

    int query(int x, int ret = 0)
    {
        for (; x; x -= lowbit(x))
            ret = (0LL + ret + nodes[x]) % mod;
        return ret;
    }
} trA[12], trB[12];

void fileIO() { freopen("matrix.in", "r", stdin), freopen("matrix.out", "w", stdout); }

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

void initialize()
{
    for (int i = 1; i <= n; i++)
    {
        ai[i] = 1LL * (i - 1) * m % mod;
        for (int t = 0; t <= 10; t++)
            trA[t].update(i, 1LL * ai[i] * quick_pow(mod - i, t) % mod);
    }
    for (int i = 1; i <= m; i++)
    {
        bi[i] = i;
        for (int t = 0; t <= 10; t++)
            trB[t].update(i, 1LL * bi[i] * quick_pow(mod - i, t) % mod);
    }
    S[0][0] = 1;
    for (int i = 1; i <= 10; i++)
        for (int j = 1; j <= i; j++)
            S[i][j] = (S[i - 1][j - 1] + 1LL * (i - 1) * S[i - 1][j] % mod) % mod;
    binomial[0][0] = 1;
    for (int i = 1; i <= 10; i++)
    {
        binomial[i][0] = binomial[i][i] = 1;
        for (int j = 1; j < i; j++)
            binomial[i][j] = (0LL + binomial[i - 1][j - 1] + binomial[i - 1][j]) % mod;
    }
    int max_level = max(n, m) + 20;
    for (int i = fac[0] = 1; i <= max_level; i++)
        fac[i] = 1LL * fac[i - 1] * i % mod;
    fac_inv[max_level] = quick_pow(fac[max_level], mod - 2);
    for (int i = max_level - 1; i >= 0; i--)
        fac_inv[i] = 1LL * fac_inv[i + 1] * (i + 1) % mod;
    for (int t = 0; t <= 10; t++)
        for (int i = 1; i <= max(n, m); i++)
            pre_pow[t][i] = (0LL + pre_pow[t][i - 1] + quick_pow(mod - i, t)) % mod;
}

int main()
{
    // fileIO();
    scanf("%d%d%d", &n, &m, &q), initialize();
    while (q--)
    {
        int x, y, xs, ys, k;
        scanf("%s%d%d", cmdlet + 1, &x, &y);
        if (cmdlet[1] == 'R')
        {
            for (int t = 0; t <= 10; t++)
                trA[t].update(x, (mod - 1LL * ai[x] * quick_pow(mod - x, t) % mod) % mod);
            for (int t = 0; t <= 10; t++)
                trA[t].update(y, (mod - 1LL * ai[y] * quick_pow(mod - y, t) % mod) % mod);
            swap(ai[x], ai[y]);
            for (int t = 0; t <= 10; t++)
                trA[t].update(x, 1LL * ai[x] * quick_pow(mod - x, t) % mod);
            for (int t = 0; t <= 10; t++)
                trA[t].update(y, 1LL * ai[y] * quick_pow(mod - y, t) % mod);
        }
        else if (cmdlet[1] == 'C')
        {
            for (int t = 0; t <= 10; t++)
                trB[t].update(x, (mod - 1LL * bi[x] * quick_pow(mod - x, t) % mod) % mod);
            for (int t = 0; t <= 10; t++)
                trB[t].update(y, (mod - 1LL * bi[y] * quick_pow(mod - y, t) % mod) % mod);
            swap(bi[x], bi[y]);
            for (int t = 0; t <= 10; t++)
                trB[t].update(x, 1LL * bi[x] * quick_pow(mod - x, t) % mod);
            for (int t = 0; t <= 10; t++)
                trB[t].update(y, 1LL * bi[y] * quick_pow(mod - y, t) % mod);
        }
        else
        {
            scanf("%d%d%d", &xs, &ys, &k);
            memset(coeff_c, 0, sizeof(coeff_c)), memset(coeff_d, 0, sizeof(coeff_d));
            // construct the A first;
            for (int d = 0; d <= k; d++)
            {
                int opt = 1LL * (((k - d) & 1) ? mod - 1 : 1) * S[k][d] % mod;
                for (int e = 0, pw = 1; e <= d; e++)
                {
                    int tmp = 1LL * opt * binomial[d][e] % mod * pw % mod, idx = d - e;
                    coeff_c[idx] = (0LL + coeff_c[idx] + tmp) % mod, pw = 1LL * pw * (xs + k) % mod;
                }
            }
            // construct the B now;
            for (int d = 0; d <= k; d++)
            {
                int opt = 1LL * (((k - d) & 1) ? mod - 1 : 1) * S[k][d] % mod;
                for (int e = 0, pw = 1; e <= d; e++)
                {
                    int tmp = 1LL * opt * binomial[d][e] % mod * pw % mod, idx = d - e;
                    coeff_d[idx] = (0LL + coeff_d[idx] + tmp) % mod, pw = 1LL * pw * (ys + k) % mod;
                }
            }
            int k_inv = quick_pow(fac[k], mod - 2);
            for (int i = 0; i <= k; i++)
                coeff_c[i] = 1LL * coeff_c[i] * k_inv % mod, coeff_d[i] = 1LL * coeff_d[i] * k_inv % mod;
            // we can calc now;
            int ans_a = 0, ans_b = 0;
            for (int t = 0; t <= k; t++)
            {
                int int_a = (0LL + trA[t].query(xs) + mod - trA[t].query(x - 1)) % mod;
                int int_b = (0LL + trB[t].query(ys) + mod - trB[t].query(y - 1)) % mod;
                ans_a = (0LL + ans_a + 1LL * int_a * coeff_c[t] % mod) % mod;
                ans_b = (0LL + ans_b + 1LL * int_b * coeff_d[t] % mod) % mod;
            }
            // calc the ci & di itself;
            int pre_c = 0, pre_d = 0;
            for (int t = 0; t <= k; t++)
                pre_c = (0LL + pre_c + 1LL * coeff_c[t] * ((0LL + pre_pow[t][xs] + mod - pre_pow[t][x - 1]) % mod) % mod) % mod;
            for (int t = 0; t <= k; t++)
                pre_d = (0LL + pre_d + 1LL * coeff_d[t] * ((0LL + pre_pow[t][ys] + mod - pre_pow[t][y - 1]) % mod) % mod) % mod;
            int ans = (1LL * ans_a * pre_d % mod + 1LL * ans_b * pre_c % mod) % mod;
            printf("%d\n", ans);
        }
    }
    return 0;
}