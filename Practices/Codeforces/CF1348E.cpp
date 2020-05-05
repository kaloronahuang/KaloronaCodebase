// CF1348E.cpp
#include <bits/stdc++.h>

using namespace std;

const int MAX_N = 550;

typedef long long ll;

int n, k, ai[MAX_N], bi[MAX_N];
ll pre_a[MAX_N], pre_b[MAX_N];
bool dp[MAX_N][MAX_N];

int main()
{
    scanf("%d%d", &n, &k);
    for (int i = 1; i <= n; i++)
        scanf("%d%d", &ai[i], &bi[i]), pre_a[i] = ai[i] + pre_a[i - 1], pre_b[i] = bi[i] + pre_b[i - 1];
    dp[0][0] = true;
    for (int i = 1; i <= n; i++)
        for (int rema = 0; rema < k; rema++)
        {
            dp[i][rema] |= dp[i - 1][(rema - (ai[i] % k) + k) % k];
            for (int delta = 0; delta < min(k, ai[i] + 1); delta++)
                if ((ai[i] - delta) % k + bi[i] >= k)
                    dp[i][rema] |= dp[i - 1][(rema + k - delta) % k];
        }
    ll ans = 0;
    for (int i = k - 1; i >= 0; i--)
        if (dp[n][i])
            ans = max(ans, (pre_a[n] + pre_b[n] - i) / k);
    printf("%lld\n", ans);
    return 0;
}