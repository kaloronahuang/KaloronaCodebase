// CF1034C.cpp
#include <bits/stdc++.h>

using namespace std;

const int MAX_N = 1e6 + 200, mod = 1e9 + 7;
typedef long long ll;

int n, fa[MAX_N], dp[MAX_N];
ll sum[MAX_N], cnt[MAX_N];

ll gcd(ll a, ll b) { return b == 0 ? a : gcd(b, a % b); }

int main()
{
    scanf("%d", &n);
    for (int i = 1; i <= n; i++)
        scanf("%lld", &sum[i]);
    for (int i = 2; i <= n; i++)
        scanf("%d", &fa[i]);
    for (int i = n; i >= 1; i--)
        if (fa[i])
            sum[fa[i]] += sum[i];
    for (int i = n; i >= 1; i--)
    {
        sum[i] = sum[1] / gcd(sum[1], sum[i]);
        if (sum[i] <= n)
            cnt[sum[i]]++;
    }
    for (int i = n; i >= 1; i--)
        for (int j = (i << 1); j <= n; j += i)
            cnt[j] += cnt[i];
    dp[1] = 1;
    int ans = 0;
    for (int i = 1; i <= n; i++)
        if (cnt[i] == i)
        {
            ans = (0LL + ans + dp[i]) % mod;
            for (int j = i << 1; j <= n; j += i)
                dp[j] = (0LL + dp[j] + dp[i]) % mod;
        }
    printf("%d\n", ans);
    return 0;
}