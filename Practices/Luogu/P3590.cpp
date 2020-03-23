// P3590.cpp
#include <bits/stdc++.h>

using namespace std;

const int MAX_N = 1e6 + 200, INF = 0x3f3f3f3f;

int n, ans, ptot = 1;
char str[MAX_N];

struct node
{
    int lson, rson, max_val[2] = {-1, -1}, min_val[2] = {INF, INF};
} nodes[MAX_N * 3];

struct package
{
    int id, x, y, z;
    bool operator<(const package &rhs) const { return x < rhs.x; }
} pre[MAX_N], ai[MAX_N], bi[MAX_N];

int update(int qx, int l, int r, int p, package val)
{
    if (p == 0)
        p = ++ptot;
    if (nodes[p].min_val[0] > val.id)
    {
        if (nodes[p].min_val[0] != INF && bi[nodes[p].min_val[0]].id != val.z)
            nodes[p].min_val[1] = nodes[p].min_val[0];
        nodes[p].min_val[0] = val.id;
    }
    else if (nodes[p].min_val[1] > val.id && bi[nodes[p].min_val[0]].z != val.z)
        nodes[p].min_val[1] = val.id;
    if (nodes[p].max_val[0] < val.id)
    {
        if (nodes[p].max_val[0] != -1 && bi[nodes[p].max_val[0]].z != val.z)
            nodes[p].max_val[1] = nodes[p].max_val[0];
        nodes[p].max_val[0] = val.id;
    }
    else if (nodes[p].max_val[1] < val.id && bi[nodes[p].max_val[0]].z != val.z)
        nodes[p].max_val[1] = val.id;
    if (l == r)
        return p;
    int mid = (l + r) >> 1;
    if (qx <= mid)
        nodes[p].lson = update(qx, l, mid, nodes[p].lson, val);
    else
        nodes[p].rson = update(qx, mid + 1, r, nodes[p].rson, val);
    return p;
}

int query(int ql, int qr, int l, int r, int p, package val)
{
    if (p == 0)
        return 0;
    if (ql <= l && r <= qr)
    {
        int min_val, max_val;
        if (nodes[p].min_val[0] == INF)
            return 0;
        min_val = (val.z == bi[nodes[p].min_val[0]].z) ? nodes[p].min_val[1] : nodes[p].min_val[0];
        max_val = (val.z == bi[nodes[p].max_val[0]].z) ? nodes[p].max_val[1] : nodes[p].max_val[0];
        if (min_val == INF || max_val == -1)
            return 0;
        return max(abs(val.id - min_val), abs(val.id - max_val));
    }
    int mid = (l + r) >> 1, ret = 0;
    if (ql <= mid)
        ret = max(ret, query(ql, qr, l, mid, nodes[p].lson, val));
    if (mid < qr)
        ret = max(ret, query(ql, qr, mid + 1, r, nodes[p].rson, val));
    return ret;
}

int main()
{
    scanf("%d%s", &n, str);
    for (int i = 0, ptr = 0; i < n; i++)
    {
        if (str[i] != str[ptr])
            ptr = i;
        ans = max(ans, i - ptr + 1);
    }
    for (int i = 1; i <= n; i++)
    {
        pre[i] = pre[i - 1];
        if (str[i - 1] == 'C')
            pre[i].x++;
        if (str[i - 1] == 'B')
            pre[i].y++;
        if (str[i - 1] == 'S')
            pre[i].z++;
    }
    int lower = 0;
    for (int i = 1; i <= n; i++)
    {
        ai[i].x = pre[i].x - pre[i].y;
        ai[i].y = pre[i].x - pre[i].z;
        ai[i].z = pre[i].y - pre[i].z;
        lower = min(lower, min(ai[i].x, min(ai[i].y, ai[i].z)));
        ai[i].id = i;
    }
    n++;
    for (int i = 1; i <= n; i++)
        ai[i].x -= lower - 1, ai[i].y -= lower - 1, ai[i].z -= lower - 1;
    for (int i = 1; i <= n; i++)
        bi[i] = ai[i];
    bi[0] = bi[n], sort(ai + 1, ai + 1 + n);
    int domain = n - lower + 1;
    for (int i = 1, ptr = 1; i <= n; i++)
    {
        if (ai[i].x != ai[ptr].x)
            ptr = i;
        if (ai[i].x != ai[i + 1].x)
        {
            for (int j = ptr; j <= i; j++)
                ans = max(ans, max(query(1, ai[j].y - 1, 1, domain, 1, ai[j]), query(ai[j].y + 1, domain, 1, domain, 1, ai[j])));
            for (int j = ptr; j <= i; j++)
                update(ai[j].y, 1, domain, 1, ai[j]);
        }
    }
    printf("%d\n", ans);
    return 0;
}