// BZ1799.cpp
#include <bits/stdc++.h>
#define ll long long

using namespace std;

const int MAX_N = 220;

int len, digits[MAX_N], domain, mark[2][20][MAX_N][MAX_N], mod;
ll dp[2][20][MAX_N][MAX_N], x, y;

ll dfs(int A, int B, int C, int D)
{
    if (B == 0)
        return C == 0 && D == 0;
    if (mark[A][B][C][D] == domain)
        return dp[A][B][C][D];
    mark[A][B][C][D] = domain;
    ll t = 0, lft = max(0, C - (B - 1) * 9), rig = min(C, A == 1 ? 9 : digits[B]);
    for (ll i = lft; i <= rig; i++)
        t += dfs(A | (i < digits[B]), B - 1, C - i, (D * 10 + i) % mod);
    return dp[A][B][C][D] = t;
}

ll solve(ll x)
{
    ll ret = 0;
    len = 0;
    while (x)
        digits[++len] = x % 10, x /= 10;
    for (mod = 1; mod <= len * 9; mod++)
        domain++, ret += dfs(0, len, mod, 0);
    return ret;
}

int main()
{
    scanf("%lld%lld", &x, &y);
    printf("%lld", solve(y) - solve(x - 1));
    return 0;
}