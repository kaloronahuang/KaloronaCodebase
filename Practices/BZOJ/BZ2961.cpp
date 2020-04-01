// BZ2961.cpp
#include <bits/stdc++.h>

using namespace std;

const int MAX_N = 500100;
const double eps = 1e-8;

int n, utail, ltail;
bool ans[MAX_N], pos[MAX_N];

struct node
{
    int typ, id;
    double x, y, k;
    bool operator<(const node &rhs) const { return k < rhs.k; }
} nodes[MAX_N], tmp[MAX_N], upper[MAX_N], lower[MAX_N];

double slope(node &a, node &b)
{
    if (fabs(a.x - b.x) < eps)
        return a.y < b.y ? 1e18 : -1e18;
    return (a.y - b.y) / (a.x - b.x);
}

double getDist(node &a, node &b) { return sqrt((a.x - b.x) * (a.x - b.x) + (a.y - b.y) * (a.y - b.y)); }

void solve(int l, int r)
{
    if (l == r)
        return;
    int mid = (l + r) >> 1, lptr = l, rptr = mid + 1;
    for (int i = l; i <= r; i++)
        if (nodes[i].id <= mid)
            tmp[lptr++] = nodes[i];
        else
            tmp[rptr++] = nodes[i];
    for (int i = l; i <= r; i++)
        nodes[i] = tmp[i];
    solve(l, mid);
    utail = ltail = 0;
    for (int i = l; i <= mid; i++)
        if (nodes[i].typ == 0)
        {
            while (utail > 1 && slope(upper[utail - 1], nodes[i]) + eps > slope(upper[utail - 1], upper[utail]))
                utail--;
            while (ltail > 1 && slope(lower[ltail - 1], nodes[i]) - eps < slope(lower[ltail - 1], lower[ltail]))
                ltail--;
            upper[++utail] = nodes[i], lower[++ltail] = nodes[i];
        }
    lptr = utail, rptr = 1;
    for (int i = mid + 1; i <= r; i++)
        if (nodes[i].typ == 1)
            if (nodes[i].y < 0)
            {
                while (lptr > 1 && slope(upper[lptr - 1], upper[lptr]) < nodes[i].k)
                    lptr--;
                if (lptr >= 1 && getDist(upper[0], upper[lptr]) < getDist(upper[lptr], nodes[i]))
                    ans[nodes[i].id] = false;
            }
            else
            {
                while (rptr < ltail && slope(lower[rptr], lower[rptr + 1]) < nodes[i].k)
                    rptr++;
                if (rptr <= ltail && getDist(lower[0], lower[rptr]) < getDist(lower[rptr], nodes[i]))
                    ans[nodes[i].id] = false;
            }
    solve(mid + 1, r);
    lptr = l, rptr = mid + 1;
    int cur = l;
    while (lptr <= mid && rptr <= r)
        if (nodes[lptr].x < nodes[rptr].x || (fabs(nodes[lptr].x - nodes[rptr].x) < eps && nodes[lptr].y < nodes[rptr].y))
            tmp[cur++] = nodes[lptr++];
        else
            tmp[cur++] = nodes[rptr++];
    while (lptr <= mid)
        tmp[cur++] = nodes[lptr++];
    while (rptr <= r)
        tmp[cur++] = nodes[rptr++];
    for (int i = l; i <= r; i++)
        nodes[i] = tmp[i];
}

int main()
{
    scanf("%d", &n);
    bool flag = false;
    for (int i = 1; i <= n; i++)
    {
        scanf("%d%lf%lf", &nodes[i].typ, &nodes[i].x, &nodes[i].y);
        nodes[i].id = i;
        if (nodes[i].typ == 1)
            pos[i] = true, ans[i] = flag;
        else
            flag = true;
        nodes[i].k = fabs(nodes[i].y) < eps ? 1e18 : -nodes[i].x / nodes[i].y;
    }
    sort(nodes + 1, nodes + 1 + n);
    solve(1, n);
    for (int i = 1; i <= n; i++)
        if (pos[i])
            puts(ans[i] ? "Yes" : "No");
    return 0;
}