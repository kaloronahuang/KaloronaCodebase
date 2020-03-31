// BZOJ4137.cpp
#include <bits/stdc++.h>

using namespace std;

const int MAX_N = 5e5 + 200;

int n, q, ai[MAX_N], rtot, ctot, gframe, ans[MAX_N];

struct request
{
    int l, r, tl, tr, x;
} reqs[MAX_N];

struct comodity
{
    int time_frame, pos, val;
    bool operator<(const comodity &rhs) const { return pos < rhs.pos; }
} bulks[MAX_N], tmp1[MAX_N], tmp2[MAX_N];

namespace Trie
{

struct node
{
    int ch[2], tag;
} nodes[MAX_N << 3];

int ptot, roots[MAX_N];

int insert(int pre, int dep, int val)
{
    int p = ++ptot;
    nodes[p] = nodes[pre], nodes[p].tag++;
    if (dep < 0)
        return p;
    int dir = (val >> dep) & 1;
    nodes[p].ch[dir] = insert(nodes[pre].ch[dir], dep - 1, val);
    return p;
}

int query(int p, int pre, int dep, int val)
{
    if (dep < 0)
        return 0;
    int dir = (val >> dep) & 1, lval = nodes[nodes[p].ch[dir ^ 1]].tag - nodes[nodes[pre].ch[dir ^ 1]].tag;
    if (lval > 0)
        return query(nodes[p].ch[dir ^ 1], nodes[pre].ch[dir ^ 1], dep - 1, val) ^ (1 << dep);
    else
        return query(nodes[p].ch[dir], nodes[pre].ch[dir], dep - 1, val);
}

} // namespace Trie

#define lson (p << 1)
#define rson ((p << 1) | 1)
#define mid ((l + r) >> 1)

vector<int> nodes[MAX_N << 2];

void update(int ql, int qr, int l, int r, int p, int val)
{
    if (ql > qr)
        return;
    if (ql <= l && r <= qr)
        return (void)(nodes[p].push_back(val));
    if (ql <= mid)
        update(ql, qr, l, mid, lson, val);
    if (mid < qr)
        update(ql, qr, mid + 1, r, rson, val);
}

int stk[MAX_N], tail;

int binary(int x)
{
    int l = 1, r = tail, ret = 0;
    while (l <= r)
        if (stk[mid] <= x)
            ret = mid, l = mid + 1;
        else
            r = mid - 1;
    return ret;
}

void calc(int p, int l, int r)
{
    tail = Trie::ptot = 0;
    for (int i = l; i <= r; i++)
        stk[++tail] = bulks[i].pos, Trie::roots[tail] = Trie::insert(Trie::roots[tail - 1], 17, bulks[i].val);
    for (auto &x : nodes[p])
    {
        int lft = binary(reqs[x].l - 1), rig = binary(reqs[x].r);
        ans[x] = max(ans[x], Trie::query(Trie::roots[rig], Trie::roots[lft], 17, reqs[x].x));
    }
}

void solve(int p, int l, int r, int LB, int RB)
{
    if (LB > RB)
        return;
    calc(p, LB, RB);
    if (l == r)
        return;
    int lptr = 0, rptr = 0;
    for (int i = LB; i <= RB; i++)
        if (bulks[i].time_frame <= mid)
            tmp1[++lptr] = bulks[i];
        else
            tmp2[++rptr] = bulks[i];
    for (int i = 1; i <= lptr; i++)
        bulks[LB + i - 1] = tmp1[i];
    for (int i = 1; i <= rptr; i++)
        bulks[LB + lptr + i - 1] = tmp2[i];
    solve(lson, l, mid, LB, LB + lptr - 1);
    solve(rson, mid + 1, r, LB + lptr, RB);
}

#undef mid
#undef rson
#undef lson

int main()
{
    scanf("%d%d", &n, &q);
    for (int i = 1; i <= n; i++)
        scanf("%d", &ai[i]), Trie::roots[i] = Trie::insert(Trie::roots[i - 1], 17, ai[i]);
    for (int i = 1, opt, l, r, d, x; i <= q; i++)
    {
        scanf("%d", &opt);
        if (opt == 1)
        {
            scanf("%d%d%d%d", &l, &r, &x, &d);
            ans[++rtot] = Trie::query(Trie::roots[r], Trie::roots[l - 1], 17, x);
            reqs[rtot] = request{l, r, max(ctot - d + 1, 1), ctot, x};
        }
        else
            ctot++, scanf("%d%d", &bulks[ctot].pos, &bulks[ctot].val), bulks[ctot].time_frame = ctot;
    }
    for (int i = 1; i <= rtot; i++)
        update(reqs[i].tl, reqs[i].tr, 1, ctot, 1, i);
    sort(bulks + 1, bulks + 1 + ctot);
    solve(1, 1, ctot, 1, ctot);
    for (int i = 1; i <= rtot; i++)
        printf("%d\n", ans[i]);
    return 0;
}