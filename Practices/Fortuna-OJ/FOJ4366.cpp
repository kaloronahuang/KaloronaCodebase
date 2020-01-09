// FOJ4366.cpp
#include <bits/stdc++.h>

using namespace std;

const int MAX_N = 4e5 + 200;

int n, ai[MAX_N], nodes[MAX_N << 4];
char org[MAX_N], str[MAX_N];

#define lson (p << 1)
#define rson ((p << 1) | 1)
#define mid ((l + r) >> 1)

void update(int qx, int l, int r, int p, int val)
{
    if (l == r)
        return (void)(nodes[p] = val);
    if (qx <= mid)
        update(qx, l, mid, lson, val);
    else
        update(qx, mid + 1, r, rson, val);
    nodes[p] = max(nodes[lson], nodes[rson]);
}

int query(int ql, int qr, int l, int r, int p)
{
    if (ql <= l && r <= qr)
        return nodes[p];
    int ret = 0;
    if (ql <= mid)
        ret = max(ret, query(ql, qr, l, mid, lson));
    if (mid < qr)
        ret = max(ret, query(ql, qr, mid + 1, r, rson));
    return ret;
}

#undef mid
#undef rson
#undef lson

int main()
{
    scanf("%s", org + 1), n = strlen(org + 1);
    for (int i = 1; i <= n; i++)
        org[i + n] = org[i];
    str[0] = '?', str[1] = '#';
    for (int i = 1; i <= (n << 1); i++)
        str[i << 1] = org[i], str[(i << 1) | 1] = '#';
    str[(n << 2) + 2] = '!';
    int mid = 0;
    for (int i = 2, siz = (n << 2); i <= siz; i++)
    {
        if (i <= ai[mid] + mid)
            ai[i] = min(ai[mid] + mid - i, ai[(mid << 1) - i]);
        while (str[i + ai[i] + 1] == str[i - ai[i] - 1])
            ai[i]++;
        if (i + ai[i] > ai[mid] + mid)
            mid = i;
    }
    for (int i = 3; i <= n + 2; i++)
        update(i - ai[i], 1, (n << 2) + 1, 1, i);
    int ans = 0;
    for (int i = 2; i <= (n << 2); i++)
    {
        ans = max(ans, query(1, i + ai[i], 1, (n << 2) + 1, 1) - i);
        if (i + n + 1 <= (n << 2))
            update(i + n + 1 - ai[i + n + 1], 1, (n << 2) + 1, 1, i + n + 1);
    }
    printf("%d\n", ans);
    return 0;
}