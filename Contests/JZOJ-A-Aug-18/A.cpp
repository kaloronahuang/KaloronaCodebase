// A.cpp
#include <bits/stdc++.h>
#define ll long long

using namespace std;

const int MAX_N = 1e6 + 200;

ll n, m;
int volumes[MAX_N], weights[MAX_N], wgt[110];
int upper_tot, max_rate = 0, dp[2][MAX_N];
long double rate[110];

int main()
{
    scanf("%lld%lld", &n, &m);
    for (int i = 1; i <= n; i++)
    {
        scanf("%d%d", &volumes[i], &weights[i]);
        wgt[volumes[i]] = max(wgt[volumes[i]], weights[i]);
        upper_tot = max(upper_tot, volumes[i]);
    }
    for (int i = 1; i <= upper_tot; i++)
    {
        rate[i] = (long double)wgt[i] / i;
        if (rate[i] > rate[max_rate])
            max_rate = i;
    }
    ll minus_part = m / max_rate - 100, answer = 0;
    if (minus_part > 0)
        m -= minus_part * max_rate, answer += wgt[max_rate] * minus_part;
    for (int i = 1; i <= upper_tot; i++)
        for (int j = 0; j <= m; j++)
        {
            dp[i & 1][j] = dp[(i - 1) & 1][j];
            if (j >= i)
                dp[i & 1][j] = max(dp[i & 1][j], dp[i & 1][j - i] + wgt[i]);
        }
    printf("%lld", dp[upper_tot & 1][m] + answer);
    return 0;
}