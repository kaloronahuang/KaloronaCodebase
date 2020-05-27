// CF1358D.cpp
#include <bits/stdc++.h>

using namespace std;

const int MAX_N = 4e5 + 200;

typedef long long ll;

int n, xi[MAX_N];
ll pre[MAX_N], S, pre2[MAX_N];

ll calc(ll l, ll r) { return (1LL * (l + r) * (r - l + 1)) >> 1; }

int main()
{
    scanf("%d%lld", &n, &S);
    for (int i = 1; i <= n; i++)
        scanf("%d", &xi[i]), xi[i + n] = xi[i], pre[i] = pre[i - 1] + xi[i], pre2[i] = pre2[i - 1] + calc(1, xi[i]);
    for (int i = 1; i <= n; i++)
        pre[i + n] = pre[i + n - 1] + xi[i], pre2[i + n] = pre2[i + n - 1] + calc(1, xi[i]);
    ll ans = 0;
    for (int i = 1, lptr = 0; i <= (n << 1); i++)
    {
        while (pre[i] - pre[lptr] > S)
            lptr++;
        if (i > n)
        {
            ll val = pre2[i] - pre2[lptr], lft = S - (pre[i] - pre[lptr]);
            val += ((2LL * xi[lptr] + 1 - lft) * lft) >> 1;
            ans = max(ans, val);
        }
    }
    printf("%lld\n", ans);
    return 0;
}