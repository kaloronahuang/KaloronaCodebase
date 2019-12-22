// LOJ2720.cpp
#include <bits/stdc++.h>

using namespace std;

const int MAX_N = 1e6 + 2000, MAX_M = 2e7 + 200;

int n, q, limit[MAX_N];
char S[MAX_N], T[MAX_N];

namespace SegmentTree
{

struct node
{
    int sum, lson, rson;
} nodes[MAX_M];

int ptot, roots[MAX_N];

int update(int qx, int l, int r, int p)
{
    if (p == 0)
        p = ++ptot;
    nodes[p].sum++;
    if (l == r)
        return p;
    int mid = (l + r) >> 1;
    if (qx <= mid)
        nodes[p].lson = update(qx, l, mid, nodes[p].lson);
    else
        nodes[p].rson = update(qx, mid + 1, r, nodes[p].rson);
    return p;
}

int query(int ql, int qr, int l, int r, int p)
{
    if (p == 0)
        return 0;
    if (ql <= l && r <= qr)
        return nodes[p].sum;
    int ret = 0, mid = (l + r) >> 1;
    if (ql <= mid)
        ret += query(ql, qr, l, mid, nodes[p].lson);
    if (mid < qr)
        ret += query(ql, qr, mid + 1, r, nodes[p].rson);
    return ret;
}

int merge(int x, int y, int l, int r)
{
    if (x == 0 || y == 0)
        return x + y;
    int p = ++ptot, mid = (l + r) >> 1;
    nodes[p].sum = nodes[x].sum + nodes[y].sum;
    if (l == r)
        return p;
    nodes[p].lson = merge(nodes[x].lson, nodes[y].lson, l, mid);
    nodes[p].rson = merge(nodes[x].rson, nodes[y].rson, mid + 1, r);
    return p;
}

} // namespace SegmentTree

namespace SAM
{

struct node
{
    int dep, ch[26], link;
} nodes[MAX_N];

int last_ptr = 1, ptot = 1, bucket[MAX_N], rnk[MAX_N];

int newnode() { return ++ptot; }

void initialize_collection()
{
    for (int i = 1; i <= ptot; i++)
        bucket[nodes[i].dep]++;
    for (int i = 1; i <= ptot; i++)
        bucket[i] += bucket[i - 1];
    for (int i = 1; i <= ptot; i++)
        rnk[bucket[nodes[i].dep]--] = i;
    for (int i = ptot; i >= 1; i--)
        if (nodes[rnk[i]].link != 0)
            SegmentTree::roots[nodes[rnk[i]].link] = SegmentTree::merge(SegmentTree::roots[nodes[rnk[i]].link], SegmentTree::roots[rnk[i]], 1, n);
}

} // namespace SAM

namespace SAM_T
{

SAM::node nodes[MAX_N];
int ptot = 1, last_ptr = 1, pos[MAX_N];

void clear() { ptot = last_ptr = 1, memset(nodes[1].ch, 0, sizeof(nodes[1].ch)), nodes[1].dep = nodes[1].link = 0; }

int newnode()
{
    int p = ++ptot;
    memset(nodes[p].ch, 0, sizeof(nodes[p].ch));
    nodes[p].dep = nodes[p].link = 0, pos[p] = 0;
    return p;
}

} // namespace SAM_T

int insert(int c, int &last_ptr, int (*newnode)(), SAM::node *nodes, bool toggle = false)
{
    int pre = last_ptr, p = last_ptr = newnode();
    nodes[p].dep = nodes[pre].dep + 1;
    if (toggle)
        SAM_T::pos[p] = nodes[p].dep;
    while (pre && nodes[pre].ch[c] == 0)
        nodes[pre].ch[c] = p, pre = nodes[pre].link;
    if (pre == 0)
        nodes[p].link = 1;
    else
    {
        int q = nodes[pre].ch[c];
        if (nodes[q].dep == nodes[pre].dep + 1)
            nodes[p].link = q;
        else
        {
            int clone = newnode();
            nodes[clone] = nodes[q];
            if (toggle)
                SAM_T::pos[clone] = SAM_T::pos[q];
            nodes[clone].dep = nodes[pre].dep + 1;
            nodes[q].link = nodes[p].link = clone;
            while (pre && nodes[pre].ch[c] == q)
                nodes[pre].ch[c] = clone, pre = nodes[pre].link;
        }
    }
    return p;
}

int main()
{
    freopen("name.in", "r", stdin);
    freopen("name.out", "w", stdout);
    scanf("%s", S + 1), n = strlen(S + 1);
    for (int i = 1; i <= n; i++)
    {
        insert(S[i] - 'a', SAM::last_ptr, SAM::newnode, SAM::nodes);
        SegmentTree::roots[SAM::last_ptr] = SegmentTree::update(i, 1, n, SegmentTree::roots[SAM::last_ptr]);
    }
    SAM::initialize_collection();
    scanf("%d", &q);
    while (q--)
    {
        int l, r, m;
        scanf("%s%d%d", T + 1, &l, &r);
        SAM_T::clear(), m = strlen(T + 1);
        for (int i = 1, p = 1, clen = 0; i <= m; i++)
        {
            int c = T[i] - 'a';
            insert(c, SAM_T::last_ptr, SAM_T::newnode, SAM_T::nodes, true);
            while (true)
            {
                if (SAM::nodes[p].ch[c] && SegmentTree::query(
                                               l + clen, r,
                                               1, n,
                                               SegmentTree::roots[SAM::nodes[p].ch[c]]))
                {
                    clen++, p = SAM::nodes[p].ch[c];
                    break;
                }
                if (clen == 0)
                    break;
                clen--;
                if (clen == SAM::nodes[SAM::nodes[p].link].dep)
                    p = SAM::nodes[p].link;
            }
            limit[i] = clen;
        }
        long long ans = 0;
        for (int i = 2; i <= SAM_T::ptot; i++)
            ans += max(0, SAM_T::nodes[i].dep - max(SAM_T::nodes[SAM_T::nodes[i].link].dep, limit[SAM_T::pos[i]]));
        printf("%lld\n", ans);
    }
    return 0;
}