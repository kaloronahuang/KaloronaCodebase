// P2577.cpp
#include <iostream>
#include <cstdio>
#include <algorithm>
#include <cstring>
#define ll long long
using namespace std;
const int MX_N = 220;
struct person
{
    ll a, b;
    bool operator<(const person &ps) const
    {
        return b > ps.b;
    }
} persons[MX_N];
ll sum[MX_N], n, dp[MX_N][MX_N * MX_N];
int main()
{
    scanf("%lld", &n);
    for (int i = 1; i <= n; i++)
        scanf("%lld%lld", &persons[i].a, &persons[i].b);
    sort(persons + 1, persons + 1 + n);
    for (int i = 1; i <= n; i++)
        sum[i] = sum[i - 1] + persons[i].a;
    memset(dp, 0x3f, sizeof(dp));
    dp[0][0] = 0;
    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= sum[i]; j++)
        {
            if (j >= persons[i].a)
                dp[i][j] = min(dp[i][j], max(dp[i - 1][j - persons[i].a], (ll)(j + persons[i].b)));
            dp[i][j] = min(dp[i][j], max(dp[i - 1][j], sum[i] - j + persons[i].b));
        }
    ll ans = 0x7fffffff;
    for (int i = 0; i <= sum[n]; i++)
        ans = min(ans, dp[n][i]);
    printf("%lld", ans);
    return 0;
}