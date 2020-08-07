// wlwl.cpp
#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

const int MAX_N = 1e5 + 200;

int n;
ll mod, ai[MAX_N];
bool vis[220];

void fileIO(string str)
{
    freopen((str + ".in").c_str(), "r", stdin);
    freopen((str + ".out").c_str(), "w", stdout);
}

ll fmul(ll a, ll b)
{
    ll ret = 0;
    while (b)
    {
        if (b & 1)
            ret = (0LL + ret + a) % mod;
        a = (0LL + a + a) % mod;
        b >>= 1;
    }
    return ret;
}

ll ffpow(ll bas, ll tim)
{
    ll ret = 1;
    while (tim)
    {
        if (tim & 1)
            ret = fmul(ret, bas);
        bas = fmul(bas, bas);
        tim >>= 1;
    }
    return ret;
}

ll fpow(ll bas, ll tim)
{
    ll ret = 1;
    while (tim)
    {
        if (tim & 1)
            ret = 1LL * ret * bas % mod;
        bas = 1LL * bas * bas % mod;
        tim >>= 1;
    }
    return ret;
}

ll solve(ll a, ll b)
{
    memset(vis, false, sizeof(vis));
    for (int i = 1; i <= mod; i++)
        vis[fpow(b, i)] = true;
    for (int i = 1; i <= mod; i++)
        if (vis[fpow(a, i)])
            return i;
    return 0;
}

int main()
{
    // fileIO("wlwl");
    scanf("%d%lld", &n, &mod);
    for (int i = 1; i <= n; i++)
        scanf("%lld", &ai[i]);
    if (n <= 200 && mod <= 200)
    {
        ll ret = 0;
        for (int i = 1; i <= n; i++)
            for (int j = 1; j <= n; j++)
                ret = (0LL + ret + fmul(solve(ai[i], ai[j]), solve(ai[j], ai[i]))) % mod;
        printf("%lld\n", ret);
    }
    return 0;
}