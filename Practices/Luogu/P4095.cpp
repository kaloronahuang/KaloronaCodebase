// P4095.cpp
#include <bits/stdc++.h>
#define ll long long

using namespace std;

const int MAX_N = 1010;

ll dp_prefix[MAX_N * 10][MAX_N], dp_suffix[MAX_N * 10][MAX_N];
ll n, tot, wi[MAX_N * 10], vi[MAX_N * 10], lft[MAX_N], rig[MAX_N], q;

int main()
{
    scanf("%lld", &n);
    for (int i = 1; i <= n; i++)
    {
        ll a, b, c;
        scanf("%lld%lld%lld", &a, &b, &c);
        int now = 1;
        lft[i] = tot + 1;
        while (c >= now)
            wi[++tot] = a * now, vi[tot] = b * now, c -= now, now <<= 1;
        if (c > 0)
            wi[++tot] = c * a, vi[tot] = c * b;
        rig[i] = tot;
    }
    scanf("%lld", &q);
    for (int i = 1; i <= tot; i++)
        for (int j = 1000; j >= 0; j--)
        {
            dp_prefix[i][j] = dp_prefix[i - 1][j];
            if (j >= wi[i])
                dp_prefix[i][j] = max(dp_prefix[i][j], dp_prefix[i - 1][j - wi[i]] + vi[i]);
        }
    for (int i = tot; i >= 1; i--)
        for (int j = 1000; j >= 0; j--)
        {
            dp_suffix[i][j] = dp_suffix[i + 1][j];
            if (j >= wi[i])
                dp_suffix[i][j] = max(dp_suffix[i][j], dp_suffix[i + 1][j - wi[i]] + vi[i]);
        }
    while (q--)
    {
        ll di, ei;
        scanf("%lld%lld", &di, &ei), di++;
        ll ans = 0;
        for (int i = ei; i >= 0; i--)
            ans = max(ans, dp_prefix[lft[di] - 1][i] + dp_suffix[rig[di] + 1][ei - i]);
        printf("%lld\n", ans);
    }
    return 0;
}