// P3168.cpp
#include <bits/stdc++.h>
#define ll long long
using namespace std;

const int MAX_N = 2e5 + 5, MAX_M = 5e6 + 5;

int head[MAX_N], current, roots[MAX_N], n, m, mxc;
struct edge
{
    int to, nxt;
} edges[MAX_M << 1];

struct node
{
    int siz, lson, rson;
    ll sum;
} nodes[MAX_M];
int treeTot;

void addpath(int src, int dst)
{
    edges[current].to = dst, edges[current].nxt = head[src];
    head[src] = current++;
}

int update(int l, int r, int pre, ll val)
{
    int p = ++treeTot;
    nodes[p] = nodes[pre], nodes[p].sum += val, nodes[p].siz += (val > 0) ? 1 : -1;
    if (l == r)
        return p;
    int mid = (l + r) >> 1;
    if (abs(val) <= mid)
        nodes[p].lson = update(l, mid, nodes[pre].lson, val);
    else
        nodes[p].rson = update(mid + 1, r, nodes[pre].rson, val);
    return p;
}

ll query(int l, int r, int p, int k)
{
    if (l == r)
        return l * k;
    int mid = (l + r) >> 1;
    if (k <= nodes[nodes[p].lson].siz)
        return query(l, mid, nodes[p].lson, k);
    else
        return query(mid + 1, r, nodes[p].rson, k - nodes[nodes[p].lson].siz) + nodes[nodes[p].lson].sum;
}

int main()
{
    memset(head, -1, sizeof(head));
    scanf("%d%d", &m, &n);
    for (int i = 1, a, b, c; i <= m; i++)
        scanf("%d%d%d", &a, &b, &c), addpath(a, c), addpath(b + 1, -c), mxc = max(mxc, c);
    for (int i = 1; i <= n; i++)
    {
        roots[i] = roots[i - 1];
        for (int e = head[i]; e != -1; e = edges[e].nxt)
            roots[i] = update(1, mxc, roots[i], edges[e].to);
    }
    int pre = 1;
    for (int i = 1; i <= n; i++)
    {
        int x, a, b, c, k;
        scanf("%d%d%d%d", &x, &a, &b, &c);
        k = 1 + ((ll)a * pre + b) % c;
        printf("%lld\n", pre = (nodes[roots[x]].siz <= k) ? nodes[roots[x]].sum : query(1, mxc, roots[x], k));
    }
    return 0;
}