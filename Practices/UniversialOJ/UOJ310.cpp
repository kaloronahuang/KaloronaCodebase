// UOJ310.cpp
#include <bits/stdc++.h>

using namespace std;

const int MAX_N = 2e6 + 200, mod = 998244353, poly_siz = 1048576;

int n, ai[MAX_N], bi[MAX_N], ci[MAX_N], pw[MAX_N];

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

const int inv2 = fpow(2, mod - 2);

void fwt_xor(int *arr, int dft)
{
    for (int step = 1; step < poly_siz; step <<= 1)
        for (int j = 0; j < poly_siz; j += (step << 1))
            for (int k = j; k < j + step; k++)
            {
                int A = arr[k], B = arr[k + step];
                arr[k] = (0LL + A + B) % mod, arr[k + step] = (0LL + A + mod - B) % mod;
                if (dft == -1)
                    arr[k] = 1LL * arr[k] * inv2 % mod, arr[k + step] = 1LL * arr[k + step] * inv2 % mod;
            }
}

int main()
{
    scanf("%d", &n);
    for (int i = 1; i <= n; i++)
        scanf("%d", &ai[i]), bi[0]++, bi[ai[i]] += 2;
    for (int i = pw[0] = 1; i < poly_siz; i++)
        pw[i] = 3LL * pw[i - 1] % mod;
    fwt_xor(bi, 1);
    for (int i = 0; i < poly_siz; i++)
    {
        int x = (3LL * n + mod - bi[i]) % mod * inv2 % mod * inv2 % mod;
        ci[i] = (x & 1) ? (mod - pw[n - x]) % mod : (pw[n - x]);
    }
    fwt_xor(ci, -1), printf("%lld\n", (0LL + ci[0] + mod - 1) % mod);
    return 0;
}