// P3140.cpp
#include <bits/stdc++.h>
#define ll long long

using namespace std;

const int MAX_N = 1005, MAX_K = 8;

ll dp[MAX_N][MAX_K], ri[MAX_N], doors, n;

int main()
{
    scanf("%lld%lld", &n, &doors);
    for (int i = 0; i < n; i++)
        scanf("%lld", &ri[i]);
    ll ans = 0x3f3f3f3f3f3f3f3f;
    for (int i = 0; i < n; i++)
    {
        memset(dp, 0x3f, sizeof(dp));
        dp[n][0] = 0;
        for (int k = 1; k <= doors; k++)
        {
            for (int j = 0; j < n; j++)
            {
                ll acc = 0;
                for (int x = j + 1; x <= n; x++)
                {
                    acc += (x - j - 1) * ri[x - 1];
                    dp[j][k] = min(dp[j][k], dp[x][k - 1] + acc);
                }
            }
        }
        ans = min(ans, dp[0][doors]);
        rotate(ri, ri + 1, ri + n);
    }
    printf("%lld", ans);
    return 0;
}