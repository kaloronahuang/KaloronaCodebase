// cowmbat.cpp
#include <bits/stdc++.h>

using namespace std;

const int MAX_N = 1e5 + 200;

typedef long long ll;

int n, m, k;
ll pre[MAX_N][26], dp[MAX_N][26], mp[30][30], min_dp[MAX_N];
char str[MAX_N];

void fileIO(string src)
{
    freopen((src + ".in").c_str(), "r", stdin);
    freopen((src + ".out").c_str(), "w", stdout);
}

int main()
{
    // fileIO("cowmbat");
    scanf("%d%d%d%s", &n, &m, &k, str + 1);
    for (int i = 0; i < m; i++)
        for (int j = 0; j < m; j++)
            scanf("%lld", &mp[i][j]);
    for (int k = 0; k < m; k++)
        for (int i = 0; i < m; i++)
            for (int j = 0; j < m; j++)
                mp[i][j] = min(mp[i][j], mp[i][k] + mp[k][j]);
    for (int i = 1; i <= n; i++)
        for (int j = 0; j < m; j++)
            pre[i][j] = pre[i - 1][j] + mp[str[i] - 'a'][j];
    for (int i = 1; i < k; i++)
        for (int j = 0; j < m; j++)
            dp[i][j] = 0x3f3f3f3f3f3f3f3f;
    for (int i = k; i <= n; i++)
    {
        ll min_val = 0x3f3f3f3f3f3f3f3f;
        for (int j = 0; j < m; j++)
            dp[i][j] = 0x3f3f3f3f3f3f3f3f, min_val = min(min_val, dp[i - k][j]);
        for (int j = 0; j < m; j++)
            dp[i][j] = min(dp[i - 1][j] + mp[str[i] - 'a'][j], min_val + pre[i][j] - pre[i - k][j]);
    }
    printf("%lld\n", *min_element(dp[n], dp[n] + m));
    return 0;
}