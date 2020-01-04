#pragma GCC optimize(2)
// LOJ152.cpp
#include <bits/stdc++.h>

using namespace std;

const int MAX_N = (1 << 22) + 2000, mod = 1e9 + 9;

int n, fi[22][MAX_N], gi[22][MAX_N], poly_siz, cnt[MAX_N], ans[22][MAX_N], gans[MAX_N];

inline char nc()
{
    static char buf[10000000], *p1 = buf, *p2 = buf;
    return p1 == p2 && (p2 = (p1 = buf) + fread(buf, 1, 10000000, stdin), p1 == p2) ? EOF : *p1++;
}

int read()
{
    int x = 0, f = 1;
    char ch = nc();
    while (!isdigit(ch))
    {
        if (ch == '-')
            f = -1;
        ch = nc();
    }
    while (isdigit(ch))
        x = (x << 3) + (x << 1) + ch - '0', ch = nc();
    return x * f;
}

inline void fwt_or(int *arr, int opt)
{
    for (int step = 1; step < poly_siz; step <<= 1)
        for (int j = 0; j < poly_siz; j += (step << 1))
            for (int k = j; k < j + step; k++)
                arr[k + step] = (1LL * arr[k + step] + mod + 1LL * opt * arr[k]) % mod;
}

int main()
{
    n = read(), poly_siz = (1 << n);
    for (int i = 0; i <= poly_siz; i++)
        cnt[i] = cnt[i >> 1] + (i & 1);
    for (int i = 0; i < poly_siz; i++)
        fi[cnt[i]][i] += read();
    for (int i = 0; i < poly_siz; i++)
        gi[cnt[i]][i] += read();
    for (int i = 0; i <= n; i++)
        fwt_or(fi[i], 1), fwt_or(gi[i], 1);
    for (int i = 0; i <= n; i++)
        for (int j = 0; j <= i; j++)
            for (int k = 0; k < poly_siz; k++)
                ans[i][k] = (1LL * ans[i][k] + 1LL * fi[i - j][k] * gi[j][k] % mod) % mod;
    for (int i = 0; i <= n; i++)
        fwt_or(ans[i], -1);
    for (int i = 0; i < poly_siz; i++)
        printf("%d ", ans[cnt[i]][i]);
    puts("");
    return 0;
}