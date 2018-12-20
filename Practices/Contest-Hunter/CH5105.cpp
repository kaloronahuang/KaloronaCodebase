// CH5105.cpp
#include <iostream>
#include <cstdio>
#include <algorithm>
#include <cstring>
#define ll long long
using namespace std;
const int MX_N = 35, MX_M = 5100;
const ll INF = 0x3f3f3f3f3f3f3f3f;
ll n, m, g[MX_N], dp[MX_N][MX_M], c[MX_N], presum[MX_N];
ll lastPersonNum[MX_N][MX_M], cookieSum[MX_N][MX_M], ans[MX_N];
bool compare(const ll &a, const ll &b) { return g[a] > g[b]; }
void process(int num, int bis)
{
    if (num == 0)
        return;
    process(lastPersonNum[num][bis], cookieSum[num][bis]);
    if (lastPersonNum[num][bis] == num)
        for (int i = 1; i <= num; i++)
            ans[c[i]]++;
    else
        for (int i = lastPersonNum[num][bis] + 1; i <= num; i++)
            ans[c[i]] = 1;
}
int main()
{
    scanf("%lld%lld", &n, &m);
    for (int i = 1; i <= n; i++)
        scanf("%lld", &g[i]), c[i] = i;
    sort(c + 1, c + n + 1, compare);
    for (int i = 1; i <= n; i++)
        presum[i] = presum[i - 1] + g[c[i]];
    memset(dp, 0x3f, sizeof(dp));
    dp[0][0] = 0;
    for (int i = 1; i <= n; i++)
        for (int bis = i; bis <= m; bis++)
        {
            dp[i][bis] = dp[i][bis - i];
            lastPersonNum[i][bis] = i;
            cookieSum[i][bis] = bis - i;
            for (int k = 0; k < i; k++)
            {
                ll val = dp[k][bis - (i - k)] + k * (presum[i] - presum[k]);
                if (dp[i][bis] > val)
                    dp[i][bis] = val, lastPersonNum[i][bis] = k, cookieSum[i][bis] = bis - (i - k);
            }
        }
    printf("%lld\n", dp[n][m]);
    process(n, m);
    for (int i = 1; i <= n; i++)
        printf("%lld ", ans[i]);
    return 0;
}