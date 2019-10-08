// P3960.cpp
#include <bits/stdc++.h>
#define ll long long

using namespace std;

const int MAX_N = 3e5 + 200, SEG = 1e7 + 200;

ll siz[SEG], n, m, q, ptot, upper;
int lson[SEG], rson[SEG], roots[SEG];
vector<ll> vecs[MAX_N];

ll atRank(ll k, int l, int r, int p)
{
    if (l == r)
        return l;
    ll mid = (l + r) >> 1, lsiz = mid - l + 1 - siz[lson[p]];
    if (k <= lsiz)
        return atRank(k, l, mid, lson[p]);
    else
        return atRank(k - lsiz, mid + 1, r, rson[p]);
}

int update(int qx, int l, int r, int p)
{
    if (p == 0)
        p = ++ptot;
    ++siz[p];
    if (l == r)
        return p;
    int mid = (l + r) >> 1;
    if (qx <= mid)
        lson[p] = update(qx, l, mid, lson[p]);
    else
        rson[p] = update(qx, mid + 1, r, rson[p]);
    return p;
}

ll query_col(int x, int y)
{
    ll tmp = atRank(y, 1, upper, roots[x]);
    roots[x] = update(tmp, 1, upper, roots[x]);
    return tmp < m ? 1LL * (x - 1) * m + tmp : vecs[x][tmp - m];
}

ll query_row(int x)
{
    ll tmp = atRank(x, 1, upper, roots[n + 1]);
    roots[n + 1] = update(tmp, 1, upper, roots[n + 1]);
    return tmp <= n ? 1LL * tmp * m : vecs[n + 1][tmp - n - 1];
}

int main()
{
    scanf("%lld%lld%lld", &n, &m, &q);
    upper = max(n, m) + q;
    while (q--)
    {
        int x, y;
        ll tmp;
        scanf("%d%d", &x, &y);
        if (y == m)
            tmp = query_row(x), vecs[n + 1].push_back(tmp), printf("%lld\n", tmp);
        else
        {
            tmp = query_col(x, y), vecs[n + 1].push_back(tmp);
            printf("%lld\n", tmp);
            tmp = query_row(x), vecs[x].push_back(tmp);
        }
    }
    return 0;
}