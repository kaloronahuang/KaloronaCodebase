// A.cpp
#include <bits/stdc++.h>

using namespace std;

const int MAX_N = 550, mod = 1004535809, g = 3;

int n, ai[MAX_N], rev[MAX_N], dp[110][110][MAX_N], poly_bit, poly_siz, trans[MAX_N], inv[MAX_N], fac_inv[MAX_N], tmp[MAX_N], fac[MAX_N];

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

const int gi = fpow(g, mod - 2);

void ntt_initialize()
{
    for (int i = 0; i < poly_siz; i++)
        rev[i] = (rev[i >> 1] >> 1) | ((i & 1) << (poly_bit - 1));
}

void ntt(int *arr, int dft)
{
    for (int i = 0; i < poly_siz; i++)
        if (i < rev[i])
            swap(arr[i], arr[rev[i]]);
    for (int step = 1; step < poly_siz; step <<= 1)
    {
        int omega_n = fpow(dft == 1 ? g : gi, (mod - 1) / (step << 1));
        for (int j = 0; j < poly_siz; j += (step << 1))
        {
            int omega_nk = 1;
            for (int k = j; k < j + step; k++, omega_nk = 1LL * omega_nk * omega_n % mod)
            {
                int t = 1LL * arr[k + step] * omega_nk % mod;
                arr[k + step] = (0LL + arr[k] + mod - t) % mod, arr[k] = (0LL + arr[k] + t) % mod;
            }
        }
    }
    if (dft == -1)
    {
        int inv = fpow(poly_siz, mod - 2);
        for (int i = 0; i < poly_siz; i++)
            arr[i] = 1LL * arr[i] * inv % mod;
    }
}

int main()
{
    scanf("%d", &n);
    for (int i = 1; i <= n; i++)
        scanf("%d", &ai[i]);

    while ((1 << poly_bit) <= (n << 2))
        poly_bit++;
    poly_siz = 1 << poly_bit, ntt_initialize();

    inv[0] = inv[1] = 1;
    for (int i = 2; i < MAX_N; i++)
        inv[i] = 1LL * (mod - mod / i) * inv[mod % i] % mod;
    for (int i = fac_inv[0] = 1; i < MAX_N; i++)
        fac_inv[i] = 1LL * fac_inv[i - 1] * inv[i] % mod;
    for (int i = fac[0] = 1; i < MAX_N; i++)
        fac[i] = 1LL * fac[i - 1] * i % mod;
    dp[0][0][0] = 1;
    for (int i = 1; i <= n; i++)
        for (int j = 0; j <= i; j++)
        {
            // transform from dp[i - 1][j] & dp[i - 1][j - 1] * trans;
            /*
            for (int k = 0; k <= (n << 1); k++)
            {
                dp[i][j][k] = dp[i - 1][j][k];
                if (j > 0)
                    for (int delta = 1; delta <= ai[i] && delta <= k; delta++)
                        dp[i][j][k] = (0LL + dp[i][j][k] + 1LL * fac_inv[delta - 1] * dp[i - 1][j - 1][k - delta] % mod) % mod;
            }
            continue;
            */
            memcpy(dp[i][j], dp[i - 1][j], sizeof(dp[i][j]));
            if (j == 0)
                continue;
            for (int k = 0; k < ai[i]; k++)
                trans[k] = fac_inv[k];
            for (int k = ai[i]; k < poly_siz; k++)
                trans[k] = 0;
            memcpy(tmp, dp[i - 1][j - 1], sizeof(tmp));
            ntt(tmp, 1), ntt(trans, 1);
            for (int k = 0; k < poly_siz; k++)
                tmp[k] = 1LL * tmp[k] * trans[k] % mod;
            ntt(tmp, -1);
            for (int k = 0; k <= (n << 1); k++)
                dp[i][j][k] = (0LL + dp[i][j][k] + (k > 0 ? tmp[k - 1] : 0)) % mod;
        }
    printf("%d ", n);
    for (int s = 2; s <= n; s++)
        printf("%lld ", 1LL * fac[s - 2] * dp[n][s][2 * s - 2] % mod);
    puts("");
    return 0;
}