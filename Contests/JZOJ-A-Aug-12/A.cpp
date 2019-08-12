// A.cpp
#pragma GCC optimize(3)
#include <bits/stdc++.h>
#define lson (p << 1)
#define rson ((p << 1) | 1)
#define mid ((l + r) >> 1)

using namespace std;

const int MAX_N = 2e5 + 1, INF = 0x3f3f3f3f;

int n, m, q, org[6][MAX_N];

struct node
{
    int mp[6][6];
} nodes[MAX_N << 2];

void pushup(node &p, node &ls, node &rs)
{
    memset(p.mp, 0x3f, sizeof(p.mp));
    for (int k = 1; k <= n; k++)
        for (int i = 1; i <= n; i++)
            for (int j = 1; j <= n; j++)
                p.mp[i][j] = min(p.mp[i][j], ls.mp[i][k] + rs.mp[k][j]);
    return;
}

void build(int l, int r, int p)
{
    memset(nodes[p].mp, 0x3f, sizeof(nodes[p].mp));
    if (l == r)
    {
        for (int i = 1; i <= n; i++)
            if (org[i][l])
                for (int j = i; j <= n; j++)
                    if (org[j][l])
                        nodes[p].mp[i][j] = nodes[p].mp[j][i] = j - i + 1;
                    else
                        break;
        return;
    }
    build(l, mid, lson), build(mid + 1, r, rson);
    pushup(nodes[p], nodes[lson], nodes[rson]);
}

void update(int qx, int l, int r, int p)
{
    memset(nodes[p].mp, 0x3f, sizeof(nodes[p].mp));
    if (l == r && l == qx)
    {
        for (int i = 1; i <= n; i++)
            if (org[i][l])
                for (int j = i; j <= n; j++)
                    if (org[j][l])
                        nodes[p].mp[i][j] = nodes[p].mp[j][i] = j - i + 1;
                    else
                        break;
        return;
    }
    if (qx <= mid)
        update(qx, l, mid, lson);
    else
        update(qx, mid + 1, r, rson);
    pushup(nodes[p], nodes[lson], nodes[rson]);
}

node query(int ql, int qr, int l, int r, int p)
{
    if (ql <= l && r <= qr)
        return nodes[p];
    if (qr <= mid)
        return query(ql, qr, l, mid, lson);
    if (mid < ql)
        return query(ql, qr, mid + 1, r, rson);
    node fa, lft = query(ql, qr, l, mid, lson), rgt = query(ql, qr, mid + 1, r, rson);
    pushup(fa, lft, rgt);
    return fa;
}

int main()
{
    scanf("%d%d%d", &n, &m, &q);
    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= m; j++)
            scanf("%d", &org[i][j]);
    build(1, m, 1);
    while (q--)
    {
        int opt, a, b, c, d;
        scanf("%d%d%d", &opt, &a, &b);
        if (opt == 1)
            org[a][b] ^= 1, update(b, 1, m, 1);
        else
        {
            scanf("%d%d", &c, &d);
            if (b > d)
                puts("-1");
            else
            {
                node nd = query(b, d, 1, m, 1);
                if (nd.mp[a][c] == INF)
                    puts("-1");
                else
                    printf("%d\n", nd.mp[a][c] - 1);
            }
        }
    }
    return 0;
}