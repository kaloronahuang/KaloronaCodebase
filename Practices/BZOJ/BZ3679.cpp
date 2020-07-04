// BZ3679.cpp
#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

const int MAX_N = 33;

int n, ai[MAX_N], tot, ptot;
ll L, R, dp[MAX_N][6060];
map<int, int> mp;

ll solve(int pos, ll prod, bool pzero, bool touched)
{
    if (prod > n)
        return 0;
    if (!mp.count(prod))
        mp[prod] = ++ptot;
    if (pos == 0)
        return (prod > 0);
    if (!pzero && !touched && dp[pos][mp[prod]] != -1)
        return dp[pos][mp[prod]];
    int upper = touched ? ai[pos] : 9;
    ll ret = solve(pos - 1, 0, pzero, touched && 0 == ai[pos]);
    for (int i = 1; i <= upper; i++)
        if (pzero)
            ret += solve(pos - 1, i, false, touched && ai[pos] == i);
        else
            ret += solve(pos - 1, prod * i, false, touched && ai[pos] == i);
    if (!pzero && !touched)
        dp[pos][mp[prod]] = ret;
    return ret;
}

ll solve(ll upper)
{
    tot = 0;
    while (upper)
        ai[++tot] = upper % 10, upper /= 10;
    return solve(tot, 0, true, true);
}

int main()
{
    memset(dp, -1, sizeof(dp));
    scanf("%d%lld%lld", &n, &L, &R);
    printf("%lld\n", solve(R - 1) - solve(L - 1));
    return 0;
}