// P3372.cpp
#include <iostream>

using namespace std;

const int maxn = 100020;
#define ll long long
ll arr[maxn];
ll tree[maxn * 4];
ll lazy[maxn * 4];
ll n, m;

void build(int l, int r, int node)
{
    if (l == r)
        tree[node] = arr[l];
    else
    {
        int mid = (l + r) >> 1;
        build(l, mid, node * 2), build(mid + 1, r, node * 2 + 1);
        tree[node] = tree[node * 2] + tree[node * 2 + 1];
    }
}

ll sum(int ql, int qr, int l, int r, int node)
{
    if (ql <= l && r <= qr)
        return tree[node];
    ll ret = 0;
    int mid = (l + r) >> 1;
    if (l != r && lazy[node])
        tree[2 * node] += lazy[node] * (mid - l + 1),
            tree[2 * node + 1] += lazy[node] * (r - mid),
            lazy[2 * node] += lazy[node],
            lazy[2 * node + 1] += lazy[node];
    lazy[node] = 0;
    if (ql <= mid)
        ret += sum(ql, qr, l, mid, node * 2);
    if (qr > mid)
        ret += sum(ql, qr, mid + 1, r, node * 2 + 1);
    return ret;
}

void update(int ql, int qr, int c, int l, int r, int node)
{
    if (ql <= l && r <= qr)
    {
        tree[node] += c * (r - l + 1), lazy[node] += c;
        return;
    }
    ll mid = (l + r) >> 1;
    if (l != r && lazy[node])
        tree[2 * node] += lazy[node] * (mid - l + 1),
            tree[2 * node + 1] += lazy[node] * (r - mid),
            lazy[2 * node] += lazy[node],
            lazy[2 * node + 1] += lazy[node];
    lazy[node] = 0;
    if (ql <= mid)
        update(ql, qr, c, l, mid, 2 * node);
    if (qr > mid)
        update(ql, qr, c, mid + 1, r, 2 * node + 1);
    tree[node] = tree[node * 2] + tree[2 * node + 1];
}

int main()
{
    cin >> n >> m;
    for (int i = 1; i <= n; i++)
        cin >> arr[i];
    build(1, n, 1);
    for (int i = 0; i < m; i++)
    {
        ll opt, x, y, k;
        cin >> opt;
        switch (opt)
        {
        case 1:
            cin >> x >> y >> k;
            update(x, y, k, 1, n, 1);
            break;
        case 2:
            cin >> x >> y;
            cout << sum(x, y, 1, n, 1) << endl;
            break;
        }
    }
    return 0;
}