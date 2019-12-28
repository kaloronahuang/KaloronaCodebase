// BZ4589.cpp
#include <bits/stdc++.h>

using namespace std;

const int MAX_N = 1e5 + 200, mod = 1e9 + 7;

int primes[MAX_N], tot, conv[MAX_N], poly_siz, n, m;
bool vis[MAX_N];

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

void sieve()
{
    vis[1] = vis[0] = true;
    for (int i = 2; i < MAX_N; i++)
    {
        if (!vis[i])
            primes[++tot] = i;
        for (int j = 1; j <= tot && 1LL * i * primes[j] < MAX_N; j++)
        {
            vis[i * primes[j]] = true;
            if (i % primes[j] == 0)
                break;
        }
    }
}

int main()
{
    sieve();
    while (scanf("%d%d", &n, &m) != EOF)
    {
        poly_siz = 1;
        while (poly_siz <= m)
            poly_siz <<= 1;
        for (int i = 0; i <= m; i++)
            conv[i] = (vis[i] == false);
        for (int i = m + 1; i < poly_siz; i++)
            conv[i] = 0;
        fwt_xor(conv, 1);
        for (int i = 0; i < poly_siz; i++)
            conv[i] = quick_pow(conv[i], n);
        fwt_xor(conv, -1);
        printf("%d\n", conv[0]);
    }
    return 0;
}