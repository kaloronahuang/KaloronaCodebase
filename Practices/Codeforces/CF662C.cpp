// CF662C.cpp
#include <bits/stdc++.h>
#define ll long long

using namespace std;

const int MAX_N = 22, MAX_M = 1e5 + 200;

int n, m;
ll ai[1 << MAX_N], bi[1 << MAX_N], stats[MAX_M], poly_siz;

void fwt_xor(ll *arr, int opt)
{
    for (int step = 1; step < poly_siz; step <<= 1)
        for (int j = 0; j < poly_siz; j += (step << 1))
            for (int k = j; k < j + step; k++)
            {
                ll A = arr[k], B = arr[k + step];
                arr[k] = A + B, arr[k + step] = A - B;
                if (opt == -1)
                    arr[k] >>= 1, arr[k + step] >>= 1;
            }
}

int main()
{
    scanf("%d%d", &n, &m);
    for (int i = 1; i <= n; i++)
        for (int j = 1, val; j <= m; j++)
            scanf("%1d", &val), stats[j] |= (val << (i - 1));
    for (int i = 1; i <= m; i++)
        ai[stats[i]]++;
    for (int i = 0; i < (1 << n); i++)
        bi[i] = min(__builtin_popcount(i), n - __builtin_popcount(i));
    poly_siz = 1LL << n;
    fwt_xor(ai, 1), fwt_xor(bi, 1);
    for (int i = 0; i < poly_siz; i++)
        ai[i] *= bi[i];
    fwt_xor(ai, -1);
    ll ans = 0x3f3f3f3f3f3f3f3f;
    for (int i = 0; i < poly_siz; i++)
        ans = min(ans, ai[i]);
    printf("%lld\n", ans);
    return 0;
}