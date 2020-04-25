// CF1285E.cpp
#include <bits/stdc++.h>

using namespace std;

const int MAX_N = 8e5 + 200;

typedef long long ll;

int T, n;
ll diff[MAX_N], dp[MAX_N], li[MAX_N], ri[MAX_N];
vector<int> mp;

int ripe(int x) { return lower_bound(mp.begin(), mp.end(), x) - mp.begin() + 1; }

int main()
{
    scanf("%d", &T);
    while (T--)
    {
        ll ans1 = 0, ans2 = -0x3f3f3f3f;
        scanf("%d", &n);
        for (int i = 1; i <= n; i++)
            scanf("%lld%lld", &li[i], &ri[i]), mp.push_back(li[i]), mp.push_back(ri[i]);
        sort(mp.begin(), mp.end()), mp.erase(unique(mp.begin(), mp.end()), mp.end());
        for (int i = 1; i <= n; i++)
        {
            li[i] = ripe(li[i]) << 1, ri[i] = ripe(ri[i]) << 1;
            diff[li[i]]++, diff[ri[i] + 1]--;
        }
        int upper = mp.size() << 1;
        for (int i = 1; i <= upper + 5; i++)
            diff[i] += diff[i - 1];
        for (int i = 0; i <= upper + 5; i++)
            ans1 += diff[i] && !diff[i + 1];
        for (int i = 0; i <= upper + 4; i++)
            dp[i] += (diff[i] == 1 && diff[i + 1] != 1);
        for (int i = 1; i <= upper + 5; i++)
            dp[i] += (diff[i] == 1 && diff[i - 1] != 1);
        for (int i = 1; i <= upper + 5; i++)
            dp[i] += dp[i - 1];
        for (int i = 1; i <= n; i++)
        {
            ll content = (dp[ri[i]] - dp[li[i] - 1]) >> 1;
            content -= (diff[ri[i]] == 1) + (diff[li[i]] == 1);
            ans2 = max(ans2, content);
        }
        printf("%lld\n", ans1 + ans2);
        for (int i = 0; i <= upper + 5; i++)
            dp[i] = diff[i] = 0;
    }
    return 0;
}