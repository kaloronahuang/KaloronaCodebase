// B.cpp
#include <bits/stdc++.h>
#define ll long long

using namespace std;

const int MAX_N = 330;

ll gcd(ll a, ll b) { return b == 0 ? a : gcd(b, a % b); }

ll dp[MAX_N][MAX_N][2], n, prefix[MAX_N];
bool conn[MAX_N][MAX_N];
struct node
{
    ll key, val;
    bool operator<(const node &nd) const { return key < nd.key; }
} nodes[MAX_N];

ll dfs(int l, int r, int opt)
{
    if (l > r)
        return 0;
    if (dp[l][r][opt] != 0)
        return dp[l][r][opt];
    ll ans = 0;
    int root = (opt == 1) ? r + 1 : l - 1;
    bool flag = false;
    if (root > n)
        return dp[l][r][opt] = -1;
    for (int i = l; i <= r; i++)
    {
        if (conn[i][root] == false)
            continue;
        ll lft = dfs(l, i - 1, 1), rig = dfs(i + 1, r, 0);
        if (lft == -1 || rig == -1)
            continue;
        ans = max(ans, lft + rig);
        flag = true;
    }
    if (flag)
        return dp[l][r][opt] = ans + prefix[r] - prefix[l - 1];
    else
        return dp[l][r][opt] = -1;
}

int main()
{
    scanf("%lld", &n);
    for (int i = 1; i <= n; i++)
        scanf("%lld%lld", &nodes[i].key, &nodes[i].val);
    sort(nodes + 1, nodes + 1 + n);
    for (int i = 1; i <= n; i++)
        prefix[i] = prefix[i - 1] + nodes[i].val;
    for (int i = 1; i <= n; i++)
    {
        conn[i][0] = conn[0][i] = true;
        for (int j = i + 1; j <= n; j++)
            if (gcd(nodes[i].key, nodes[j].key) != 1)
                conn[i][j] = conn[j][i] = true;
    }
    printf("%lld", dfs(1, n, 0));
    return 0;
}