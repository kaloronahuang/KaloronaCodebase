// C.cpp
#include <bits/stdc++.h>
#define ll long long
using namespace std;

const int MAX_N = 1e5 + 2000;
int head[MAX_N], current, value[MAX_N], limit[MAX_N], n, mi[MAX_N], mx[MAX_N];
int tmpx, tmpy, tmpz, tot, point_tot, roots[MAX_N], curt_root;
ll answer = 0;
bool modify[MAX_N << 2];
vector<int> vec;
struct edge
{
    int to, nxt;
} edges[MAX_N];
struct node
{
    int l, r, lson, rson;
    ll sum;
} nodes[MAX_N * 40];

int build(int l, int r)
{
    int p = ++tot;
    nodes[p].l = l, nodes[p].r = r;
    if (l == r)
        return p;
    int mid = (l + r) >> 1;
    nodes[p].lson = build(l, mid), nodes[p].rson = build(mid + 1, r);
    return p;
}

int update(int qx, int p_prev, int val)
{
    int p = ++tot;
    nodes[p].l = nodes[p_prev].l, nodes[p].r = nodes[p_prev].r;
    nodes[p].lson = nodes[p_prev].lson, nodes[p].rson = nodes[p_prev].rson;
    nodes[p].sum += nodes[p_prev].sum + val;
    int mid = (nodes[p].l + nodes[p].r) >> 1;
    if (nodes[p].l == nodes[p].r && nodes[p].r == qx)
        return p;
    if (qx <= mid)
        nodes[p].lson = update(qx, nodes[p_prev].lson, val);
    else
        nodes[p].rson = update(qx, nodes[p_prev].rson, val);
    return p;
}

ll query(int ql, int qr, int p)
{
    if (ql <= nodes[p].l && nodes[p].r <= qr)
        return nodes[p].sum;
    int mid = (nodes[p].l + nodes[p].r) >> 1;
    ll ans = 0;
    if (ql <= mid)
        ans += query(ql, qr, nodes[p].lson);
    if (mid < qr)
        ans += query(ql, qr, nodes[p].rson);
    return ans;
}

void addpath(int src, int dst)
{
    edges[current].to = dst, edges[current].nxt = head[src];
    head[src] = current++;
}

void dfs(int u)
{
    int st = point_tot;
    for (int i = head[u]; i != -1; i = edges[i].nxt)
        dfs(edges[i].to);
    int p = ++point_tot;
    roots[p] = update(limit[u], roots[p - 1], value[u]);
    answer = max(answer, query(1, limit[u], roots[p]) - query(1, limit[u], roots[st]));
}

int main()
{
    memset(head, -1, sizeof(head));
    scanf("%d", &n);
    for (int i = 1; i <= n; i++)
        scanf("%d%d%d", &tmpx, &tmpy, &tmpz), value[i] = tmpz, limit[i] = min(tmpx, tmpy), vec.push_back(limit[i]);
    for (int i = 1; i <= n - 1; i++)
        scanf("%d%d", &tmpx, &tmpy), addpath(tmpx, tmpy);
    sort(vec.begin(), vec.end());
    vec.erase(unique(vec.begin(), vec.end()), vec.end());
    for (int i = 1; i <= n; i++)
        limit[i] = lower_bound(vec.begin(), vec.end(), limit[i]) - vec.begin() + 1;
    roots[0] = build(1, n);
    dfs(1);
    printf("%lld", answer);
    return 0;
}