// C.cpp
#include <bits/stdc++.h>

using namespace std;

const int MAX_N = 1e5 + 200;

struct node
{
    int lson, rson, sum;
} nodes[MAX_N * 100];

int n, m, q, roots[MAX_N], ptot, T, f;
vector<int> colors[MAX_N];
bool vis[2020];

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

bool warning = false;

int merge(int mA, int mB, int l, int r)
{
    if (mA == 0)
        return mB;
    if (mB == 0)
        return mA;
    int p = ++ptot;
    nodes[p].sum = 0, nodes[p].lson = 0, nodes[p].rson = 0;
    if (l == r)
    {
        nodes[p].sum = nodes[mA].sum + nodes[mB].sum;
        warning |= (nodes[p].sum > 1);
        return p;
    }
    nodes[p].lson = merge(nodes[mA].lson, nodes[mB].lson, l, mid);
    nodes[p].rson = merge(nodes[mA].rson, nodes[mB].rson, mid + 1, r);
    nodes[p].sum = nodes[nodes[p].lson].sum + nodes[nodes[p].rson].sum;
    return p;
}

int getBranch(int l, int r, int lft, int rig)
{
    int p = ++ptot;
    nodes[p].sum = nodes[rig].sum - nodes[lft].sum;
    if (l == r)
    {
        warning |= (nodes[p].sum > 1);
        return p;
    }
    nodes[p].lson = getBranch(l, mid, nodes[lft].lson, nodes[rig].lson);
    nodes[p].rson = getBranch(mid + 1, r, nodes[lft].rson, nodes[rig].rson);
    return p;
}

int main()
{
    scanf("%d%d", &T, &f);
    while (T--)
    {
        memset(roots, 0, sizeof(roots));
        scanf("%d%d%d", &n, &m, &q);
        for (int i = 1; i <= n; i++)
            colors[i].clear();
        for (int i = 1, x, y; i <= m; i++)
            scanf("%d%d", &x, &y), colors[x].push_back(i), colors[y].push_back(i);
        if (n <= 2000)
        {
            while (q--)
            {
                memset(vis, 0, sizeof(vis));
                warning = false;
                int k;
                scanf("%d", &k);
                while (k--)
                {
                    int l, r;
                    scanf("%d%d", &l, &r);
                    for (int i = l; i <= r && (!warning); i++)
                    {
                        for (int j = 0, siz = colors[i].size(); j < siz; j++)
                            if (vis[colors[i][j]] == true)
                            {
                                warning = true;
                                break;
                            }
                            else
                                vis[colors[i][j]] = true;
                    }
                }
                if (!warning)
                    putchar('0');
                else
                    putchar('1');
            }
            puts("");
            continue;
        }
        for (int i = 1; i <= n; i++)
        {
            if (colors[i].empty())
                roots[i] = roots[i - 1];
            while (!colors[i].empty())
            {
                int c = colors[i].back();
                colors[i].pop_back();
                roots[i] = update(c, 1, m, roots[i] == 0 ? roots[i - 1] : roots[i]);
            }
        }
        while (q--)
        {
            warning = false;
            int k, now_root = 0, pre_tot = ptot;
            scanf("%d", &k);
            while (k--)
            {
                int l, r, tmp;
                scanf("%d%d", &l, &r);
                if (warning)
                    continue;
                tmp = getBranch(1, m, roots[l - 1], roots[r]);
                if (warning)
                    continue;
                now_root = merge(now_root, tmp, 1, m);
                if (warning)
                    continue;
            }
            if (!warning)
                putchar('0');
            else
                putchar('1');
            ptot = pre_tot;
        }
        puts("");
    }
    return 0;
}
