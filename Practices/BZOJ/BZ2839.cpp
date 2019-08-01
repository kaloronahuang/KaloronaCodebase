// BZ2839.cpp
#include <bits/stdc++.h>
#define ll long long
using namespace std;

const int mod = 1000000007, MAX_N = 1000100;

int n, k, level[MAX_N], level_inv[MAX_N], bin[MAX_N];

int quick_pow(int bas, int tim)
{
    int ans = 1;
    bas %= mod;
    while (tim != 0)
    {
        if (tim & 1)
            ans = 1LL * ans * bas % mod;
        bas = 1LL * bas * bas % mod;
        tim >>= 1;
    }
    return ans;
}

int comb(int a, int b) { return 1LL * level[a] * level_inv[a - b] % mod * level_inv[b] % mod; }

int main()
{
    scanf("%d%d", &n, &k);
    level[1] = level[0] = level_inv[1] = level_inv[0] = 1;
    bin[1] = 2, bin[0] = 1;
    for (int i = 2; i <= n; i++)
        level[i] = 1LL * level[i - 1] * i % mod, bin[i] = (bin[i - 1] << 1) % (mod - 1);
    level_inv[n] = quick_pow(level[n], mod - 2);
    for (int i = n - 1; i >= 2; i--)
        level_inv[i] = 1LL * level_inv[i + 1] * (i + 1) % mod;

    int ans = 0, opt = 1;
    for (int i = 0; i <= n - k; i++)
        ans = (1LL * ans + 1LL * opt * comb(n - k, i) % mod * quick_pow(2, bin[n - k - i]) % mod + mod) % mod, opt = -opt;
    printf("%d", 1LL * ans * comb(n, k) % mod);
    return 0;
} // BZ2839.cpp