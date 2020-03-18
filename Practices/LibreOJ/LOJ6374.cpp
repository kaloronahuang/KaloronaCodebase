// LOJ6374.cpp
#include <bits/stdc++.h>

using namespace std;

const int MAX_N = 1e6 + 200, mod = 1e9 + 7, MAX_R = 110;

int tx, ty, mx, my, R, G, K, vecs[MAX_R], fac[MAX_N], fac_inv[MAX_N], inv[MAX_N], upper, block_upper;
int rules[MAX_R][MAX_R], g[MAX_R];

int fpow(int bas, int tim)
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

void preprocess()
{
    upper = max(tx, ty) + R, block_upper = min(tx, ty) / G;
    for (int i = fac[0] = 1; i <= upper; i++)
        fac[i] = 1LL * fac[i - 1] * i % mod;
    fac_inv[upper] = fpow(fac[upper], mod - 2);
    for (int i = upper - 1; i >= 0; i--)
        fac_inv[i] = 1LL * fac_inv[i + 1] * (i + 1) % mod;
    for (int i = inv[0] = 1; i <= upper; i++)
        inv[i] = 1LL * fac_inv[i] * fac[i - 1] % mod;
}

int binomial(int n_, int k_) { return (n_ < k_ || n_ < 0 || k_ < 0) ? 0 : 1LL * fac[n_] * fac_inv[k_] % mod * fac_inv[n_ - k_] % mod; }

int singleInversion(int dist, int limit, int cnt)
{
    int ret = 0;
    for (int i = 0, opt = 1; i <= cnt; i++, opt = mod - opt)
        if (dist + cnt - 1 - i * (limit + 1) >= cnt - 1)
            ret = (0LL + ret + 1LL * opt * binomial(dist + cnt - 1 - i * (limit + 1), cnt - 1) % mod * binomial(cnt, i) % mod) % mod;
        else
            break;
    return ret;
}

int doubleInversion(int distX, int distY, int limitX, int limitY, int tot)
{
    int ret = 0;
    for (int i = 0, opt = (tot & 1) ? mod - 1 : 1; i <= tot; i++, opt = mod - opt)
        ret = (0LL + ret + 1LL * opt * singleInversion(distX, limitX, i) % mod * singleInversion(distY, limitY, i) % mod * binomial(tot, i) % mod) % mod;
    return ret;
}

int main()
{
    scanf("%d%d%d%d%d%d%d", &tx, &ty, &mx, &my, &R, &G, &K);
    for (int i = 1; i <= K; i++)
        scanf("%d", &vecs[i]), vecs[i] /= G;
    sort(vecs + 1, vecs + 1 + K), K = unique(vecs + 1, vecs + 1 + K) - vecs - 1;
    preprocess(), rules[0][0] = 1;
    for (int i = 1; i <= R && i <= block_upper; i++)
        for (int j = 1; j <= K; j++)
            for (int siz = vecs[j]; siz <= block_upper; siz++)
                rules[i][siz] = (0LL + rules[i][siz] + rules[i - 1][siz - vecs[j]]) % mod;
    for (int i = 0; i <= R && i <= block_upper; i++)
        for (int j = 0; j <= block_upper; j++)
            if (rules[i][j])
                g[i] = (0LL + g[i] + 1LL * rules[i][j] * doubleInversion(tx - j * G, ty - j * G, mx, my, R - i) % mod * binomial(R, i) % mod) % mod;
    int ans = 0;
    for (int i = 0, opt = 1; i <= R && i <= block_upper; i++, opt = mod - opt)
        ans = (0LL + ans + 1LL * opt * g[i] % mod) % mod;
    printf("%d\n", ans);
    return 0;
}