// F.cpp
#include <bits/stdc++.h>

using namespace std;

const int MAX_N = 1e5 + 200, mod = 998244353;

inline int lowbit(int x) { return x & (-x); }

int n, pi[MAX_N], di[MAX_N], nodes[MAX_N << 2];
vector<int> mapping;

int ripe(int x) { return lower_bound(mapping.begin(), mapping.end(), x) - mapping.begin() + 1; }

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

const int inv100 = fpow(100, mod - 2);

/*

void update(int x, int d)
{
    for (; x <= n; x += lowbit(x))
        nodes[x] = 1LL * nodes[x] * d % mod;
}

int query(int x)
{
    int ans = 1;
    for (; x > 0; x -= lowbit(x))
        ans = 1LL * ans * nodes[x] % mod;
    return ans;
}

*/

#define lson (p << 1)
#define rson ((p << 1) | 1)
#define mid ((l + r) >> 1)

void pushup(int p)
{
    nodes[p] = 1LL * nodes[lson] * nodes[rson] % mod;
}

void build(int l, int r, int p)
{
    if (l == r)
    {
        nodes[p] = 1;
        return;
    }
    build(l, mid, lson), build(mid + 1, r, rson);
    pushup(p);
}

void update(int qx, int l, int r, int p, int val)
{
    if (l == r)
    {
        nodes[p] = 1LL * nodes[p] * val % mod;
        return;
    }
    if (qx <= mid)
        update(qx, l, mid, lson, val);
    else
        update(qx, mid + 1, r, rson, val);
    pushup(p);
}

int query(int ql, int qr, int l, int r, int p)
{
    if (ql <= l && r <= qr)
        return nodes[p];
    int ret = 1;
    if (ql <= mid)
        ret = 1LL * ret * query(ql, qr, l, mid, lson) % mod;
    if (mid < qr)
        ret = 1LL * ret * query(ql, qr, mid + 1, r, rson) % mod;
    return ret;
}

int main()
{
    scanf("%d", &n);
    for (int i = 1; i <= n; i++)
        scanf("%d%d", &pi[i], &di[i]), pi[i] = 1LL * pi[i] * inv100 % mod, mapping.push_back(di[i]);
    sort(mapping.begin(), mapping.end());
    mapping.erase(unique(mapping.begin(), mapping.end()), mapping.end());
    for (int i = 1; i <= n; i++)
        di[i] = ripe(di[i]), nodes[i] = 1;
    int ans = 0;
    build(1, n, 1);
    for (int i = 1; i <= n; i++)
    {
        int prob = query(di[i] + 1, n, 1, n, 1);
        ans = (0LL + ans + 1LL * prob * pi[i] % mod) % mod;
        update(di[i], 1, n, 1, (1LL + mod - pi[i]));
    }
    printf("%d\n", ans);
    return 0;
}