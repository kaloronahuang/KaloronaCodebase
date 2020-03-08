// CF1322C.cpp
#include <bits/stdc++.h>

using namespace std;

const int MAX_N = 1e6 + 200;

typedef long long ll;

int T, n, m;
ll ci[MAX_N];
vector<ll> G[MAX_N];
map<vector<ll>, ll> mp;

ll gcd(ll a, ll b) { return a == 0 ? b : (b == 0 ? a : gcd(b, a % b)); }

int main()
{
    scanf("%d", &T);
    while (T--)
    {
        scanf("%d%d", &n, &m), mp.clear();
        for (int i = 1; i <= n; i++)
            scanf("%lld", &ci[i]), G[i].clear();
        for (int i = 1, u, v; i <= m; i++)
            scanf("%d%d", &u, &v), G[v].push_back(u);
        for (int i = 1; i <= n; i++)
            if (!G[i].empty())
                sort(G[i].begin(), G[i].end()), mp[G[i]] += ci[i];
        ll ans = 0;
        for (auto &x : mp)
            ans = gcd(ans, x.second);
        printf("%lld\n", ans);
    }
    return 0;
}