// BZ4361.cpp
#include <bits/stdc++.h>
#define ll long long
using namespace std;
const ll MAX_N = 2010, mod = 1e9 + 7;
ll f[MAX_N][MAX_N], g[MAX_N], arr[MAX_N], n, tree[MAX_N][MAX_N], level[MAX_N];
vector<ll> vec;

ll lowbit(ll x) { return x & (-x); }

ll query(ll id, ll x)
{
    ll ans = 0;
    while (x)
        ans = (ans + tree[id][x]) % mod, x -= lowbit(x);
    return ans;
}

void add(ll id, ll x, ll d)
{
    while (x <= n)
        tree[id][x] = (tree[id][x] + d) % mod, x += lowbit(x);
}

int main()
{
    scanf("%lld", &n);
    for (ll i = 1; i <= n; i++)
        scanf("%lld", &arr[i]), vec.push_back(arr[i]);
    level[0] = 1;
    for (ll i = 1; i < MAX_N; i++)
        level[i] = level[i - 1] * i % mod;

    sort(vec.begin(), vec.end()), vec.erase(unique(vec.begin(), vec.end()), vec.end());
    for (ll i = 1; i <= n; i++)
        arr[i] = lower_bound(vec.begin(), vec.end(), arr[i]) - vec.begin() + 1;

    add(0, 1, 1);
    for (ll i = 1; i <= n; i++)
        for (ll j = i; j >= 1; j--)
        {
            f[i][j] = (f[i][j] + query(j - 1, arr[i])) % mod;
            add(j, arr[i], f[i][j]);
        }
    for (ll i = 1; i <= n; i++)
        for (ll j = i; j <= n; j++)
            g[i] = (g[i] + f[j][i]) % mod;
    ll ans = 0;
    for (ll i = 1; i <= n; i++)
        ans = (ans + g[i] * level[n - i] % mod - g[i + 1] * level[n - i - 1] % mod * (i + 1) % mod + mod) % mod;
    printf("%lld", ans);
    return 0;
}