// FOJ6445.cpp
#include <bits/stdc++.h>
#pragma GCC optimize(2)

using namespace std;

const char *sigma = "syfaknoi";
const int MAX_N = 4e6 + 200, mod = 998244353, G = 3;
const double pi = acos(-1.0);
typedef complex<double> cd;

int limit, n, m, diff[MAX_N], poly_bit, poly_siz, rev[MAX_N], cnt1[300], cnt2[300];
char str1[MAX_N], str2[MAX_N], vec[MAX_N];
int A[MAX_N], B[MAX_N];

void fileIO()
{
    freopen("string.in", "r", stdin);
    freopen("string.out", "w", stdout);
}

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

/*

void fft(cd *arr, int dft)
{
    for (int i = 0; i < poly_siz; i++)
        if (i < rev[i])
            swap(arr[i], arr[rev[i]]);
    for (int step = 1; step < poly_siz; step <<= 1)
    {
        cd omega_n = exp(cd(0, dft * pi / step));
        for (int j = 0; j < poly_siz; j += (step << 1))
        {
            cd omega_nk(1, 0);
            for (int k = j; k < j + step; k++, omega_nk *= omega_n)
            {
                cd t = arr[k + step] * omega_nk;
                arr[k + step] = arr[k] - t, arr[k] += t;
            }
        }
    }
    if (dft == -1)
        for (int i = 0; i < poly_siz; i++)
            arr[i] /= poly_siz;
}

*/

int main()
{
    // fileIO();
    scanf("%d%s%s", &limit, str1, str2);
    n = strlen(str1), m = strlen(str2);
    reverse(str2, str2 + m);
    for (int i = 0; i < n; i++)
        cnt1[str1[i]]++;
    for (int i = 0; i < m; i++)
        cnt2[str2[i]]++;
    int len = (n + m + 1);
    while ((1 << poly_bit) < len)
        poly_bit++;
    poly_siz = (1 << poly_bit);
    ntt_initialize();
    for (int idx = 0; idx < 8; idx++)
    {
        char ch = sigma[idx];
        if (cnt1[ch] == 0 || cnt2[ch] == 0)
            continue;
        for (int i = 0; i < n; i++)
            A[i] = (str1[i] == ch);
        for (int i = n; i < poly_siz; i++)
            A[i] = 0;
        for (int i = 0; i < m; i++)
            B[i] = (str2[i] == ch);
        for (int i = m; i < poly_siz; i++)
            B[i] = 0;

        ntt(A, 1), ntt(B, 1);
        for (int i = 0; i < poly_siz; i++)
            A[i] = 1LL * A[i] * B[i] % mod;
        ntt(A, -1);

        for (int i = 0; i < n - m + 1; i++)
            diff[i] += A[m + i - 1];
        continue;
    }
    int ans = 0;
    for (int i = 0; i < n - m + 1; i++)
        ans += (diff[i] >= (m - limit));
    printf("%d\n", ans);
    return 0;
}