// P3527.cpp
#include <bits/stdc++.h>
#define ll long long

using namespace std;

const int MAX_N = 3e5 + 200, INF = 0x3f3f3f3f;

int n, m, q, ans[MAX_N];
ll nodes[MAX_N << 1];
vector<int> G[MAX_N];

struct query
{
    int l, r, val, id;
} queries[MAX_N];

struct nation
{
    int demand, id;
} nations[MAX_N], tmp[MAX_N], ln[MAX_N], rn[MAX_N];

int read()
{
    int x = 0, f = 1;
    char ch = getchar();
    while (!isdigit(ch))
    {
        if (ch == '-')
            f = -1;
        ch = getchar();
    }
    while (isdigit(ch))
        x = (x << 3) + (x << 1) + ch - '0', ch = getchar();
    return x * f;
}

inline int lowbit(int x) { return x & (-x); }

void update(int qx, ll val)
{
    for (; qx <= (m << 1); qx += lowbit(qx))
        nodes[qx] += val;
}

ll query(int qx, ll ret = 0)
{
    for (; qx != 0; qx -= lowbit(qx))
        ret += nodes[qx];
    return ret;
}

void solve(int l, int r, int ql, int qr)
{
    if (ql > qr)
        return;
    if (l == r)
    {
        for (int i = ql; i <= qr; i++)
            ans[nations[i].id] = l;
        return;
    }
    int mid = (l + r) >> 1, lcnt = 0, rcnt = 0;
    for (int i = l; i <= mid; i++)
        update(queries[i].l, queries[i].val), update(queries[i].r + 1, -queries[i].val);
    for (int id = ql; id <= qr; id++)
    {
        ll res = 0;
        for (int i = 0, siz = G[nations[id].id].size(); i < siz; i++)
        {
            // printf("FUCK %d\n", G[nations[id].id][i]);
            res += query(G[nations[id].id][i]) + query(G[nations[id].id][i] + m);
            if (res >= nations[id].demand)
                break;
        }
        if (res >= nations[id].demand)
            ln[++lcnt] = nations[id];
        else
            rn[++rcnt] = nations[id], rn[rcnt].demand -= res;
    }
    for (int i = l; i <= mid; i++)
        update(queries[i].l, -queries[i].val), update(queries[i].r + 1, queries[i].val);
    for (int i = ql; i <= ql + lcnt - 1; i++)
        nations[i] = ln[i - ql + 1];
    for (int i = ql + lcnt; i <= ql + lcnt + rcnt - 1; i++)
        nations[i] = rn[i - ql - lcnt + 1];
    solve(l, mid, ql, ql + lcnt - 1), solve(mid + 1, r, ql + lcnt, qr);
}

int main()
{
    // freopen("testdata (5).in", "r", stdin);
    n = read(), m = read();
    for (int i = 1; i <= m; i++)
        G[read()].push_back(i);
    for (int i = 1; i <= n; i++)
        nations[i].demand = read(), nations[i].id = i;
    q = read();
    for (int i = 1; i <= q; i++)
        queries[i].l = read(), queries[i].r = read(), queries[i].val = read(), queries[i].r += ((queries[i].l > queries[i].r) ? m : 0);
    q++, queries[q].l = 1, queries[q].r = (m << 1), queries[q].val = INF, queries[q].id = q;
    solve(1, q, 1, n);
    for (int i = 1; i <= n; i++)
        if (ans[i] == q)
            puts("NIE");
        else
            printf("%d\n", ans[i]);
    return 0;
}