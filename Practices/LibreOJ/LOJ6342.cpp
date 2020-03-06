// LOJ6342.cpp
#include <bits/stdc++.h>

using namespace std;

const int MAX_N = 1e7 + 1, mod = 1e9 + 7;

int n, inv[MAX_N];

int main()
{
    scanf("%d", &n), inv[1] = 1;
    for (int i = 2; i <= n; i++)
        inv[i] = (mod - 1LL * (mod / i) * inv[mod % i] % mod) % mod;
    int sum = 0, dp = 0;
    for (int i = n - 1; i >= 1; i--)
        dp = 1LL * (sum + n - i + 1) * inv[n - i] % mod, sum = (0LL + sum + dp) % mod;
    printf("%d\n", dp);
    return 0;
}