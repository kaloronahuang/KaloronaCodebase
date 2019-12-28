// P4717.cpp
// NTT;
#include <bits/stdc++.h>

using namespace std;

const int MAX_N = (1 << 17) + 200, mod = 998244353;

int n, Ai[MAX_N], Bi[MAX_N], C[MAX_N], A[MAX_N], B[MAX_N];

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
    for (int step = 1; step < n; step <<= 1)
        for (int j = 0; j < n; j += (step << 1))
            for (int k = j; k < j + step; k++)
                arr[k + step] = (1LL * arr[k + step] + mod + 1LL * arr[k] * opt) % mod;
}

void fwt_and(int *arr, int opt)
{
    for (int step = 1; step < n; step <<= 1)
        for (int j = 0; j < n; j += (step << 1))
            for (int k = j; k < j + step; k++)
                arr[k] = (1LL * arr[k] + mod + 1LL * arr[k + step] * opt) % mod;
}

void fwt_xor(int *arr, int opt)
{
    for (int step = 1; step < n; step <<= 1)
        for (int j = 0; j < n; j += (step << 1))
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
    scanf("%d", &n), n = 1 << n;
    for (int i = 0; i < n; i++)
        scanf("%d", &Ai[i]);
    for (int i = 0; i < n; i++)
        scanf("%d", &Bi[i]);

    memcpy(A, Ai, sizeof(A)), memcpy(B, Bi, sizeof(B));
    fwt_or(A, 1), fwt_or(B, 1);
    for (int i = 0; i < n; i++)
        C[i] = 1LL * A[i] * B[i] % mod;
    fwt_or(C, -1);
    for (int i = 0; i < n; i++)
        printf("%d ", C[i]);
    puts("");

    memcpy(A, Ai, sizeof(A)), memcpy(B, Bi, sizeof(B));
    fwt_and(A, 1), fwt_and(B, 1);
    for (int i = 0; i < n; i++)
        C[i] = 1LL * A[i] * B[i] % mod;
    fwt_and(C, -1);
    for (int i = 0; i < n; i++)
        printf("%d ", C[i]);
    puts("");

    memcpy(A, Ai, sizeof(A)), memcpy(B, Bi, sizeof(B));
    fwt_xor(A, 1), fwt_xor(B, 1);
    for (int i = 0; i < n; i++)
        C[i] = 1LL * A[i] * B[i] % mod;
    fwt_xor(C, -1);
    for (int i = 0; i < n; i++)
        printf("%d ", C[i]);
    puts("");
    return 0;
}