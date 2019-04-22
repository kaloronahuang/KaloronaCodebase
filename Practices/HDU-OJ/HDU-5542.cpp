// HDU-5542.cpp
#include <bits/stdc++.h>
#define ll long long
using namespace std;

const int MAX_N = 1e3 + 2000, mod = 1000000007;
int tree[MAX_N][MAX_N], n, m, arr[MAX_N], T;
ll dp[MAX_N][MAX_N];
vector<int> mapping;

int lowbit(int x) { return x & (-x); }

void update(int x, int d, int id)
{
    while (x <= n + 1)
        (tree[id][x] += d) %= mod, x += lowbit(x);
}

ll query(int x, int id)
{
    ll ans = 0;
    while (x)
        (ans += tree[id][x]) %= mod, x -= lowbit(x);
    return ans;
}

int main()
{
    scanf("%d", &T);
    for (int gpid = 1; gpid <= T; gpid++)
    {
        memset(tree, 0, sizeof(tree));
        mapping.clear();
        scanf("%d%d", &n, &m);
        for (int i = 1; i <= n; i++)
            scanf("%d", &arr[i]), mapping.push_back(arr[i]);
        mapping.push_back(0);
        sort(mapping.begin(), mapping.end());
        mapping.erase(unique(mapping.begin(), mapping.end()), mapping.end());
        for (int i = 1; i <= n; i++)
            arr[i] = lower_bound(mapping.begin(), mapping.end(), arr[i]) - mapping.begin() + 1;
        dp[0][0] = 1;
        for (int i = 1; i <= m; i++)
        {
            update(1, dp[i - 1][0], i);
            for (int j = 1; j <= n; j++)
                dp[i][j] = query(arr[j] - 1, i), update(arr[j], dp[i - 1][j], i);
        }

        ll ans = 0;
        for (int i = 1; i <= n; i++)
            ans = (ans + dp[m][i]) % mod;
        printf("Case #%d: %lld\n", gpid, ans);
    }
    return 0;
}