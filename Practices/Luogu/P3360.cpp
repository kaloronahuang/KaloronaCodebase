// P3360.cpp
#include <bits/stdc++.h>
using namespace std;
#define ll long long
const int MAX_N = 1010;
ll f[MAX_N][MAX_N], w[MAX_N], c[MAX_N], n, tot = 1;
void dfs(ll u)
{
    ll t, x;
    scanf("%lld%lld", &t, &x), t *= 2;
    if (x == 0)
    {
        ll l = ++tot;
        dfs(l);
        ll r = ++tot;
        dfs(r);
        for (int i = t; i <= n; i++)
            for (int j = 0; j <= i - t; j++)
                f[u][i] = max(f[l][j] + f[r][i - t - j], f[u][i]);
        return;
    }
    for (int i = 1; i <= x; i++)
        scanf("%d%d", &w[i], &c[i]);
    for (int i = 1; i <= x; i++)
        for (int j = n; j >= c[i]; j--)
            if (j - c[i] >= t)
                f[u][j] = max(f[u][j], f[u][j - c[i]] + w[i]);
}
int main()
{
    scanf("%lld", &n), n--, dfs(1);
    printf("%lld", f[1][n]);
    return 0;
}