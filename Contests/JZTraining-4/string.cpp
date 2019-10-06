// string.cpp
#include <bits/stdc++.h>

using namespace std;

const int MAX_N = 1e5 + 200;

int n, m, tag[MAX_N << 2];
char str[MAX_N];

struct node
{
    int cnt[27], id;
} nodes[MAX_N << 2];

#define lson (p << 1)
#define rson ((p << 1) | 1)
#define mid ((l + r) >> 1)

void pushdown(int p, int l, int r)
{
    if (tag[p])
    {
        memset(nodes[lson].cnt, 0, sizeof(nodes[lson].cnt));
        memset(nodes[rson].cnt, 0, sizeof(nodes[rson].cnt));
        nodes[lson].cnt[tag[p]] = mid - l + 1;
        nodes[rson].cnt[tag[p]] = r - mid;
        nodes[lson].id = nodes[rson].id = tag[p];
        tag[lson] = tag[rson] = tag[p];
        tag[p] = 0;
    }
}

node pushup(node &p, node ls, node rs)
{
    for (int i = 1; i <= 26; i++)
        p.cnt[i] = ls.cnt[i] + rs.cnt[i], p.id = p.cnt[i] == 1 ? i : p.id;
    return p;
}

void build(int l, int r, int p)
{
    if (l == r)
        return (void)(nodes[p].cnt[str[l] - 'a' + 1]++, nodes[p].id = str[l] - 'a' + 1);
    build(l, mid, lson), build(mid + 1, r, rson);
    pushup(nodes[p], nodes[lson], nodes[rson]);
}

void update(int ql, int qr, int l, int r, int p, int val)
{
    if (ql <= l && r <= qr)
    {
        memset(nodes[p].cnt, 0, sizeof(nodes[p].cnt));
        nodes[p].cnt[val] = r - l + 1, tag[p] = val;
        nodes[p].id = val;
        return;
    }
    pushdown(p, l, r);
    if (ql <= mid)
        update(ql, qr, l, mid, lson, val);
    if (mid < qr)
        update(ql, qr, mid + 1, r, rson, val);
    pushup(nodes[p], nodes[lson], nodes[rson]);
}

node query(int ql, int qr, int l, int r, int p)
{
    if (ql <= l && r <= qr)
        return nodes[p];
    node now;
    pushdown(p, l, r);
    memset(now.cnt, 0, sizeof(now.cnt));
    if (ql <= mid)
        now = query(ql, qr, l, mid, lson);
    if (mid < qr)
        pushup(now, now, query(ql, qr, mid + 1, r, rson));
    return now;
}

int main()
{
    scanf("%d%d", &n, &m);
    scanf("%s", str + 1);
    build(1, n, 1);
    while (m--)
    {
        int opt, l, r;
        scanf("%d%d%d", &l, &r, &opt);
        if (opt == 1)
        {
            node res = query(l, r, 1, n, 1);
            int cur = l;
            for (int i = 1; i <= 26; i++)
                if (res.cnt[i] != 0)
                    update(cur, cur + res.cnt[i] - 1, 1, n, 1, i), cur += res.cnt[i];
        }
        else
        {
            node res = query(l, r, 1, n, 1);
            int cur = l;
            for (int i = 26; i >= 1; i--)
                if (res.cnt[i] != 0)
                    update(cur, cur + res.cnt[i] - 1, 1, n, 1, i), cur += res.cnt[i];
        }
    }
    for (int i = 1; i <= n; i++)
    {
        node res = query(i, i, 1, n, 1);
        putchar(res.id + 'a' - 1);
    }
    return 0;
}