// BZ1396.cpp
#include <bits/stdc++.h>

using namespace std;

const int MAX_N = 2e6 + 200, INF = 0x3f3f3f3f;

int n, siz[MAX_N], bucket[MAX_N], rnk[MAX_N], pos[MAX_N], rig[MAX_N], ans[MAX_N];
char S[MAX_N];

namespace SGT
{

    int nodes[MAX_N << 2], tag[MAX_N << 2];

#define lson (p << 1)
#define rson ((p << 1) | 1)
#define mid ((l + r) >> 1)

    void build(int l, int r, int p)
    {
        tag[p] = INF;
        if (l == r)
            return (void)(nodes[p] = INF);
        build(l, mid, lson), build(mid + 1, r, rson);
        nodes[p] = min(nodes[lson], nodes[rson]);
    }

    void modify(int p, int val) { nodes[p] = min(nodes[p], val), tag[p] = min(tag[p], val); }

    void pushdown(int p)
    {
        if (tag[p] != INF)
        {
            modify(lson, tag[p]), modify(rson, tag[p]);
            tag[p] = INF;
        }
    }

    void update(int ql, int qr, int l, int r, int p, int val)
    {
        if (ql <= l && r <= qr)
            return (void)(modify(p, val));
        pushdown(p);
        if (ql <= mid)
            update(ql, qr, l, mid, lson, val);
        if (mid < qr)
            update(ql, qr, mid + 1, r, rson, val);
        nodes[p] = min(nodes[lson], nodes[rson]);
    }

    int query(int ql, int qr, int l, int r, int p)
    {
        if (ql <= l && r <= qr)
            return nodes[p];
        pushdown(p);
        int ret = INF;
        if (ql <= mid)
            ret = min(ret, query(ql, qr, l, mid, lson));
        if (mid < qr)
            ret = min(ret, query(ql, qr, mid + 1, r, rson));
        return ret;
    }

#undef mid
#undef rson
#undef lson

} // namespace SGT

namespace SAM
{

    struct node
    {
        int ch[26], link, dep;
    } nodes[MAX_N];

    int last_ptr = 1, ptot = 1;

    void insert(int c)
    {
        int pre = last_ptr, p = last_ptr = ++ptot;
        nodes[p].dep = nodes[pre].dep + 1;
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
                int clone = ++ptot;
                nodes[clone] = nodes[q], nodes[clone].dep = nodes[pre].dep + 1;
                nodes[p].link = nodes[q].link = clone, rig[clone] = rig[q];
                while (pre && nodes[pre].ch[c] == q)
                    nodes[pre].ch[c] = clone, pre = nodes[pre].link;
            }
        }
    }

} // namespace SAM

int main()
{
    scanf("%s", S + 1), n = strlen(S + 1);
    using namespace SAM;
    for (int i = 1; i <= n; i++)
        insert(S[i] - 'a'), siz[pos[i] = last_ptr]++, rig[last_ptr] = i;
    for (int i = 1; i <= ptot; i++)
        bucket[nodes[i].dep]++;
    for (int i = 1; i <= ptot; i++)
        bucket[i] += bucket[i - 1];
    for (int i = 1; i <= ptot; i++)
        rnk[bucket[nodes[i].dep]--] = i;
    for (int i = ptot; i >= 1; i--)
    {
        int u = rnk[i];
        if (nodes[u].link)
            siz[nodes[u].link] += siz[u];
    }
    SGT::build(1, n, 1);
    for (int i = 2; i <= ptot; i++)
        if (siz[i] == 1)
        {
            int val = nodes[nodes[i].link].dep + 1;
            SGT::update(rig[i] - val + 1, rig[i], 1, n, 1, val);
            // cout << i << " : " << rig[i] << " : " << val << endl;
        }
    ans[n + 1] = INF;
    for (int i = n; i >= 1; i--)
        ans[i] = min(ans[i + 1] + 1, SGT::query(i, i, 1, n, 1));
    for (int i = 1; i <= n; i++)
        printf("%d\n", ans[i]);
    return 0;
}