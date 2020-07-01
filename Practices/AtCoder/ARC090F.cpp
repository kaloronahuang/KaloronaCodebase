// ARC090F.cpp
#include <bits/stdc++.h>

using namespace std;

const int MAX_N = 5e7 + 200, mod = 1e9 + 7;

int n, f[MAX_N];

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

int main()
{
    scanf("%d", &n);
    for (int i = 1; i < MAX_N; i++)
        f[i] = f[i / 10] + 1;
    int ans = 0;
    for (int i = 1, j = 1, sum = 0; i < 1e7; i++)
    {
        while (sum < n)
            sum += f[j++];
        if (sum == n)
            ans++;
        sum -= f[i];
    }
    for (int i = 1; i <= n / 8; i++)
    {
        if (n % i == 0)
            // y == 0, t = n / i;
            ans = (0LL + ans + (0LL + fpow(10, n / i) + mod - (fpow(10, (n / i) - 1) + i - 1) % mod) % mod) % mod;
        else
            ans = (0LL + ans + 1) % mod;
    }
    printf("%d\n", ans);
    return 0;
}