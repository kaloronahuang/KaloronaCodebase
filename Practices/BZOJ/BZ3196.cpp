// BZ3196.cpp
#include <bits/stdc++.h>

using namespace std;

const int MAX_N = 55000;

int n, m, seq[MAX_N], ptot, upper, tree[MAX_N], lid[MAX_N], rid[MAX_N];
vector<int> st;

struct query
{
    int opt, l, r, k;
} queries[MAX_N];

struct node
{
    int sum, lson, rson;
} nodes[MAX_N * 550];

inline int lowbit(int x) { return x & (-x); }

int ripe(int x) { return lower_bound(st.begin(), st.end(), x) - st.begin() + 1; }

#define mid ((l + r) >> 1)

int update(int qx, int l, int r, int p, int val)
{
    if (p == 0)
        nodes[++ptot] = nodes[p], p = ptot;
    nodes[p].sum += val;
    if (l == r)
        return p;
    if (qx <= mid)
        nodes[p].lson = update(qx, l, mid, nodes[p].lson, val);
    else
        nodes[p].rson = update(qx, mid + 1, r, nodes[p].rson, val);
    return p;
}

void update(int pos, int val, int delta)
{
    for (; pos <= n; pos += lowbit(pos))
        tree[pos] = update(val, 1, upper, tree[pos], delta);
}

int cnt = 0;

int getRank(int k, int l, int r)
{
    cnt++;
    int ret = 0;
    if (cnt >= 200)
    {
        puts("Holy Shit");
    }
    if (k > r)
    {
        for (int i = 1; i <= lid[0]; i++)
            ret -= nodes[lid[i]].sum;
        for (int i = 1; i <= rid[0]; i++)
            ret += nodes[rid[i]].sum;
        cnt--;
        return ret;
    }
    int clid[30], crid[30];
    for (int i = 1; i <= lid[0]; i++)
        clid[i] = lid[i], lid[i] = nodes[lid[i]].lson;
    for (int i = 1; i <= rid[0]; i++)
        crid[i] = rid[i], rid[i] = nodes[rid[i]].lson;
    ret = getRank(k, l, mid);
    if (k > mid + 1)
    {
        for (int i = 1; i <= lid[0]; i++)
            lid[i] = nodes[clid[i]].rson;
        for (int i = 1; i <= rid[0]; i++)
            rid[i] = nodes[crid[i]].rson;
        ret += getRank(k, mid + 1, r);
    }
    cnt--;
    return ret;
}

int kth(int k, int l, int r)
{
    if (l == r)
        return l;
    int ret = 0;
    for (int i = 1; i <= lid[0]; i++)
        ret -= nodes[nodes[lid[i]].lson].sum;
    for (int i = 1; i <= rid[0]; i++)
        ret += nodes[nodes[rid[i]].lson].sum;
    if (k <= ret)
    {
        for (int i = 1; i <= lid[0]; i++)
            lid[i] = nodes[lid[i]].lson;
        for (int i = 1; i <= rid[0]; i++)
            rid[i] = nodes[rid[i]].lson;
        return kth(k, l, mid);
    }
    else
    {
        k -= ret;
        for (int i = 1; i <= lid[0]; i++)
            lid[i] = nodes[lid[i]].rson;
        for (int i = 1; i <= rid[0]; i++)
            rid[i] = nodes[rid[i]].rson;
        return kth(k, mid + 1, r);
    }
}

void prepareLineup(int l, int r)
{
    lid[0] = rid[0] = 0;
    for (int i = l - 1; i >= 1; i -= lowbit(i))
        lid[++lid[0]] = tree[i];
    for (int i = r; i >= 1; i -= lowbit(i))
        rid[++rid[0]] = tree[i];
}

#undef mid

int main()
{
    scanf("%d%d", &n, &m);
    for (int i = 1; i <= n; i++)
        scanf("%d", &seq[i]), st.push_back(seq[i]);
    for (int i = 1; i <= m; i++)
    {
        scanf("%d%d%d", &queries[i].opt, &queries[i].l, &queries[i].r);
        if (queries[i].opt != 3)
            scanf("%d", &queries[i].k), st.push_back(queries[i].k);
        else
            st.push_back(queries[i].r);
    }
    sort(st.begin(), st.end()), st.erase(unique(st.begin(), st.end()), st.end());
    upper = st.size();
    for (int i = 1; i <= n; i++)
        update(i, seq[i] = ripe(seq[i]), 1);
    for (int i = 1; i <= m; i++)
    {
        int opt = queries[i].opt, l = queries[i].l, r = queries[i].r, k = queries[i].k;
        if (opt == 1)
            prepareLineup(l, r), printf("%d\n", getRank(ripe(k), 1, upper) + 1);
        else if (opt == 2)
            prepareLineup(l, r), printf("%d\n", st[kth(k, 1, upper) - 1]);
        else if (opt == 3)
        {
            int x = seq[l], y = ripe(r);
            if (x == y)
                continue;
            update(l, x, -1), update(l, y, 1);
            seq[l] = y;
        }
        else if (opt == 4)
        {
            k = ripe(k), prepareLineup(l, r);
            int pos = getRank(k, 1, upper);
            prepareLineup(l, r);
            printf("%d\n", st[kth(pos, 1, upper) - 1]);
        }
        else if (opt == 5)
        {
            k = ripe(k), prepareLineup(l, r);
            int pos = getRank(k + 1, 1, upper);
            prepareLineup(l, r);
            printf("%d\n", st[kth(pos + 1, 1, upper) - 1]);
        }
    }
    return 0;
}