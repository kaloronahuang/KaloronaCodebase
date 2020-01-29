// CF914G.cpp
#include <bits/stdc++.h>

using namespace std;

const int MAX_N = 1e6 + 200, mod = 1e9 + 7, poly_siz = (1 << 17);

int n, seq[MAX_N], popcount[MAX_N], subset[20][MAX_N], A[MAX_N], B[MAX_N], tmp[20][MAX_N], fib[MAX_N];
int X[MAX_N], ci[MAX_N], general[MAX_N];

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

const int inv2 = quick_pow(2, mod - 2);

void fwt_or(int *arr, int opt)
{
    for (int step = 1; step < poly_siz; step <<= 1)
        for (int j = 0; j < poly_siz; j += (step << 1))
            for (int k = j; k < j + step; k++)
                arr[k + step] = (1LL * arr[k + step] + mod + 1LL * arr[k] * opt) % mod;
}

void fwt_and(int *arr, int opt)
{
    for (int step = 1; step < poly_siz; step <<= 1)
        for (int j = 0; j < poly_siz; j += (step << 1))
            for (int k = j; k < j + step; k++)
                arr[k] = (1LL * arr[k] + mod + 1LL * arr[k + step] * opt) % mod;
}

void fwt_xor(int *arr, int opt)
{
    for (int step = 1; step < poly_siz; step <<= 1)
        for (int j = 0; j < poly_siz; j += (step << 1))
            for (int k = j; k < j + step; k++)
            {
                int A = arr[k], B = arr[k + step];
                arr[k] = (1LL * A + B) % mod, arr[k + step] = (1LL * A + mod - B) % mod;
                if (opt == -1)
                    arr[k] = 1LL * arr[k] * inv2 % mod, arr[k + step] = 1LL * arr[k + step] * inv2 % mod;
            }
}

int main()
{
    for (int i = 1; i < poly_siz; i++)
        popcount[i] = popcount[i >> 1] + (i & 1);
    fib[1] = 1;
    for (int i = 2; i < poly_siz; i++)
        fib[i] = (0LL + fib[i - 1] + fib[i - 2]) % mod;
    scanf("%d", &n);
    for (int i = 1; i <= n; i++)
        scanf("%d", &seq[i]), subset[popcount[seq[i]]][seq[i]]++, X[seq[i]]++, ci[seq[i]]++;
    for (int i = 0; i <= 17; i++)
        fwt_or(subset[i], 1);
    for (int i = 0; i <= 17; i++)
    {
        for (int j = 0; j <= i; j++)
            for (int p = 0; p < (1 << 17); p++)
                tmp[i][p] = (1LL * tmp[i][p] + 1LL * subset[i - j][p] * subset[j][p] % mod) % mod;
        fwt_or(tmp[i], -1);
        for (int p = 0; p < poly_siz; p++)
            if (popcount[p] != i)
                tmp[i][p] = 0;
    }
    for (int i = 0; i < poly_siz; i++)
        general[i] = 1LL * fib[i] * tmp[popcount[i]][i] % mod;
    fwt_xor(X, 1);
    for (int i = 0; i < poly_siz; i++)
        X[i] = 1LL * X[i] * X[i] % mod;
    fwt_xor(X, -1);
    for (int i = 0; i < poly_siz; i++)
        X[i] = 1LL * X[i] * fib[i] % mod;
    for (int i = 0; i < poly_siz; i++)
        ci[i] = 1LL * ci[i] * fib[i] % mod;
    fwt_and(general, 1), fwt_and(X, 1), fwt_and(ci, 1);
    for (int i = 0; i < poly_siz; i++)
        X[i] = 1LL * general[i] * X[i] % mod * ci[i] % mod;
    fwt_and(X, -1);
    int ans = 0;
    for (int i = 0; i < 17; i++)
        ans = (1LL * ans + X[(1 << i)]) % mod;
    printf("%d\n", ans);
    return 0;
}