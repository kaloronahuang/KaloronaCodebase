// P1864.cpp
#include <bits/stdc++.h>
#define ll long long

using namespace std;

const int MAX_N = 110;

struct node
{
    int val, weight, freq;
    bool operator<(const node &nd) const { return val < nd.val; }
} nodes[MAX_N];

int n, ext;
ll dp[MAX_N][MAX_N][MAX_N], prefix[MAX_N];
vector<int> mp;

int main()
{
    scanf("%d%d", &n, &ext);
    for (int i = 1; i <= n; i++)
        scanf("%d", &nodes[i].val);
    for (int i = 1; i <= n; i++)
        scanf("%d", &nodes[i].weight), mp.push_back(nodes[i].weight);
    sort(mp.begin(), mp.end()), mp.erase(unique(mp.begin(), mp.end()), mp.end());
    for (int i = 1; i <= n; i++)
        nodes[i].weight = lower_bound(mp.begin(), mp.end(), nodes[i].weight) - mp.begin() + 1;
    for (int i = 1; i <= n; i++)
        scanf("%d", &nodes[i].freq);
    sort(nodes + 1, nodes + 1 + n);
    for (int i = 1; i <= n; i++)
        prefix[i] = prefix[i - 1] + nodes[i].freq;
    memset(dp, 0x3f, sizeof(dp));
    for (int k = 1; k <= n; k++)
        for (int i = 1; i <= n + 1; i++)
            dp[i][i - 1][k] = 0;
    for (int len = 1; len <= n; len++)
        for (int i = 1; i + len - 1 <= n; i++)
        {
            int j = i + len - 1;
            // limit
            for (int k = 1; k <= n; k++)
                for (int rt = i; rt <= j; rt++)
                {
                    dp[i][j][k] = min(dp[i][j][k], dp[i][rt - 1][k] + dp[rt + 1][j][k] + prefix[j] - prefix[i - 1] + ext);
                    if (nodes[rt].weight >= k)
                        dp[i][j][k] = min(dp[i][j][k], dp[i][rt - 1][nodes[rt].weight] + dp[rt + 1][j][nodes[rt].weight] + prefix[j] - prefix[i - 1]);
                }
        }
    printf("%lld", dp[1][n][1]);
    return 0;
}