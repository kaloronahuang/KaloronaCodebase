// UOJ246.cpp
#include <bits/stdc++.h>

using namespace std;

const int MAX_N = 2e5 + 200;

typedef long long ll;

int n, m, k, dp[MAX_N], ai[MAX_N], block, last_pos[MAX_N], pos[MAX_N];
ll ans;

int main()
{
    // freopen("ex_routine2.in", "r", stdin);
    scanf("%d%d%d", &n, &m, &k), block = sqrt(m) + 1;
    for (int i = 1; i <= n; i++)
        scanf("%d", &ai[i]), dp[i] = m;
    for (int len = 2; len <= block; len++)
    {
        for (int i = 1; i + len - 1 <= n; i++)
            dp[i] = min({dp[i], dp[i + 1], abs(ai[i] - ai[i + len - 1])});
        if (len >= k)
            for (int i = 1; i + len - 1 <= n; i++)
                ans = max(ans, 1LL * (len - 1) * dp[i]);
    }
    for (int i = 1; i <= n; i++)
    {
        for (int diff = 0, lft = 0; diff <= block; diff++)
        {
            if (ai[i] - diff >= 1)
                pos[diff] = max(pos[diff], last_pos[ai[i] - diff]);
            if (ai[i] + diff <= m)
                pos[diff] = max(pos[diff], last_pos[ai[i] + diff]);
            if (pos[diff] > lft && i - lft >= k)
                ans = max(ans, 1LL * (i - lft - 1) * diff);
            lft = max(lft, pos[diff]);
        }
        last_pos[ai[i]] = i;
    }
    printf("%lld\n", ans);
    return 0;
}