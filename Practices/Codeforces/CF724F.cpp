// CF724F.cpp
#include <bits/stdc++.h>

using namespace std;

const int MAX_N = 1010, MAX_D = 12;

int n, d, mod, inv[MAX_D], dp[MAX_N][MAX_N][MAX_D];
bool vis[MAX_N][MAX_N][MAX_D];

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

int solve(int scale, int max_part, int cdeg)
{
    if (vis[scale][max_part][cdeg])
        return dp[scale][max_part][cdeg];
    vis[scale][max_part][cdeg] = true;
    int &ret = dp[scale][max_part][cdeg];
    if (scale == 1)
        return ret = (cdeg == 0);
    if (cdeg == 0 || max_part == 0 || cdeg >= scale)
        return ret = 0;
    if (max_part == 1)
        return ret = (scale == cdeg + 1);
    ret = solve(scale, max_part - 1, cdeg);
    int part = solve(max_part, max_part, d - 1);
    if (part == 0)
        return ret;
    int binomial = 1;
    for (int i = 1; i <= cdeg && 1LL * i * max_part <= scale - 1; i++)
    {
        binomial = 1LL * binomial * inv[i] % mod * (part + i - 1) % mod;
        ret = (0LL + ret + 1LL * binomial * solve(scale - 1LL * i * max_part, max_part - 1, cdeg - i) % mod) % mod;
    }
    return ret;
}

int main()
{
    scanf("%d%d%d", &n, &d, &mod);
    for (int i = 1; i <= d; i++)
        inv[i] = fpow(i, mod - 2);
    if (n <= 2)
        puts("1"), exit(0);
    if (n & 1)
        printf("%d\n", solve(n, n >> 1, d)), exit(0);
    int part = solve(n >> 1, (n >> 1) - 1, d - 1);
    part = 1LL * part * (part + 1) % mod * inv[2] % mod;
    // printf("%d ", part);
    part = (0LL + part + solve(n, (n >> 1) - 1, d)) % mod;
    printf("%d\n", part);
    return 0;
}