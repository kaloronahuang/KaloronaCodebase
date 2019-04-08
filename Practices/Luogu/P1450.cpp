// P1450.cpp
#include <bits/stdc++.h>
#define ll long long
using namespace std;
const int MAX_N = 101000;
int ci[5], tot, di[5], si;
ll dp[101000];
int main()
{
    for (int i = 0; i < 4; i++)
        scanf("%d", &ci[i]);
    dp[0] = 1;
    for (int i = 0; i < 4; i++)
        for (int j = ci[i]; j < MAX_N; j++)
            dp[j] += dp[j - ci[i]];
    scanf("%d", &tot);
    while (tot--)
    {
        for (int j = 0; j < 4; j++)
            scanf("%d", &di[j]);
        scanf("%d", &si);
        ll ans = 0;
        for (int i = 0; i < 16; i++)
        {
            ll C = si, T = 0;
            for (int j = 0; j < 4; j++)
                if ((i >> j) & 1)
                    C -= (di[j] + 1) * ci[j], T ^= 1;
            if (C < 0)
                continue;
            ans += (T ? -1 : 1) * dp[C];
        }
        printf("%lld\n", ans);
    }
    return 0;
}