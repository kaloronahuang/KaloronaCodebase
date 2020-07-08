// HDU-4372.cpp
#include <bits/stdc++.h>

using namespace std;

const int MAX_N = 2020, mod = 1e9 + 7;

int T, binomial[MAX_N][MAX_N], stirling[MAX_N][MAX_N];

int main()
{
    binomial[0][0] = stirling[0][0] = 1;
    for (int i = 1; i < MAX_N; i++)
    {
        binomial[i][0] = 1;
        for (int j = 1; j <= i; j++)
        {
            binomial[i][j] = (0LL + binomial[i - 1][j - 1] + binomial[i - 1][j]) % mod;
            stirling[i][j] = (0LL + stirling[i - 1][j - 1] + 1LL * (i - 1) * stirling[i - 1][j] % mod) % mod;
        }
    }
    scanf("%d", &T);
    while (T--)
    {
        int n, x, y;
        scanf("%d%d%d", &n, &x, &y);
        if (x + y - 2 > n - 1)
            puts("0");
        else
            printf("%lld\n", 1LL * binomial[x - 1 + y - 1][x - 1] * stirling[n - 1][x + y - 2] % mod);
    }
    return 0;
}