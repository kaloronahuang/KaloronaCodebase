// P5665.cpp
#include <bits/stdc++.h>
#define ll __int128

using namespace std;

const int MAX_N = 3000005;
const ll INF = 0x7fffffffffffffff;

int n, typ;
ll seq[MAX_N], prefix[MAX_N], dp[MAX_N], max_val[MAX_N], opt[MAX_N], x, y, z, bi[MAX_N], m, pi[MAX_N], li[MAX_N], ri[MAX_N];

ll pow2(ll bas) { return bas * bas; }

int main()
{
    scanf("%d%d", &n, &typ);
    if (typ == 0)
        for (int i = 1; i <= n; i++)
            scanf("%lld", &seq[i]), prefix[i] = prefix[i - 1] + seq[i];
    else
    {
        scanf("%lld%lld%lld%lld%lld%lld", &x, &y, &z, &bi[1], &bi[2], &m);
        for (int i = 3; i <= n; i++)
            bi[i] = (x * bi[i - 1] + y * bi[i - 2] + z) % (1LL << 30);
        for (int i = 1; i <= m; i++)
            for (int j = pi[i - 1] + 1; j <= pi[i]; j++)
                seq[j] = (bi[j] % (ri[i] - li[i] + 1)) + li[i], prefix[j] = prefix[j - 1] + seq[j];
    }
    for (int i = 1; i <= n; i++)
    {
        dp[i] = INF;
        for (int j = opt[i - 1]; j < i; j++)
            if (max_val[j] <= (prefix[i] - prefix[j]) && dp[i] > dp[j] + pow2(prefix[i] - prefix[j]))
                dp[i] = dp[j] + pow2(prefix[i] - prefix[j]), opt[i] = j, max_val[i] = prefix[i] - prefix[j];
    }
    printf("%lld", dp[n]);
    return 0;
}