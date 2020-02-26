// LOJ3094.cpp
#include <bits/stdc++.h>

using namespace std;

const int ZERO = 1.5e5 + 1, MAX_N = (ZERO << 1) + ZERO + 1000, LIMIT = (ZERO << 1) + ZERO + 1000;

int n, m, ai[MAX_N], bucket[MAX_N], offset;

struct node
{
    int min_val, min_cnt, zero_cnt, tag;
} nodes[LIMIT << 2];

#define lson (p << 1)
#define rson ((p << 1) | 1)
#define mid ((l + r) >> 1)

void pushup(int p)
{
    nodes[p].min_val = min(nodes[lson].min_val, nodes[rson].min_val);
    nodes[p].min_cnt = (nodes[lson].min_val == nodes[p].min_val ? nodes[lson].min_cnt : 0) +
                       (nodes[rson].min_val == nodes[p].min_val ? nodes[rson].min_cnt : 0);
    nodes[p].zero_cnt = nodes[lson].zero_cnt + nodes[rson].zero_cnt;
}

void build(int l, int r, int p)
{
    if (l == r)
    {
        nodes[p].min_cnt = nodes[p].zero_cnt = 1;
        return;
    }
    build(l, mid, lson), build(mid + 1, r, rson);
    pushup(p);
}

void modify(int p, int val)
{
    nodes[p].min_val += val, nodes[p].tag += val;
    nodes[p].zero_cnt = (nodes[p].min_val == 0) ? nodes[p].min_cnt : 0;
}

void pushdown(int p)
{
    if (nodes[p].tag != 0)
        modify(lson, nodes[p].tag), modify(rson, nodes[p].tag), nodes[p].tag = 0;
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
    pushup(p);
}

int query(int ql, int qr, int l, int r, int p)
{
    if (ql <= l && r <= qr)
        return nodes[p].zero_cnt;
    pushdown(p);
    int ret = 0;
    if (ql <= mid)
        ret += query(ql, qr, l, mid, lson);
    if (mid < qr)
        ret += query(ql, qr, mid + 1, r, rson);
    return ret;
}

#undef mid
#undef rson
#undef lson

void change(int pos, int val)
{
    int real_pos = pos - bucket[pos] + 1 - (val > 0);
    update(real_pos, real_pos, 1, LIMIT, 1, val), bucket[pos] += val;
}

int main()
{
    scanf("%d%d", &n, &m), offset = ZERO, build(1, LIMIT, 1);
    for (int i = 1; i <= n; i++)
        scanf("%d", &ai[i]), ai[i] += offset, change(ai[i], 1);
    while (m--)
    {
        int p, x;
        scanf("%d%d", &p, &x);
        if (p > 0)
        {
            if (ai[p] <= n + offset)
                change(ai[p], -1);
            else
                bucket[ai[p]]--;
            ai[p] = offset + x;
            if (ai[p] <= n + offset)
                change(ai[p], 1);
            else
                bucket[ai[p]]++;
        }
        else if (x > 0)
        {
            int endp = offset + n;
            if (bucket[endp])
                update(endp - bucket[endp] + 1, endp, 1, LIMIT, 1, -1);
            offset--;
        }
        else
        {
            offset++;
            int endp = offset + n;
            if (bucket[endp])
                update(endp - bucket[endp] + 1, endp, 1, LIMIT, 1, 1);
        }
        printf("%d\n", query(offset + 1, offset + n, 1, LIMIT, 1));
    }
    return 0;
}