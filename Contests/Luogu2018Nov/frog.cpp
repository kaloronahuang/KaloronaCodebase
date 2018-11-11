// frog.cpp
#include <iostream>
#include <algorithm>
using namespace std;

const int maxn = 320;
#define ll long long
ll hi[maxn], vis[maxn];
ll n;
ll ans = 0;

ll qpow2(ll base)
{
    return base * base;
}

void dfs(ll times, ll prev, ll u)
{
    if (times == n)
    {
        ans = max(ans, prev);
        return;
    }
    vis[u] = true;
    if (u > 0)
        for (int i = 1; i < u; i++)
            if (!vis[i])
                dfs(times + 1, prev + qpow2(hi[u] - hi[i]), i);
    if (u < n)
        for (int i = u + 1; i <= n; i++)
            if (!vis[i])
                dfs(times + 1, prev + qpow2(hi[i] - hi[u]), i);
    vis[u] = true;
}

int main()
{
    cin >> n;
    hi[0] = 0;
    for (int i = 1; i <= n; i++)
        cin >> hi[i];
    dfs(0, 0, 0);
    cout << ans;
    return 0;
}