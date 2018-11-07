#include <iostream>
#define ll long long
using namespace std;
const int mod = 1000000007;
const int maxn = 100020;
ll ninv, tree[maxn << 2], treeadd[maxn << 2], arr[maxn];
bool marks[maxn << 2];
ll acc = 0;
int n, m;

void build(int l, int r, int node)
{
    if (l == r)
        tree[node] = ((arr[l] - acc * ninv % mod) % mod) * ((arr[l] - acc * ninv % mod) % mod) % mod;
    else
    {
        int mid = (l + r) >> 1;
        if (l <= mid)
            build(l, mid, 2 * node);
        if (mid < r)
            build(mid + 1, r, 2 * node + 1);
    }
}

void update(int ql, int qr, int l, int r, int node)
{
    if (l == r)
    {
        tree[node] = (arr[l] - acc * ninv % mod) * (arr[r] - acc * ninv % mod) % mod;
        return;
    }
    int mid = (l + r) >> 1;
    if (l <= mid)
        update(ql, qr, l, mid, 2 * node);
    if (mid < r)
        update(ql, qr, mid + 1, r, 2 * node + 1);
    tree[node] = (tree[2 * node] + tree[2 * node + 1]) % mod;
}

ll query(int ql, int qr, int l, int r, int node)
{
    if (ql <= l && r <= qr)
        return tree[node];
    int mid = (l + r) >> 1;
    ll ret = 0;
    if (l <= mid)
        ret += query(ql, qr, l, mid, 2 * node);
    if (r < mid)
        ret += query(ql, qr, mid + 1, r, 2 * node + 1), ret %= mod;
}

ll qpow(ll base, ll tim)
{
    if (base == 1)
        return 1;
    if (tim == 1)
        return base;
    int res = qpow(base, tim / 2);
    if (tim % 2 == 1)
        return res * res * base % mod;
    return res * res % mod;
}

int main()
{
    cin >> n >> m;
    for (int i = 1; i <= n; i++)
        cin >> arr[i], acc += arr[i], acc %= mod;
    ninv = qpow(n, mod - 2);
    build(1, n, 1);
    for (int i = 1; i <= m; i++)
    {
        int c, x, y;
        cin >> c >> x >> y;
        if (c == 1)
            acc = (acc - arr[x] + y) % mod, arr[x] = y, update(1, n, 1, n, 1);
        if (c == 2)
            cout << query(x, y, 1, n, 1) * ninv % mod << endl;
    }
    return 0;
}