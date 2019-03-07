// P3924.cpp
#include <bits/stdc++.h>
#define ll long long
#define mid ((l + r) >> 1)
#define lson (p << 1)
#define rson ((p << 1) | 1)
using namespace std;
const int MAX_N = 1e6 + 2000;
ll n, m, qwq, sum[MAX_N << 2], depth[MAX_N << 2], arr[MAX_N], s[MAX_N], max_dep;
inline ll read()
{
    ll s = 0, w = 1;
    char ch = getchar();
    while (ch < '0' || ch > '9')
    {
        if (ch == '-')
            w = -1;
        ch = getchar();
    }
    while (ch >= '0' && ch <= '9')
        s = s * 10 + ch - '0', ch = getchar();
    return s * w;
}
void build(ll l, ll r, ll dp, ll p)
{
    if (l == r)
    {
        sum[p] = arr[l], depth[l] = dp, max_dep = max(max_dep, dp);
        return;
    }
    build(l, mid, dp + 1, lson), build(mid + 1, r, dp + 1, rson);
    sum[p] = sum[lson] + sum[rson];
}
ll query(ll l, ll r, ll p, ll dep, ll prefix)
{
    if (l == r)
        return (1 << dep) * (prefix + sum[p]);
    return query(l, mid, lson, dep - 1, prefix + sum[p]) + query(mid + 1, r, rson, dep - 1, prefix + sum[p]);
}
ll gcd(ll a, ll b) { return (b == 0) ? a : gcd(b, a % b); }
int main()
{
    n = read(), m = read(), qwq = read();
    for (int i = 1; i <= n; i++)
        arr[i] = read();
    build(1, n, 1, 1);
    ll ans = query(1, n, 1, max_dep - 1, 0), dominator = 1 << (max_dep - 1);
    ll fact = gcd(dominator, qwq);
    dominator /= fact, qwq /= fact;
    for (int i = 1; i <= n; i++)
        s[i] = s[i - 1] + (((1 << depth[i]) - 1) << (max_dep - depth[i]));
    while (m--)
    {
        ll l = read(), r = read(), w = read();
        ans += (s[r] - s[l - 1]) * w;
        printf("%lld\n", ans / dominator * qwq);
    }
    return 0;
}