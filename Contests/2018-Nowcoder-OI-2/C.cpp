// C.cpp
#include <bits/stdc++.h>
typedef long long ll;

using namespace std;

ll predigits[20], dp[20][4], T, digits[20];

ll solve(ll pos)
{
    if (pos < 1000)
        return 0;
    int tot = 0, x = 0;
    for (; pos; pos /= 10)
        digits[tot++] = pos % 10;
    reverse(digits, digits + tot);
    memset(dp, 0, sizeof(dp));
    dp[1][0] = digits[0] - 1;
    for (int i = 1; i < tot; i++)
    {
        dp[i + 1][0] = dp[i][0] * 9, dp[i + 1][1] = dp[i][0] + dp[i][1] * 9;
        dp[i + 1][2] = dp[i][1] + dp[i][2] * 9, dp[i + 1][3] = dp[i][2] + dp[i][3] * 10;
        dp[i + 1][x] += digits[i] - 1;
        dp[i + 1][x + ((x < 2 && digits[i]) || (x == 2 && digits[i] > 7))]++;
        if (((x < 2 && !digits[i]) || (x == 2 && digits[i] == 7)))
            x++;
    }
    return predigits[tot - 1] + dp[tot][3];
}

int main()
{
    for (ll i = 0, val = 1; i <= 18; i++, val *= 10)
        predigits[i] = solve(val - 1);
    ll ans = 0;
    scanf("%lld", &T);
    while (T--)
    {
        ll lft, rig;
        scanf("%lld%lld", &lft, &rig);
        ans ^= (solve(rig + 1) - solve(lft));
    }
    printf("%lld", ans);
    return 0;
}