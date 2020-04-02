// BZ2212.cpp
#include <bits/stdc++.h>

using namespace std;

const int MAX_N = 2e5 + 200;

int n, ptot;
long long answer, ans1, ans2;

struct node
{
    int sum, lson, rson;
} nodes[MAX_N * 30];

int update(int qx, int l, int r, int p)
{
    if (p == 0)
        p = ++ptot;
    nodes[p].sum++;
    int mid = (l + r) >> 1;
    if (l == r)
        return p;
    if (qx <= mid)
        nodes[p].lson = update(qx, l, mid, nodes[p].lson);
    else
        nodes[p].rson = update(qx, mid + 1, r, nodes[p].rson);
    return p;
}

int merge(int x, int y)
{
    if (x == 0)
        return y;
    if (y == 0)
        return x;
    ans1 += 1LL * nodes[nodes[x].rson].sum * nodes[nodes[y].lson].sum;
    ans2 += 1LL * nodes[nodes[x].lson].sum * nodes[nodes[y].rson].sum;
    nodes[x].sum += nodes[y].sum;
    nodes[x].lson = merge(nodes[x].lson, nodes[y].lson);
    nodes[x].rson = merge(nodes[x].rson, nodes[y].rson);
    return x;
}

int read()
{
    int opt;
    scanf("%d", &opt);
    if (opt != 0)
        return update(opt, 1, n, 0);
    else
    {
        int ls = read(), rs = read();
        ans1 = ans2 = 0;
        int p = merge(ls, rs);
        answer += min(ans1, ans2);
        return p;
    }
}

int main()
{
    scanf("%d", &n), read();
    printf("%lld", answer);
    return 0;
}