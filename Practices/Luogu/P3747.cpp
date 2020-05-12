// P3747.cpp
#include <bits/stdc++.h>

using namespace std;

const int MAX_N = 5e4 + 200;

typedef long long ll;

int n, m, mod, C, ai[MAX_N], nodes[MAX_N << 2], cnt[MAX_N << 2], phi[MAX_N], ptot;
ll pw[2][100][10100];
bool nxt[2][100][10100];

typedef long long ll;

ll fpow(ll tim, ll id, bool &flag)
{
    ll idx1 = tim % 10000, idx2 = tim / 10000, ret = pw[0][id][idx1] * pw[1][id][idx2];
    if (ret >= phi[id])
        flag = true, ret %= phi[id];
    flag |= nxt[0][id][idx1] || nxt[1][id][idx2];
    return ret;
}

ll varphi(ll x)
{
    ll ret = x;
    for (ll i = 2; 1LL * i * i <= x; i++)
        if (x % i == 0)
        {
            ret -= ret / i;
            while (x % i == 0)
                x /= i;
        }
    if (x != 1)
        ret -= ret / x;
    return ret;
}

void sieve()
{
    phi[ptot] = mod;
    while (phi[ptot] != 1)
        ptot++, phi[ptot] = varphi(phi[ptot - 1]);
    phi[++ptot] = 1;
}

#define lson (p << 1)
#define rson ((p << 1) | 1)
#define mid ((l + r) >> 1)

// segment tree;

void pushup(int p) { nodes[p] = (0LL + nodes[lson] + nodes[rson]) % mod, cnt[p] = min(cnt[lson], cnt[rson]); }

void build(int l, int r, int p)
{
    if (l == r)
    {
        nodes[p] = ai[l];
        return;
    }
    build(l, mid, lson), build(mid + 1, r, rson);
    pushup(p);
}

int query(int ql, int qr, int l, int r, int p)
{
    if (ql <= l && r <= qr)
        return nodes[p];
    int ret = 0;
    if (ql <= mid)
        ret = (0LL + ret + query(ql, qr, l, mid, lson)) % mod;
    if (mid < qr)
        ret = (0LL + ret + query(ql, qr, mid + 1, r, rson)) % mod;
    return ret;
}

ll modify(ll base, ll idx)
{
    ll curt = base;
    if (curt > phi[idx])
        curt = curt % phi[idx] + phi[idx];
    for (ll i = idx; i >= 1; i--)
    {
        bool flag = false;
        curt = fpow(curt, i - 1, flag);
        if (flag)
            curt += phi[i - 1];
    }
    return curt;
}

void update(int ql, int qr, int l, int r, int p)
{
    if (cnt[p] >= ptot)
        return;
    if (l == r)
    {
        cnt[p]++, nodes[p] = modify(ai[l], cnt[p]) % mod;
        return;
    }
    if (ql <= mid && cnt[lson] < ptot)
        update(ql, qr, l, mid, lson);
    if (mid < qr && cnt[rson] < ptot)
        update(ql, qr, mid + 1, r, rson);
    pushup(p);
}

int main()
{
    scanf("%d%d%d%d", &n, &m, &mod, &C);
    for (int i = 1; i <= n; i++)
        scanf("%d", &ai[i]);
    sieve(), build(1, n, 1);
    for (int i = 0; i <= ptot; i++)
    {
        pw[0][i][0] = 1;
        for (int j = 1; j <= 10000; j++)
        {
            pw[0][i][j] = pw[0][i][j - 1] * C;
            if (pw[0][i][j] >= phi[i])
                nxt[0][i][j] = true, pw[0][i][j] %= phi[i];
            nxt[0][i][j] |= nxt[0][i][j - 1];
        }
    }
    for (int i = 0; i <= ptot; i++)
    {
        pw[1][i][0] = 1, nxt[1][i][1] = nxt[1][i][10000];
        for (int j = 1; j <= 10000; j++)
        {
            pw[1][i][j] = pw[1][i][j - 1] * pw[0][i][10000];
            if (pw[1][i][j] >= phi[i])
                nxt[1][i][j] = true, pw[1][i][j] %= phi[i];
            nxt[1][i][j] |= nxt[1][i][j - 1];
        }
    }
    while (m--)
    {
        int opt, l, r;
        scanf("%d%d%d", &opt, &l, &r);
        if (opt == 0)
            update(l, r, 1, n, 1);
        else
            printf("%d\n", query(l, r, 1, n, 1));
    }
    return 0;
}