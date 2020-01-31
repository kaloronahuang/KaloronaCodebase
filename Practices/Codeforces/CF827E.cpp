// CF827E.cpp
#include <bits/stdc++.h>

using namespace std;

const int MAX_N = 2e6 + 200, mod = 998244353, G = 3;

int T, n, poly_bit, poly_siz, rev[MAX_N], attach[MAX_N], A[MAX_N], B[MAX_N], diff[MAX_N], seq[MAX_N];
char str[MAX_N];

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

const int Gi = quick_pow(G, mod - 2);

void ntt_initialize()
{
    for (int i = 0; i < poly_siz; i++)
        rev[i] = ((rev[i >> 1] >> 1) | ((i & 1) << (poly_bit - 1)));
}

void ntt(int *arr, int dft)
{
    for (int i = 0; i < poly_siz; i++)
        if (i < rev[i])
            swap(arr[i], arr[rev[i]]);
    for (int step = 1; step < poly_siz; step <<= 1)
    {
        int omega_n = quick_pow(dft == 1 ? G : Gi, (mod - 1) / (step << 1));
        for (int j = 0; j < poly_siz; j += (step << 1))
        {
            int omega_nk = 1;
            for (int k = j; k < j + step; k++, omega_nk = 1LL * omega_nk * omega_n % mod)
            {
                int t = 1LL * omega_nk * arr[k + step] % mod;
                arr[k + step] = (1LL * arr[k] + mod - t) % mod;
                arr[k] = (1LL * arr[k] + t) % mod;
            }
        }
    }
    if (dft == -1)
    {
        int inv = quick_pow(poly_siz, mod - 2);
        for (int i = 0; i < poly_siz; i++)
            arr[i] = 1LL * arr[i] * inv % mod;
    }
}

int main()
{
    scanf("%d", &T);
    while (T--)
    {
        memset(diff, 0, sizeof(diff));
        scanf("%d%s", &n, str);
        poly_bit = poly_siz = 0;
        while ((1 << poly_bit) <= (n << 2))
            poly_bit++;
        poly_siz = (1 << poly_bit);
        ntt_initialize();
        // encode;
        for (int i = 0; i < n; i++)
            if (str[i] == 'V')
                seq[i] = 1;
            else if (str[i] == 'F')
                seq[i] = 2;
            else
                seq[i] = 0;
        // first term;
        memset(A, 0, sizeof(A)), memset(B, 0, sizeof(B));
        for (int i = 0; i < n; i++)
            A[i] = seq[i] * seq[i] * seq[i];
        for (int i = 0; i < n; i++)
            B[n - i - 1] = seq[i];
        ntt(A, 1), ntt(B, 1);
        for (int i = 0; i < poly_siz; i++)
            diff[i] = (diff[i] + 1LL * A[i] * B[i] % mod) % mod;
        // second term;
        memset(A, 0, sizeof(A)), memset(B, 0, sizeof(B));
        for (int i = 0; i < n; i++)
            A[i] = seq[i] * seq[i];
        for (int i = 0; i < n; i++)
            B[n - i - 1] = seq[i] * seq[i];
        ntt(A, 1), ntt(B, 1);
        for (int i = 0; i < poly_siz; i++)
            diff[i] = (0LL + diff[i] + mod - 2LL * A[i] * B[i] % mod) % mod;
        // third term;
        memset(A, 0, sizeof(A)), memset(B, 0, sizeof(B));
        for (int i = 0; i < n; i++)
            A[i] = seq[i];
        for (int i = 0; i < n; i++)
            B[n - i - 1] = seq[i] * seq[i] * seq[i];
        ntt(A, 1), ntt(B, 1);
        for (int i = 0; i < poly_siz; i++)
            A[i] = 1LL * A[i] * B[i] % mod;
        for (int i = 0; i < poly_siz; i++)
            diff[i] = (diff[i] + 1LL * A[i] * B[i] % mod) % mod;
        ntt(diff, -1);
        int cnt = 0;
        for (int i = 1; i <= n; i++)
            if (diff[i + n - 1] == 0)
                cnt++;
        printf("%d\n", cnt);
        for (int i = 1; i <= n; i++)
            if (diff[i + n - 1] == 0)
                printf("%d ", i);
        puts("");
    }
    return 0;
}