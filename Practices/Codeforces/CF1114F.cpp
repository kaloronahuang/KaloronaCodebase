// CF1114F.cpp
#include <bits/stdc++.h>
#define mid ((l + r) >> 1)
#define lson (p << 1)
#define rson ((p << 1) | 1)
#define ll long long
using namespace std;
const int MAX_N = 4e5 + 2000, mod = 1e9 + 7, CAPACITY = 61, prime[] = {2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37, 41, 43, 47, 53, 59, 61, 67, 71, 73, 79, 83, 89, 97, 101, 103, 107, 109, 113, 127, 131, 137, 139, 149, 151, 157, 163, 167, 173, 179, 181, 191, 193, 197, 199, 211, 223, 227, 229, 233, 239, 241, 251, 257, 263, 269, 271, 277, 281, 283, 293};
int n, q, arr[MAX_N];
ll res[MAX_N << 2], stat[MAX_N << 2], lazy[MAX_N << 2], lazyStat[MAX_N << 2], inv[CAPACITY + 1];
char opt[50];
ll quick_pow(ll bas, ll tim)
{
    bas %= mod;
    ll ans = 1;
    while (tim)
    {
        if (tim & 1)
            ans = ans * bas % mod;
        bas = bas * bas % mod;
        tim >>= 1;
    }
    return ans;
}
ll factorize(ll num)
{
    ll stat = 0;
    for (int i = 0; i <= CAPACITY; i++)
        if (num % prime[i] == 0)
            stat |= (1LL << i);
    return stat;
}
void build(int l, int r, int p)
{
    if (l == r)
    {
        res[p] = arr[l], lazy[p] = 1;
        stat[p] = factorize(arr[l]);
        return;
    }
    build(l, mid, lson), build(mid + 1, r, rson);
    stat[p] = stat[lson] | stat[rson], res[p] = res[lson] * res[rson] % mod;
    lazy[p] = 1, lazyStat[p] = 0;
}
void update(int ql, int qr, int l, int r, int p, int c, ll flag)
{
    if (ql <= l && r <= qr)
    {
        res[p] = res[p] * quick_pow(c, r - l + 1) % mod;
        stat[p] |= flag, lazy[p] = lazy[p] * c % mod, lazyStat[p] |= flag;
        return;
    }
    if (lazy[p] != 1 || lazyStat[p])
    {
        res[lson] = res[lson] * quick_pow(lazy[p], mid - l + 1) % mod, lazy[lson] = lazy[lson] * lazy[p] % mod;
        res[rson] = res[rson] * quick_pow(lazy[p], r - mid) % mod, lazy[rson] = lazy[rson] * lazy[p] % mod;
        stat[lson] |= lazyStat[p], stat[rson] |= lazyStat[p];
        lazyStat[lson] |= lazyStat[p], lazyStat[rson] |= lazyStat[p];
    }
    lazy[p] = 1, lazyStat[p] = 0;
    if (ql <= mid)
        update(ql, qr, l, mid, lson, c, flag);
    if (mid < qr)
        update(ql, qr, mid + 1, r, rson, c, flag);
    stat[p] = stat[lson] | stat[rson], res[p] = res[lson] * res[rson] % mod;
}
pair<ll, ll> query(int ql, int qr, int l, int r, int p)
{
    ll status = 0, result = 1;
    if (ql <= l && r <= qr)
    {
        status |= stat[p], result = (result * res[p]) % mod;
        return make_pair(status, result);
    }
    if (lazy[p] != 1 || lazyStat[p])
    {
        res[lson] = res[lson] * quick_pow(lazy[p], mid - l + 1) % mod, lazy[lson] = lazy[lson] * lazy[p] % mod;
        res[rson] = res[rson] * quick_pow(lazy[p], r - mid) % mod, lazy[rson] = lazy[rson] * lazy[p] % mod;
        stat[lson] |= lazyStat[p], stat[rson] |= lazyStat[p];
        lazyStat[lson] |= lazyStat[p], lazyStat[rson] |= lazyStat[p];
    }
    lazy[p] = 1, lazyStat[p] = 0;
    if (ql <= mid)
    {
        pair<ll, ll> got = query(ql, qr, l, mid, lson);
        status |= got.first, result = result * got.second % mod;
    }
    if (mid < qr)
    {
        pair<ll, ll> got = query(ql, qr, mid + 1, r, rson);
        status |= got.first, result = result * got.second % mod;
    }
    return make_pair(status, result);
}
int main()
{
    scanf("%d%d", &n, &q);
    for (int i = 1; i <= n; i++)
        scanf("%d", &arr[i]);
    build(1, n, 1);
    for (int i = 0; i <= CAPACITY; i++)
        inv[i] = quick_pow(prime[i], mod - 2);
    while (q--)
    {
        int l, r;
        scanf("%s", opt + 1), scanf("%d%d", &l, &r);
        if (opt[1] == 'M')
        {
            int x;
            scanf("%d", &x), update(l, r, 1, n, 1, x % mod, factorize(x));
        }
        else if (opt[1] == 'T')
        {
            pair<ll, ll> res = query(l, r, 1, n, 1);
            ll ans = res.second;
            for (int i = 0; i <= CAPACITY; i++)
                if ((res.first >> i) & 1)
                    ans = ans * (prime[i] - 1) % mod * inv[i] % mod;
            printf("%lld\n", ans);
        }
    }
    return 0;
}