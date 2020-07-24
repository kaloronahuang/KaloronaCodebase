// P4475.cpp
#include <bits/stdc++.h>

using namespace std;

const int MAX_N = 5e4 + 200;

typedef long long ll;

int n, m, current_frame, groot;

struct node
{
    ll d[2], max_val[2], min_val[2], sum, val;
    int lson, rson;
    bool operator<(const node &rhs) const { return d[current_frame] < rhs.d[current_frame] || (d[current_frame] == rhs.d[current_frame] && d[!current_frame] < rhs.d[!current_frame]); }
} nodes[MAX_N];

void pushup(int p)
{
    for (int i = 0; i < 2; i++)
    {
        nodes[p].max_val[i] = nodes[p].min_val[i] = nodes[p].d[i];
        if (nodes[p].lson)
            nodes[p].max_val[i] = max(nodes[nodes[p].lson].max_val[i], nodes[p].max_val[i]);
        if (nodes[p].rson)
            nodes[p].max_val[i] = max(nodes[nodes[p].rson].max_val[i], nodes[p].max_val[i]);
        if (nodes[p].lson)
            nodes[p].min_val[i] = min(nodes[nodes[p].lson].min_val[i], nodes[p].min_val[i]);
        if (nodes[p].rson)
            nodes[p].min_val[i] = min(nodes[nodes[p].rson].min_val[i], nodes[p].min_val[i]);
    }
    nodes[p].sum = nodes[p].val;
    if (nodes[p].lson)
        nodes[p].sum += nodes[nodes[p].lson].sum;
    if (nodes[p].rson)
        nodes[p].sum += nodes[nodes[p].rson].sum;
}

int build(int l, int r)
{
    if (l > r)
        return 0;
    int p = (l + r) >> 1;
    nth_element(nodes + l, nodes + p, nodes + r + 1);
    current_frame ^= 1;
    nodes[p].lson = build(l, p - 1), nodes[p].rson = build(p + 1, r);
    current_frame ^= 1;
    pushup(p);
    return p;
}

int check(int p, ll a, ll b, ll c)
{
    if (a >= 0 && b >= 0)
    {
        if (nodes[p].max_val[0] * a + nodes[p].max_val[1] * b < c)
            return 1;
        if (nodes[p].min_val[0] * a + nodes[p].min_val[1] * b >= c)
            return -1;
    }
    if (a >= 0 && b < 0)
    {
        if (nodes[p].max_val[0] * a + nodes[p].min_val[1] * b < c)
            return 1;
        if (nodes[p].min_val[0] * a + nodes[p].max_val[1] * b >= c)
            return -1;
    }
    if (a < 0 && b >= 0)
    {
        if (nodes[p].min_val[0] * a + nodes[p].max_val[1] * b < c)
            return 1;
        if (nodes[p].max_val[0] * a + nodes[p].min_val[1] * b >= c)
            return -1;
    }
    if (a < 0 && b < 0)
    {
        if (nodes[p].min_val[0] * a + nodes[p].min_val[1] * b < c)
            return 1;
        if (nodes[p].max_val[0] * a + nodes[p].max_val[1] * b >= c)
            return -1;
    }
    return 0;
}

ll query(int p, ll a, ll b, ll c)
{
    if (p == 0)
        return 0;
    int res = check(p, a, b, c);
    if (res == 1)
        return nodes[p].sum;
    if (res == -1)
        return 0;
    ll sum = 1LL * nodes[p].val * (1LL * a * nodes[p].d[0] + 1LL * b * nodes[p].d[1] < c);
    if (nodes[p].lson)
        sum += query(nodes[p].lson, a, b, c);
    if (nodes[p].rson)
        sum += query(nodes[p].rson, a, b, c);
    return sum;
}

int main()
{
    scanf("%d%d", &n, &m);
    for (int i = 1; i <= n; i++)
        scanf("%lld%lld%lld", &nodes[i].d[0], &nodes[i].d[1], &nodes[i].val);
    groot = build(1, n);
    while (m--)
    {
        int a, b, c;
        scanf("%d%d%d", &a, &b, &c);
        printf("%lld\n", query(groot, a, b, c));
    }
    return 0;
}