// P4027.cpp
#include <bits/stdc++.h>

using namespace std;

const int MAX_N = 1e5 + 200;
const double eps = 1e-7;

int n, q[MAX_N], top;
double SA[MAX_N], SB[MAX_N], rate[MAX_N], f[MAX_N];

struct node
{
    double x, y;
    int id;
} nodes[MAX_N], tmp[MAX_N];

double slope(int i, int j)
{
    if (fabs(nodes[i].x - nodes[j].x) < eps)
        return 1e-15;
    return (nodes[i].y - nodes[j].y) / (nodes[i].x - nodes[j].x);
}

double calc(int i, int j)
{
    double VB = f[j] / (rate[j] * SA[j] + SB[j]);
    return SA[i] * VB * rate[j] + SB[i] * VB;
}

int binary_search(double k)
{
    int l = 1, r = top - 1, res = top;
    while (l <= r)
    {
        int mid = (l + r) >> 1;
        if (slope(q[mid], q[mid + 1]) <= k)
            res = mid, r = mid - 1;
        else
            l = mid + 1;
    }
    return q[res];
}

void solve(int l, int r)
{
    if (l == r)
    {
        f[l] = max(f[l], f[l - 1]), nodes[l].id = l;
        nodes[l].y = f[l] / (rate[l] * SA[l] + SB[l]);
        nodes[l].x = nodes[l].y * rate[l];
        return;
    }
    int mid = (l + r) >> 1;
    solve(l, mid), top = 0;
    for (int i = l; i <= mid; i++)
    {
        while (top > 1 && slope(q[top - 1], q[top]) <= slope(q[top - 1], i))
            top--;
        q[++top] = i;
    }
    for (int i = mid + 1; i <= r; i++)
        f[i] = max(f[i], calc(i, nodes[binary_search(-SA[i] / SB[i])].id));
    solve(mid + 1, r);
    int lptr = l, rptr = mid + 1, ptr = l;
    while (lptr <= mid && rptr <= r)
        if (nodes[lptr].x < nodes[rptr].x || (fabs(nodes[lptr].x - nodes[rptr].x) < 1e-9 && nodes[lptr].y < nodes[rptr].y))
            tmp[ptr] = nodes[lptr], lptr++, ptr++;
        else
            tmp[ptr] = nodes[rptr], rptr++, ptr++;
    while (lptr <= mid)
        tmp[ptr] = nodes[lptr], lptr++, ptr++;
    while (rptr <= r)
        tmp[ptr] = nodes[rptr], rptr++, ptr++;
    for (int i = l; i <= r; i++)
        nodes[i] = tmp[i];
}

int main()
{
    scanf("%d%lf", &n, &f[0]);
    for (int i = 1; i <= n; i++)
        scanf("%lf%lf%lf", &SA[i], &SB[i], &rate[i]), f[i] = f[0];
    solve(1, n), printf("%.10lf\n", f[n]);
    return 0;
}