// gymnasts.cpp
#include <bits/stdc++.h>

using namespace std;

const int MAX_N = 1e5 + 200, mod = 1e9 + 7;

typedef long long ll;

ll n, acc, ans;
vector<pair<ll, int>> nset;

void fileIO(string src)
{
    freopen((src + ".in").c_str(), "r", stdin);
    freopen((src + ".out").c_str(), "w", stdout);
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

void dfs(int pos, ll gcd, ll phiup, ll phidown)
{
    if (pos == int(nset.size()))
    {
        if (gcd == 1)
            return;
        ans += fpow(2, (n / gcd) % (mod - 1)) * ((1LL * gcd / phidown % mod * phiup % mod) % mod) % mod;
        ans %= mod;
        return;
    }
    dfs(pos + 1, gcd, phiup, phidown);
    phiup = 1LL * phiup * (nset[pos].first - 1) % mod;
    phidown = 1LL * phidown * nset[pos].first;
    for (int i = 1; i <= nset[pos].second; i++)
    {
        gcd *= nset[pos].first;
        dfs(pos + 1, gcd, phiup, phidown);
    }
}

int main()
{
    // fileIO("gymnasts");
    scanf("%lld", &n), acc = n;
    for (ll i = 2; 1LL * i * i <= acc; i++)
        if (acc % i == 0)
        {
            int cnt = 0;
            while (acc % i == 0)
                cnt++, acc /= i;
            nset.push_back(make_pair(i, cnt));
        }
    if (acc > 1)
        nset.push_back(make_pair(acc, 1));
    dfs(0, 1, 1, 1);
    printf("%lld\n", (2LL + ans - (n % mod) + mod) % mod);
    return 0;
}