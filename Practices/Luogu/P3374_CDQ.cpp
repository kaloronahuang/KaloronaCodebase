// P3374_CDQ.cpp
#include <bits/stdc++.h>
using namespace std;

const int MAX_N = 2300000;

struct opt
{
    int type, l, r, ans, id;
    bool operator<(const opt &op) const { return l < op.l || (l == op.l && type < op.type); }
} opts[MAX_N], b[MAX_N];
int n, m, q, anses[MAX_N], tmp[MAX_N], qID, tmpx, tmpy;

void cdq(int l, int r)
{
    if (l == r)
        return;
    int mid = (l + r) >> 1;
    cdq(l, mid), cdq(mid + 1, r);
    int lptr = l, rptr = mid + 1, sum = 0;
    for (int i = l; i <= r; i++)
        if ((lptr <= mid && opts[lptr] < opts[rptr]) || rptr > r)
        {
            if (opts[lptr].type == 1)
                sum += opts[lptr].r;
            b[i] = opts[lptr++];
        }
        else
        {
            if (opts[rptr].type == 2)
                anses[opts[rptr].id] -= sum;
            if (opts[rptr].type == 3)
                anses[opts[rptr].id] += sum;
            b[i] = opts[rptr++];
        }
    for (int i = l; i <= r; i++)
        opts[i] = b[i];
}

int main()
{
    scanf("%d%d", &n, &m);
    for (int i = 1; i <= n; i++)
    {
        int id = ++q;
        opts[id].type = 1, opts[id].l = i;
        scanf("%d", &opts[id].r);
    }
    for (int i = 1; i <= m; i++)
    {
        scanf("%d", &opts[++q].type);
        if (opts[q].type == 1)
            scanf("%d%d", &opts[q].l, &opts[q].r), opts[q].type = 1;
        else
        {
            scanf("%d%d", &tmpx, &tmpy);
            opts[q].id = ++qID, opts[q].l = tmpx - 1, opts[q].type = 2;
            opts[++q].id = qID, opts[q].l = tmpy, opts[q].type = 3;
        }
    }
    cdq(1, q);
    for (int i = 1; i <= qID; i++)
        printf("%d\n", anses[i]);
    return 0;
}