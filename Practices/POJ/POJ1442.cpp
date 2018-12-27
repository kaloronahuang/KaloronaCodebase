// POJ1442.cpp
#include <iostream>
#include <vector>
#include <algorithm>
#include <cstdio>
#define mid ((l + r) >> 1)
#define ls (p << 1)
#define rs ((p << 1) | 1)
#define ll long long
using namespace std;
const ll MX_N = 200200;
struct node
{
    ll idx, val;
    bool operator<(const node &nd) const { return val < nd.val; }
};
ll f[MX_N << 2], n, m, idx, u[MX_N], mapping[MX_N], tmpx;
node add[MX_N];
void update(ll l, ll r, ll p, ll c)
{
    if (l == r && l == c)
        f[p]++;
    else
    {
        if (c <= mid)
            update(l, mid, ls, c);
        else
            update(mid + 1, r, rs, c);
        f[p] = f[ls] + f[rs];
    }
}
ll kth(ll l, ll r, ll k, ll p)
{
    if (l == r)
        return l;
    if (f[ls] >= k)
        return kth(l, mid, k, ls);
    else
        return kth(mid + 1, r, k - f[ls], rs);
}
int main()
{
    scanf("%lld%lld", &n, &m);
    for (ll i = 1; i <= n; i++)
        scanf("%lld", &add[i].val), add[i].idx = i;
    for (ll i = 1; i <= m; i++)
        scanf("%lld", &u[i]);
    sort(add + 1, add + n + 1);
    for (ll i = 1; i <= n; i++)
        mapping[add[i].idx] = i;
    ll cnt = 1;
    for (ll i = 1; i <= n; i++)
    {
        update(1, n, 1, mapping[i]);
        while (u[cnt] == i)
        {
            printf("%lld\n", add[kth(1, n, cnt, 1)].val);
            cnt++;
        }
    }
    return 0;
}