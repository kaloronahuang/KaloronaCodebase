// CH5702.cpp
#include <bits/stdc++.h>
#define ll long long
using namespace std;
ll n1, n2, dp[110][32];
string s1, s2;

ll solve()
{
    memset(dp, 0, sizeof(dp));
    for (int i = 0; i < s1.length(); i++)
    {
        int pos = i;
        dp[i][0] = 0;
        for (int j = 0; j < s2.length(); j++)
        {
            int cnt = 0;
            while (s1[pos] != s2[j])
            {
                pos = (pos + 1) % s1.length();
                if (++cnt >= s1.length())
                    return 0;
            }
            pos = (pos + 1) % s1.length();
            dp[i][0] += cnt + 1;
        }
    }
    for (int j = 1; j <= 30; j++)
        for (int i = 0; i < s1.length(); i++)
            dp[i][j] = dp[i][j - 1] + dp[(i + dp[i][j - 1]) % s1.length()][j - 1];
    ll answer = 0;
    for (int i = 0; i < s1.length(); i++)
    {
        ll x = i, ans = 0;
        for (int j = 30; j >= 0; j--)
            if (x + dp[x % s1.length()][j] <= s1.length() * n1)
                x += dp[x % s1.length()][j], ans |= (1 << j);
        answer = max(answer, ans);
    }
    return answer / n2;
}

int main()
{
    while (cin >> s2 >> n2 >> s1 >> n1)
        printf("%lld\n", solve());
    return 0;
}