// LOJ6540.cpp
#include <bits/stdc++.h>

using namespace std;

typedef unsigned uint;
typedef long long ll;

const int MAX_N = 1e5 + 200;
const ll RANGE = (1LL << 32) - 1;

int n, ptot, root;
bool tag[MAX_N];

struct node
{
    int lson, rson;
    ll even, odd;
    bool tag;
} nodes[MAX_N * 40];

#define mid ((l + r) >> 1)

void mark(ll l, ll r, int p)
{
    nodes[p].even = (r - l + 1) >> 1, nodes[p].odd = (r - l + 1) - ((r - l + 1) >> 1);
    nodes[p].tag = true;
}

void pushup(int p)
{
    nodes[p].even = nodes[nodes[p].lson].even + nodes[nodes[p].rson].even;
    nodes[p].odd = nodes[nodes[p].lson].odd + nodes[nodes[p].rson].odd;
}

int update(ll ql, ll qr, ll l, ll r, int p)
{
    if (p == 0)
        p = ++ptot;
    if (nodes[p].tag)
        return p;
    if (l == r)
    {
        nodes[p].odd = __builtin_popcount(l) & 1, nodes[p].even = (1 - nodes[p].odd);
        return p;
    }
    if (ql <= l && r <= qr)
        return mark(l, r, p), p;
    if (ql <= mid)
        nodes[p].lson = update(ql, qr, l, mid, nodes[p].lson);
    if (mid < qr)
        nodes[p].rson = update(ql, qr, mid + 1, r, nodes[p].rson);
    pushup(p);
    return p;
}

int main()
{
    scanf("%d", &n);
    while (n--)
    {
        ll l, r;
        scanf("%lld%lld", &l, &r);
        root = update(l, r, 0, RANGE, root);
        printf("%lld\n", 1LL * nodes[root].odd * nodes[root].even);
    }
    return 0;
}