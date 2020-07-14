// CF1106E.cpp
#include <bits/stdc++.h>

using namespace std;

const int MAX_N = 1e5 + 200, MAX_M = 220;

typedef long long ll;
typedef pair<int, int> pii;

int n, m, k;
ll dp[2][MAX_N];
vector<pii> tags[2][MAX_N];
map<pii, int> mcnt;
pii mframe[MAX_N];

int main()
{
    scanf("%d%d%d", &n, &m, &k);
    for (int i = 1, s, t, d, w; i <= k; i++)
    {
        scanf("%d%d%d%d", &s, &t, &d, &w);
        tags[0][s].push_back(make_pair(w, d));
        tags[1][t + 1].push_back(make_pair(w, d));
    }
    for (int i = 1; i <= n; i++)
    {
        for (pii u : tags[0][i])
            mcnt[u]++;
        for (pii u : tags[1][i])
            if (--mcnt[u] == 0)
                mcnt.erase(u);
        if (mcnt.empty())
            mframe[i] = make_pair(0, i);
        else
            mframe[i] = mcnt.rbegin()->first;
    }
    memset(dp[0], 0x3f, sizeof(dp[0])), dp[0][1] = 0;
    int b = 0;
    ll ans = 0x7f7f7f7f7f7f7f7f;
    for (int i = 0; i <= m; i++, b ^= 1)
    {
        memset(dp[!b], 0x3f, sizeof(dp[!b])), dp[!b][1] = 0;
        for (int j = 1; j <= n; j++)
        {
            dp[!b][j + 1] = min(dp[!b][j + 1], dp[b][j]);
            dp[b][mframe[j].second + 1] = min(dp[b][mframe[j].second + 1], dp[b][j] + mframe[j].first);
        }
        ans = min(ans, dp[b][n + 1]);
    }
    printf("%lld\n", ans);
    return 0;
}