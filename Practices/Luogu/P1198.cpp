// P1198.cpp
#include <bits/stdc++.h>
#define ll long long

using namespace std;

const int MAX_N = 2e5 + 200, DOM = 2e5;

ll nodes[MAX_N << 2], lastans, D;
int length, m;

#define lson (p << 1)
#define rson ((p << 1) | 1)
#define mid ((l + r) >> 1)

void update(int qx, int l, int r, int p, ll val)
{
    if (l == r)
        return (void)(nodes[p] = val);
    if (qx <= mid)
        update(qx, l, mid, lson, val);
    else
        update(qx, mid + 1, r, rson, val);
    nodes[p] = max(nodes[lson], nodes[rson]);
}

ll query(int ql, int qr, int l, int r, int p)
{
    if (ql <= l && r <= qr)
        return nodes[p];
    ll ret = -0x7ffffffffffffff;
    if (ql <= mid)
        ret = max(query(ql, qr, l, mid, lson), ret);
    if (mid < qr)
        ret = max(query(ql, qr, mid + 1, r, rson), ret);
    return ret;
}

#undef lson
#undef rson
#undef mid

char opt[20];

int main()
{
    scanf("%d%lld", &m, &D);
    int range = m;
    while (m--)
    {
        ll x;
        scanf("%s%lld", opt + 1, &x);
        if (opt[1] == 'Q')
            printf("%lld\n", lastans = ((x == 0) ? 0 : (query(length - x + 1, length, 1, range, 1) % D)));
        else
            update(++length, 1, range, 1, (x + lastans) % D);
    }
    return 0;
}