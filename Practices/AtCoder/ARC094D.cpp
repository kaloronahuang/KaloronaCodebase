// ARC094D.cpp
#include <bits/stdc++.h>

using namespace std;

const int MAX_N = 2e5 + 200, mod = 998244353;

int n, dp[MAX_N][3][3][2], str[MAX_N];
char org[MAX_N];

int main()
{
    scanf("%s", org + 1), n = strlen(org + 1);
    int oddity = 0, tot[3] = {0, 0, 0};
    bool flag = true;
    for (int i = 1; i <= n; i++)
        str[i] = org[i] - 'a', oddity = (oddity + str[i]) % 3, tot[str[i]]++;
    for (int i = 1; i < n; i++)
        flag &= (str[i] != str[i + 1]);
    if (tot[0] == n || tot[1] == n || tot[2] == n)
        puts("1"), exit(0);
    if (n <= 3)
    {
        map<string, bool> mp;
        string org_str = org + 1;
        mp[org_str] = true;
        int delta = 0;
        do
        {
            delta = 0;
            for (auto x : mp)
                for (int i = 0; i < n - 1; i++)
                    if (x.first[i] != x.first[i + 1])
                    {
                        string nxt = x.first;
                        nxt[i] = nxt[i + 1] = ('a' ^ 'b' ^ 'c') ^ (x.first[i] ^ x.first[i + 1]);
                        if (mp[nxt] == false)
                            mp[nxt] = true, delta++;
                    }
        } while (delta);
        printf("%lld\n", 1LL * mp.size());
    }
    else
    {
        int ans = (flag == true);
        dp[1][0][0][0] = dp[1][1][1][0] = dp[1][2][2][0] = 1;
        for (int i = 2; i <= n; i++)
            for (int sum = 0; sum < 3; sum++)
                for (int pre = 0; pre < 3; pre++)
                    for (int curt = 0; curt < 3; curt++)
                        if (pre == curt)
                            dp[i][(sum + curt) % 3][curt][1] = (0LL + dp[i][(sum + curt) % 3][curt][1] + dp[i - 1][sum][pre][0] + dp[i - 1][sum][pre][1]) % mod;
                        else
                        {
                            dp[i][(sum + curt) % 3][curt][0] = (0LL + dp[i][(sum + curt) % 3][curt][0] + dp[i - 1][sum][pre][0]) % mod;
                            dp[i][(sum + curt) % 3][curt][1] = (0LL + dp[i][(sum + curt) % 3][curt][1] + dp[i - 1][sum][pre][1]) % mod;
                        }
        for (int i = 0; i < 3; i++)
            ans = (0LL + ans + dp[n][oddity][i][1]) % mod;
        printf("%d\n", ans);
    }

    return 0;
}