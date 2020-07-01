// P6130.cpp
#include <bits/stdc++.h>

using namespace std;

const int MAX_N = 1e7 + 200, mod = 998244353;

int inv[MAX_N], pre[MAX_N], T, ans;

int main()
{
    inv[0] = inv[1] = 1;
    for (int i = 2; i < MAX_N; i++)
        inv[i] = 1LL * (mod - mod / i) * inv[mod % i] % mod;
    pre[0] = 1;
    for (int i = 1; i < MAX_N; i++)
        pre[i] = (0LL + pre[i - 1] + inv[i]) % mod;
    scanf("%d", &T);
    while (T--)
    {
        int n, k;
        scanf("%d%d", &n, &k);
        ans ^= 1LL * inv[n] * ((0LL + pre[n] + mod - pre[n - k]) % mod) % mod;
    }
    printf("%d\n", ans);
    return 0;
}