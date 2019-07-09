// P4781.cpp
#include <bits/stdc++.h>
#define ll long long

using namespace std;

const int MAX_N = 2020, mod = 998244353;

int n, k, xi[MAX_N], yi[MAX_N], numerators[MAX_N], denominators[MAX_N];

int quick_pow(int bas, int tim)
{
    int ans = 1;
    bas %= mod;
    while (tim)
    {
        if (tim & 1)
            ans = 1LL * ans * bas % mod;
        bas = 1LL * bas * bas % mod;
        tim >>= 1;
    }
    return ans;
}

ll upd(ll num)
{
    while (num < 0)
        num += mod;
    return num % mod;
}

int main()
{
    scanf("%d%d", &n, &k);
    for (int i = 1; i <= n; i++)
        scanf("%d%d", &xi[i], &yi[i]), numerators[i] = yi[i], denominators[i] = 1;
    for (int i = 1; i <= n; i++)
    {
        for (int j = 1; j <= n; j++)
            if (i != j)
            {
                numerators[i] = 1LL * numerators[i] * upd(k - xi[j]) % mod;
                denominators[i] = 1LL * denominators[i] * upd((xi[i] - xi[j])) % mod;
            }
    }
    int ans = 0;
    for (int i = 1; i <= n; i++)
        ans = (1LL * ans + 1LL * numerators[i] * quick_pow(denominators[i], mod - 2) % mod) % mod;
    printf("%d", ans);
    return 0;
}