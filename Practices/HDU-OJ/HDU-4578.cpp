// HDU-4578.cpp
#include <bits/stdc++.h>

using namespace std;

const int MAX_N = 1e5 + 200, mod = 10007;

int n, q;

struct node
{
    int sum[4], add_tag, mul_tag, eval_tag;
} nodes[MAX_N << 2];

#define lson (p << 1)
#define rson ((p << 1) | 1)
#define mid ((l + r) >> 1)

void build(int l, int r, int p)
{
    memset(nodes[p].sum, 0, sizeof(nodes[p].sum));
    nodes[p].add_tag = nodes[p].eval_tag = 0;
    nodes[p].mul_tag = 1;
    if (l == r)
        return;
    build(l, mid, lson), build(mid + 1, r, rson);
    return;
}

void modify_add(int p, int l, int r, int val)
{
    nodes[p].add_tag = (0LL + nodes[p].add_tag + val) % mod;
    nodes[p].sum[3] = (0LL + nodes[p].sum[3] + 1LL * (r - l + 1) * val % mod * val % mod * val % mod + 3LL * val % mod * (0LL + nodes[p].sum[2] + 1LL * nodes[p].sum[1] * val % mod) % mod) % mod;
    nodes[p].sum[2] = (0LL + nodes[p].sum[2] + 1LL * (r - l + 1) * val % mod * val % mod + 2LL * val * nodes[p].sum[1] % mod) % mod;
    nodes[p].sum[1] = (0LL + nodes[p].sum[1] + 1LL * (r - l + 1) * val % mod) % mod;
}

void modify_multiply(int p, int val)
{
    nodes[p].mul_tag = 1LL * nodes[p].mul_tag * val % mod, nodes[p].add_tag = 1LL * nodes[p].add_tag * val % mod;
    nodes[p].sum[3] = 1LL * nodes[p].sum[3] * val % mod * val % mod * val % mod;
    nodes[p].sum[2] = 1LL * nodes[p].sum[2] * val % mod * val % mod;
    nodes[p].sum[1] = 1LL * nodes[p].sum[1] * val % mod;
}

void modify_eval(int p, int l, int r, int val)
{
    nodes[p].add_tag = 0, nodes[p].mul_tag = 1, nodes[p].eval_tag = val;
    nodes[p].sum[1] = 1LL * (r - l + 1) * val % mod;
    nodes[p].sum[2] = 1LL * (r - l + 1) * val % mod * val % mod;
    nodes[p].sum[3] = 1LL * (r - l + 1) * val % mod * val % mod * val % mod;
}

void pushdown(int p, int l, int r)
{
    if (nodes[p].eval_tag)
        modify_eval(lson, l, mid, nodes[p].eval_tag), modify_eval(rson, mid + 1, r, nodes[p].eval_tag), nodes[p].eval_tag = 0;
    if (nodes[p].mul_tag != 1)
        modify_multiply(lson, nodes[p].mul_tag), modify_multiply(rson, nodes[p].mul_tag), nodes[p].mul_tag = 1;
    if (nodes[p].add_tag)
        modify_add(lson, l, mid, nodes[p].add_tag), modify_add(rson, mid + 1, r, nodes[p].add_tag), nodes[p].add_tag = 0;
}

void pushup(int p)
{
    for (int i = 0; i < 4; i++)
        nodes[p].sum[i] = (0LL + nodes[lson].sum[i] + nodes[rson].sum[i]) % mod;
}

void update(int ql, int qr, int l, int r, int p, int val, int typ)
{
    if (ql <= l && r <= qr)
    {
        switch (typ)
        {
        case 1:
            modify_add(p, l, r, val);
            break;
        case 2:
            modify_multiply(p, val);
            break;
        case 3:
            modify_eval(p, l, r, val);
            break;
        }
        return;
    }
    pushdown(p, l, r);
    if (ql <= mid)
        update(ql, qr, l, mid, lson, val, typ);
    if (mid < qr)
        update(ql, qr, mid + 1, r, rson, val, typ);
    pushup(p);
}

int query(int ql, int qr, int l, int r, int p, int typ)
{
    if (ql <= l && r <= qr)
        return nodes[p].sum[typ];
    pushdown(p, l, r);
    int ret = 0;
    if (ql <= mid)
        ret = (0LL + ret + query(ql, qr, l, mid, lson, typ)) % mod;
    if (mid < qr)
        ret = (0LL + ret + query(ql, qr, mid + 1, r, rson, typ)) % mod;
    return ret;
}

int main()
{
    while (scanf("%d%d", &n, &q) != EOF && (n != 0 || q != 0))
    {
        build(1, n, 1);
        while (q--)
        {
            int opt, x, y, p;
            scanf("%d%d%d%d", &opt, &x, &y, &p);
            if (opt <= 3)
                update(x, y, 1, n, 1, p, opt);
            else
                printf("%d\n", query(x, y, 1, n, 1, p));
        }
    }
    return 0;
}