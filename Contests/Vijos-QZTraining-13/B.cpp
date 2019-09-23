// B.cpp
#include <bits/stdc++.h>
#define pr pair<double, int>
using namespace std;

const int MAX_N = 500100;

int n;
double D, C, d0, nodes[MAX_N << 2], tag[MAX_N << 2], di[MAX_N], pi[MAX_N], segs[MAX_N];

#define lson (p << 1)
#define rson ((p << 1) | 1)
#define mid ((l + r) >> 1)

void pushdown(int p)
{
    if (tag[p] != 0)
    {
        nodes[lson] += tag[p], nodes[rson] += tag[p];
        tag[lson] += tag[p], tag[rson] += tag[p];
        tag[p] = 0;
    }
}

void pushup(int p)
{
    nodes[p] = nodes[lson] + nodes[rson];
}

void update(int ql, int qr, int l, int r, int p, double val)
{
    if (ql <= l && r <= qr)
        return (void)(nodes[p] += val, tag[p] += val);
    pushdown(p);
    if (ql <= mid)
        update(ql, qr, l, mid, lson, val);
    if (mid < qr)
        update(ql, qr, mid + 1, r, rson, val);
    pushup(p);
}

double query(int ql, int qr, int l, int r, int p)
{
    if (ql <= l && r <= qr)
        return nodes[p];
    double ret = 0;
    if (ql <= mid)
        ret = max(ret, query(ql, qr, l, mid, lson));
    if (mid < qr)
        ret = max(ret, query(ql, qr, mid + 1, r, rson));
    return ret;
}

#undef lson
#undef rson
#undef mid

int main()
{
    scanf("%d%lf%lf%lf", &n, &D, &C, &d0);
    for (int i = 1; i <= n; i++)
        scanf("%lf%lf", &di[i], &pi[i]);
    for (int i = 1; i <= n - 1; i++)
        segs[i] = di[i + 1] - di[i];
    segs[n] = D - di[n];
    priority_queue<pr> pq;
    int lastpos = 0;
    double ans = 0;
    for (int i = 1; i <= n; i++)
    {
        pq.push(make_pair(-pi[i], i));
        double need = segs[i] / d0;
        while (need > 0)
        {
            if (pq.empty())
                puts("Poor Congcong"), exit(0);
            int pos = pq.top().second;
            if (pos <= lastpos)
            {
                pq.pop();
                continue;
            }
            double lft = C - query(pos, i, 1, n, 1);
            if (lft <= 0)
            {
                pq.pop();
                break;
            }
            if (need - lft <= 0)
            {
                ans += need * pi[pos];
                update(pos, i, 1, n, 1, need);
                need = 0;
            }
            else
            {
                ans += lft * pi[pos];
                need -= lft, update(pos, i, 1, n, 1, lft);
                lastpos = max(lastpos, pos);
                pq.pop();
            }
        }
    }
    printf("%.2lf", ans);
    return 0;
}