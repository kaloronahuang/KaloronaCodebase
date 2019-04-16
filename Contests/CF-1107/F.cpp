// F.cpp
#include <bits/stdc++.h>
typedef long long ll;
using namespace std;

const int MAX_N = 550;
struct credit
{
    ll a, b, k;
    bool operator<(const credit &crd) const { return b > crd.b; }
} credits[MAX_N];
int n;
ll dp[MAX_N][MAX_N];

int main()
{
    scanf("%d", &n);
    for (int i = 1; i <= n; i++)
        scanf("%lld%lld%lld", &credits[i].a, &credits[i].b, &credits[i].k);
    sort(credits + 1, credits + 1 + n);
    for (int i = 1; i <= n; i++)
        dp[0][i] = -1e9;
    for (int i = 1; i <= n; i++)
    {
        ll curt = max(0LL, credits[i].a - credits[i].b * credits[i].k);
        dp[i][0] = dp[i - 1][0] + curt;
        for (int j = 1; j <= i; j++)
            dp[i][j] = max(dp[i - 1][j] + curt, dp[i - 1][j - 1] + credits[i].a - credits[i].b * (j - 1));
    }
    ll ans = 0;
    for (int i = 0; i <= n; i++)
        ans = max(ans, dp[n][i]);
    printf("%lld", ans);
    return 0;
}