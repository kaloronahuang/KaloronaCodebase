// B.cpp
#include <bits/stdc++.h>

using namespace std;

const int MAX_N = 1e6 + 200, mod = 998244353;

int n, m, kind, poly_siz, ai[20], A[int(5e5) + 200][(1 << 8) + 10];

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

int main()
{
    freopen("yuyuko.in", "r", stdin);
    freopen("yuyuko.out", "w", stdout);
    scanf("%d%d%d", &n, &m, &kind);
    poly_siz = (1 << m);
    for (int i = 1; i <= kind; i++)
        scanf("%d", &ai[i]);
    if (kind == 1)
    {
        int ans = 0, bas = 1;
        for (int i = 1, val; i <= n; i++)
            scanf("%d", &val), ans ^= val, bas = 1LL * bas * ai[1] % mod;
        for (int i = 0; i < poly_siz; i++)
            if (i == ans)
                printf("%d ", bas);
            else
                printf("0 ");
        puts("");
        return 0;
    }
    for (int i = 1; i <= n; i++)
        for (int j = 1, val; j <= kind; j++)
            scanf("%d", &val), A[i][val] = (0LL + A[i][val] + ai[j]) % mod;
    for (int i = 1; i <= n; i++)
        fwt_xor(A[i], 1);
    for (int id = 2; id <= n; id++)
        for (int i = 0; i < poly_siz; i++)
            A[1][i] = 1LL * A[1][i] * A[id][i] % mod;
    fwt_xor(A[1], -1);
    for (int i = 0; i < poly_siz; i++)
        printf("%d ", A[1][i]);
    puts("");
    return 0;
}