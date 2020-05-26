// P4561.cpp
#include <bits/stdc++.h>

using namespace std;

const int MAX_N = 2e5 + 200, RANGE = 1e7 + 50 + MAX_N, mod = 998244353;

typedef long long ll;

int T, fac[RANGE], n, m, L, R, xi[MAX_N], sum[MAX_N], lft, rig;
vector<int> mp;

int fpow(int bas, int tim)
{
    int ret = 1;
    while (tim)
    {
        if (tim & 1)
            ret = 1LL * ret * bas % mod;
        bas = 1LL * bas * bas % mod;
        tim >>= 1;
    }
    return ret;
}

ll check(ll mid)
{
    ll acc = 1LL * mid * (R - L - (rig - lft));
    if (acc > m)
        return acc;
    for (int i = lft; i <= rig && acc <= m; i++)
        acc += max(0LL + mid - sum[i], 0LL);
    return acc;
}

int main()
{
    for (int i = fac[0] = 1; i < RANGE; i++)
        fac[i] = 1LL * fac[i - 1] * i % mod;
    scanf("%d", &T);
    while (T--)
    {
        for (int i = 1; i <= n; i++)
            sum[i] = 0;
        scanf("%d%d%d%d", &n, &m, &L, &R), mp.clear();
        for (int i = 1; i <= n; i++)
            scanf("%d", &xi[i]), mp.push_back(xi[i]);
        sort(mp.begin(), mp.end()), mp.erase(unique(mp.begin(), mp.end()), mp.end());
        for (int i = 1; i <= n; i++)
            xi[i] = lower_bound(mp.begin(), mp.end(), xi[i]) - mp.begin() + 1;
        lft = lower_bound(mp.begin(), mp.end(), L) - mp.begin() + 1;
        rig = upper_bound(mp.begin(), mp.end(), R) - mp.begin();
        for (int i = 1; i <= n; i++)
            sum[xi[i]]++;
        ll l = 0, r = n + m, res = 0;
        while (l <= r)
        {
            ll mid = (l + r) >> 1;
            if (check(mid) <= m)
                l = mid + 1, res = mid;
            else
                r = mid - 1;
        }
        int ans = fpow(fac[res], (R - L - (rig - lft)));
        int upper = mp.size();
        for (int i = 1; i <= upper; i++)
            if (lft <= i && i <= rig)
                ans = 1LL * ans * fac[max(1LL * sum[i], res)] % mod;
            else
                ans = 1LL * ans * fac[sum[i]] % mod;
        ans = 1LL * ans * fpow(res + 1, m - check(res)) % mod;
        printf("%lld\n", 1LL * fac[n + m] * fpow(ans, mod - 2) % mod);
    }
    // printf("%.3lf\n", 1.0 * clock() / CLOCKS_PER_SEC);
    return 0;
}