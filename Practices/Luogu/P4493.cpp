// P4493.cpp
#include <bits/stdc++.h>

using namespace std;

const int MAX_N = 3e5 + 200;

typedef long long ll;
typedef unsigned long long ull;

int n, K, q, pos[MAX_N], roots[MAX_N], bpos[MAX_N], blen[MAX_N];
char str[MAX_N], B[MAX_N];
ll ansBox[MAX_N];

struct queryInfo
{
    int l1, r1, l2, r2, id;
    bool operator<(const queryInfo &rhs) const { return r2 - l2 < rhs.r2 - rhs.l2; }
} queries[MAX_N];

namespace SegmentTree
{

struct node
{
    int val, lson, rson;
} nodes[MAX_N * 60];

int ptot;

#define mid ((l + r) >> 1)

int update(int qx, int l, int r, int p)
{
    if (p == 0)
        p = ++ptot;
    if (l == r)
    {
        nodes[p].val = l;
        return p;
    }
    if (qx <= mid)
        nodes[p].lson = update(qx, l, mid, nodes[p].lson);
    else
        nodes[p].rson = update(qx, mid + 1, r, nodes[p].rson);
    nodes[p].val = max(nodes[nodes[p].lson].val, nodes[nodes[p].rson].val);
    return p;
}

int merge(int x, int y, int l, int r)
{
    if (x == 0 || y == 0)
        return x + y;
    else if (l == r)
    {
        int p = ++ptot;
        nodes[p].val = l;
        return p;
    }
    int p = ++ptot;
    nodes[p].lson = merge(nodes[x].lson, nodes[y].lson, l, mid);
    nodes[p].rson = merge(nodes[x].rson, nodes[y].rson, mid + 1, r);
    nodes[p].val = max(nodes[nodes[p].lson].val, nodes[nodes[p].rson].val);
    return p;
}

int query(int qx, int l, int r, int p)
{
    if (l == r)
        return l;
    if (nodes[nodes[p].lson].val >= qx)
        return query(qx, l, mid, nodes[p].lson);
    else
        return query(qx, mid + 1, r, nodes[p].rson);
}

#undef mid

} // namespace SegmentTree

namespace SAM
{

struct node
{
    int ch[26], link, dep;
} nodes[MAX_N];

int ptot = 1, last_ptr = 1, bucket[MAX_N], idx[MAX_N], up[20][MAX_N];

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
            nodes[p].link = nodes[q].link = clone;
            while (pre && nodes[pre].ch[c] == q)
                nodes[pre].ch[c] = clone, pre = nodes[pre].link;
        }
    }
}

void radixSort()
{
    for (int i = 1; i <= ptot; i++)
        bucket[nodes[i].dep]++;
    for (int i = 1; i <= ptot; i++)
        bucket[i] += bucket[i - 1];
    for (int i = 1; i <= ptot; i++)
        idx[bucket[nodes[i].dep]--] = i;
    for (int i = ptot; i >= 1; i--)
        if (nodes[idx[i]].link != 0)
            roots[nodes[idx[i]].link] = SegmentTree::merge(roots[nodes[idx[i]].link], roots[idx[i]], 1, n);
    for (int i = 1; i <= ptot; i++)
        up[0][i] = nodes[i].link;
    for (int i = 1; i < 20; i++)
        for (int j = 1; j <= ptot; j++)
            up[i][j] = up[i - 1][up[i - 1][j]];
    for (int i = 1, p = 1, len = 0; i <= n; i++)
    {
        if (nodes[p].ch[B[i] - 'a'] != 0)
            p = nodes[p].ch[B[i] - 'a'], len++;
        else
        {
            while (p && nodes[p].ch[B[i] - 'a'] == 0)
                p = nodes[p].link;
            if (p == 0)
                p = 1, len = 0;
            else
                len = nodes[p].dep + 1, p = nodes[p].ch[B[i] - 'a'];
        }
        bpos[i] = p, blen[i] = len;
    }
}

int jump(int pos, int len)
{
    int p = bpos[pos];
    if (blen[pos] < len)
        return 0;
    for (int i = 19; i >= 0; i--)
        if (up[i][p] && nodes[up[i][p]].dep >= len)
            p = up[i][p];
    return p;
}

ll solve(queryInfo curt)
{
    int len = curt.r2 - curt.l2 + 1;
    curt.r1 = min(curt.r1, K + len - 1);
    int p = jump(curt.r2, len);
    if (p == 0)
        return 0;
    if (SegmentTree::nodes[roots[p]].val < curt.l1 + len - 1)
        return 0;
    int stpos = SegmentTree::query(curt.l1 + len - 1, 1, n, roots[p]), edpos = curt.r1;
    ll ret = 0;
    while (stpos <= edpos)
    {
        if (stpos - len + 1 >= K)
            break;
        ret += K - (stpos - len + 1);
        if (SegmentTree::nodes[roots[p]].val < stpos + len)
            break;
        stpos = SegmentTree::query(stpos + len, 1, n, roots[p]);
    }
    return ret;
}

} // namespace SAM

namespace Subtask2
{

const int bitnum = 133;
int nxt[20][MAX_N];
ull hash_val[MAX_N], pow_[MAX_N];
ll prod[20][MAX_N];

void processHash()
{
    for (int i = pow_[0] = 1; i <= n; i++)
        hash_val[i] = hash_val[i - 1] * bitnum + str[i] - 'a', pow_[i] = pow_[i - 1] * bitnum;
}

void processNxt(int len)
{
    memset(nxt, 0, sizeof(nxt));
    unordered_map<ull, deque<int> /**/> pre;
    for (int i = 1; i + len - 1 <= n; i++)
    {
        ull chash = hash_val[i + len - 1] - hash_val[i - 1] * pow_[len];
        while (!pre[chash].empty() && pre[chash].front() <= i - len)
            nxt[0][pre[chash].front()] = i, pre[chash].pop_front();
        pre[chash].push_back(i), prod[0][i] = K - i;
    }
    for (int i = 1; i < 20; i++)
        for (int j = 1; j <= n - len + 1; j++)
        {
            nxt[i][j] = nxt[i - 1][nxt[i - 1][j]];
            prod[i][j] = prod[i - 1][j] + prod[i - 1][nxt[i - 1][j]];
        }
}

ll solve(queryInfo curt)
{
    int len = curt.r2 - curt.l2 + 1;
    curt.r1 = min(curt.r1, K + len - 1);
    int p = SAM::jump(curt.r2, len);
    if (p == 0)
        return 0;
    if (SegmentTree::nodes[roots[p]].val < curt.l1 + len - 1)
        return 0;
    int stpos = SegmentTree::query(curt.l1 + len - 1, 1, n, roots[p]) - len + 1, edpos = curt.r1 - len + 1;
    if (stpos > edpos)
        return 0;
    ll ret = 0;
    for (int i = 19; i >= 0; i--)
        if (nxt[i][stpos] && nxt[i][stpos] <= edpos)
            ret += prod[i][stpos], stpos = nxt[i][stpos];
    ret += prod[0][stpos];
    return ret;
}

} // namespace Subtask2

int main()
{
    // freopen("cover4.in", "r", stdin);
    // freopen("test.out", "w", stdout);
    scanf("%d%d%s%s", &n, &K, str + 1, B + 1);
    for (int i = 1; i <= n; i++)
    {
        SAM::insert(str[i] - 'a'), pos[i] = SAM::last_ptr;
        roots[SAM::last_ptr] = SegmentTree::update(i, 1, n, roots[SAM::last_ptr]);
    }
    Subtask2::processHash(), SAM::radixSort(), scanf("%d", &q);
    for (int i = 1; i <= q; i++)
        scanf("%d%d%d%d", &queries[i].l1, &queries[i].r1, &queries[i].l2, &queries[i].r2), queries[i].id = i;
    sort(queries + 1, queries + 1 + q);
    for (int ptr = 1; ptr <= q; ptr++)
    {
        queryInfo curt = queries[ptr];
        if (curt.r2 - curt.l2 + 1 <= 51)
        {
            if (ptr == 1 || curt.r2 - curt.l2 != queries[ptr - 1].r2 - queries[ptr - 1].l2)
                Subtask2::processNxt(curt.r2 - curt.l2 + 1);
            ansBox[curt.id] = Subtask2::solve(curt);
        }
        else
            ansBox[curt.id] = SAM::solve(curt);
    }
    for (int i = 1; i <= q; i++)
        printf("%lld\n", ansBox[i]);
    return 0;
}