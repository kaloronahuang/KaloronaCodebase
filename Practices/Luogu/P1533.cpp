// P1533.cpp
#include <bits/stdc++.h>

using namespace std;

const int MAX_N = 500100;

struct node
{
    int sum, lson, rson;
} nodes[MAX_N * 20];

int n, m, ai[MAX_N], roots[MAX_N], ptot;
vector<int> mp;

#define mid ((l + r) >> 1)

int update(int qx, int l, int r, int pre)
{
    int p = ++ptot;
    nodes[p] = nodes[pre];
    nodes[p].sum++;
    if (l == r)
        return p;
    if (qx <= mid)
        nodes[p].lson = update(qx, l, mid, nodes[pre].lson);
    else
        nodes[p].rson = update(qx, mid + 1, r, nodes[pre].rson);
    return p;
}

int query(int k, int l, int r, int lft, int rig)
{
    if (l == r)
        return l;
    int lval = nodes[nodes[rig].lson].sum - nodes[nodes[lft].lson].sum;
    if (k <= lval)
        return query(k, l, mid, nodes[lft].lson, nodes[rig].lson);
    else
        return query(k - lval, mid + 1, r, nodes[lft].rson, nodes[rig].rson);
}

int main()
{
    scanf("%d%d", &n, &m);
    for (int i = 1; i <= n; i++)
        scanf("%d", &ai[i]), mp.push_back(ai[i]);
    sort(mp.begin(), mp.end());
    mp.erase(unique(mp.begin(), mp.end()), mp.end());
    for (int i = 1; i <= n; i++)
        roots[i] = update(lower_bound(mp.begin(), mp.end(), ai[i]) - mp.begin() + 1, 1, mp.size(), roots[i - 1]);
    while (m--)
    {
        int l, r, k;
        scanf("%d%d%d", &l, &r, &k);
        printf("%d\n", mp[query(k, 1, mp.size(), roots[l - 1], roots[r]) - 1]);
    }
    return 0;
}