// P4221.cpp
#pragma GCC optimize(2)
#include <bits/stdc++.h>

using namespace std;

const int MAX_N = 25, MAX_M = MAX_N * MAX_N, mod = 998244353;

int n, m, p, wi[MAX_N], deg[MAX_N], G[MAX_N], mem[MAX_N], lg2[1 << 21], weights[1 << 21], cnt[1 << 21];
int poly_siz, F[22][1 << 21], H[22][1 << 21], tmp[1 << 21], wpow[1 << 21], winv[1 << 21];
bool valid[1 << 21];

int find(int x) { return mem[x] == x ? x : mem[x] = find(mem[x]); }

int lowbit(int x) { return x & (-x); }

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

void fwt_or(int *arr, int dft)
{
    dft = (0LL + dft + mod) % mod;
    for (int step = 1; step < poly_siz; step <<= 1)
        for (int j = 0; j < poly_siz; j += (step << 1))
            for (int k = j; k < j + step; k++)
                arr[k + step] = (0LL + arr[k + step] + 1LL * dft * arr[k] % mod) % mod;
}

int main()
{
    scanf("%d%d%d", &n, &m, &p);
    for (int i = 1, u, v; i <= m; i++)
        scanf("%d%d", &u, &v), G[u] |= (1 << (v - 1)), G[v] |= (1 << (u - 1));
    for (int i = 1; i <= n; i++)
        scanf("%d", &wi[i]);
    // printf("%.3lf\n", 1.0 * clock() / CLOCKS_PER_SEC);
    cnt[1] = 1;
    for (int i = 2; i < (1 << n); i++)
        lg2[i] = lg2[i >> 1] + 1, cnt[i] = cnt[i >> 1] + (i & 1);
    for (int stat = 1; stat < (1 << n); stat++)
    {
        memset(deg, 0, sizeof(deg));
        for (int i = 1; i <= n; i++)
            mem[i] = i;
        for (int u = 1; u <= n; u++)
            if (stat & (1 << (u - 1)))
                deg[u] = cnt[stat & G[u]];
        int rt = 0;
        for (int u = 1; u <= n; u++)
            if (stat & (1 << (u - 1)))
            {
                int acc = stat & G[u];
                while (acc)
                    mem[find(u)] = find(lg2[lowbit(acc)] + 1), acc -= lowbit(acc);
            }
        for (int i = 1; i <= n; i++)
            if (stat & (1 << (i - 1)))
                weights[stat] += wi[i], rt = i;
        for (int u = 1; u <= n && !valid[stat]; u++)
            valid[stat] |= (deg[u] & 1) || ((stat & (1 << (u - 1))) && (deg[u] == 0 || find(u) != find(rt)));
        valid[stat] &= cnt[stat] != 1;
        wpow[stat] = fpow(weights[stat], p), winv[stat] = fpow(wpow[stat], mod - 2);
        if (valid[stat])
            F[cnt[stat]][stat] = wpow[stat];
    }
    // printf("%.3lf\n", 1.0 * clock() / CLOCKS_PER_SEC);
    poly_siz = 1 << n;
    H[0][0] = 1, fwt_or(H[0], 1);
    for (int i = 1; i <= n; i++)
    {
        // printf("FWT start %.3lf\n", 1.0 * clock() / CLOCKS_PER_SEC);
        fwt_or(F[i], 1);
        // printf("FWT end %.3lf\n", 1.0 * clock() / CLOCKS_PER_SEC);
        for (int j = 0; j < i; j++)
            for (int k = 0; k < poly_siz; k++)
                tmp[k] = (0LL + tmp[k] + 1LL * F[i - j][k] * H[j][k] % mod) % mod;
        fwt_or(tmp, -1);
        for (int j = 0; j < poly_siz; j++)
            H[i][j] = 1LL * tmp[j] * winv[j] % mod, tmp[j] = 0;
        if (i != n)
            fwt_or(H[i], 1);
    }
    printf("%d\n", H[n][(1 << n) - 1]);
    // printf("%.3lf\n", 1.0 * clock() / CLOCKS_PER_SEC);
    return 0;
}