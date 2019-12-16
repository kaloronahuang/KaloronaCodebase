// CF1009E.cpp
#include <bits/stdc++.h>

using namespace std;

const int MAX_N = 1e6 + 200, mod = 998244353;

int n;

int main()
{
    scanf("%d", &n);
    for (int i = 1, ai, dp_all = 0, hi = 0, gi = 0; i <= n; i++)
    {
        scanf("%d", &ai);
        hi = (1LL * (hi << 1) % mod + 1LL * ai) % mod;
        dp_all = (1LL * gi + 1LL * hi) % mod;
        gi = (1LL * dp_all + 1LL * gi) % mod;
        if (i == n)
            printf("%d\n", dp_all);
    }
    return 0;
}