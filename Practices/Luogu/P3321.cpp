// P3321.cpp
#include <bits/stdc++.h>

using namespace std;

const int MAX_N = 2e5 + 200, mod = 1004535809, G = 3;

int n, m, target, Slen, rev[MAX_N], primes[MAX_N], ptot, g, A[MAX_N], B[MAX_N], tmp[MAX_N];
unordered_map<int, int> log_mp;

int quick_pow(int bas, int tim, int cmod)
{
    int ret = 1;
    while (tim)
    {
        if (tim & 1)
            ret = 1LL * ret * bas % cmod;
        bas = 1LL * bas * bas % cmod;
        tim >>= 1;
    }
    return ret;
}

const int Gi = quick_pow(G, mod - 2, mod);

int getRoot(int p)
{
    ptot = 0;
    int x = p - 1;
    for (int i = 2; 1LL * i * i <= x; i++)
        if (x % i == 0)
        {
            primes[++ptot] = i;
            while (x % i == 0)
                x /= i;
        }
    if (x > 1)
        primes[++ptot] = x;
    for (int i = 2; i <= p - 1; i++)
    {
        bool flag = true;
        for (int k = 1; flag && k <= ptot; k++)
            if (quick_pow(i, (p - 1) / primes[k], p) == 1)
                flag = false;
        if (flag)
            return i;
    }
    return 0;
}

void ntt_initialize(int poly_bit)
{
    for (int i = 1; i < (1 << poly_bit); i++)
        rev[i] = ((rev[i >> 1] >> 1) | ((i & 1) << (poly_bit - 1)));
}

void ntt(int *arr, int dft, int poly_siz)
{
    for (int i = 0; i < poly_siz; i++)
        if (i < rev[i])
            swap(arr[i], arr[rev[i]]);
    for (int step = 1; step < poly_siz; step <<= 1)
    {
        int omega_n = quick_pow(dft == 1 ? G : Gi, (mod - 1) / (step << 1), mod);
        for (int j = 0; j < poly_siz; j += (step << 1))
        {
            int omega_nk = 1;
            for (int k = j; k < j + step; k++, omega_nk = 1LL * omega_nk * omega_n % mod)
            {
                int t = 1LL * omega_nk * arr[k + step] % mod;
                arr[k + step] = (0LL + arr[k] + mod - t) % mod, arr[k] = (0LL + arr[k] + t) % mod;
            }
        }
    }
    if (dft == -1)
    {
        int inv = quick_pow(poly_siz, mod - 2, mod);
        for (int i = 0; i < poly_siz; i++)
            arr[i] = 1LL * arr[i] * inv % mod;
    }
}

int tA[MAX_N], tB[MAX_N], res[MAX_N];

int main()
{
    scanf("%d%d%d%d", &n, &m, &target, &Slen), g = getRoot(m);
    for (int i = 0; i < m - 1; i++)
        log_mp[quick_pow(g, i, m)] = i;
    for (int i = 1, val; i <= Slen; i++)
    {
        scanf("%d", &val), val %= m;
        if (val)
            A[log_mp[val % m]]++;
    }
    B[log_mp[1]] = 1;
    int poly_bit = 0, poly_siz = 1;
    while (poly_siz <= (m << 1))
        poly_siz <<= 1, poly_bit++;
    ntt_initialize(poly_bit);
    while (n)
    {
        if (n & 1)
        {
            memcpy(tA, A, sizeof(A)), memcpy(tB, B, sizeof(B));
            ntt(tA, 1, poly_siz), ntt(tB, 1, poly_siz);
            for (int i = 0; i < poly_siz; i++)
                tA[i] = 1LL * tA[i] * tB[i] % mod;
            ntt(tA, -1, poly_siz);
            for (int i = 0; i < m - 1; i++)
                B[i] = (0LL + tA[i] + tA[i + m - 1]) % mod;
        }
        memcpy(tA, A, sizeof(A));
        ntt(tA, 1, poly_siz);
        for (int i = 0; i < poly_siz; i++)
            tA[i] = 1LL * tA[i] * tA[i] % mod;
        ntt(tA, -1, poly_siz);
        for (int i = 0; i < m - 1; i++)
            A[i] = (0LL + tA[i] + tA[i + m - 1]) % mod;
        n >>= 1;
    }
    printf("%d\n", B[log_mp[target]]);
    return 0;
}