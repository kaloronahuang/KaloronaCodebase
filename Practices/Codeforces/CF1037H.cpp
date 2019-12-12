// CF1037H.cpp
#include <bits/stdc++.h>

using namespace std;

const int MAX_N = 2e5 + 200;

int head[MAX_N], n, q, current, last_ptr = 1, ptot = 1;
int fa[MAX_N], stot, roots[MAX_N], nxt[MAX_N];
char str[MAX_N];

struct edge
{
    int to, nxt;
} edges[MAX_N << 1];

struct node
{
    int ch[26], link, len;
} nodes[MAX_N];

struct seg
{
    int lson, rson;
} tree[MAX_N * 20];

void addpath(int src, int dst)
{
    edges[current].to = dst, edges[current].nxt = head[src];
    head[src] = current++;
}

int update(int qx, int l, int r, int p)
{
    if (p == 0)
        p = ++stot;
    if (l == r)
        return p;
    int mid = (l + r) >> 1;
    if (qx <= mid)
        tree[p].lson = update(qx, l, mid, tree[p].lson);
    else
        tree[p].rson = update(qx, mid + 1, r, tree[p].rson);
    return p;
}

bool query(int ql, int qr, int l, int r, int p)
{
    if (p == 0)
        return false;
    if (ql <= l && r <= qr)
        return true;
    int mid = (l + r) >> 1;
    bool flag = false;
    if (ql <= mid)
        flag |= query(ql, qr, l, mid, tree[p].lson);
    if (mid < qr)
        flag |= query(ql, qr, mid + 1, r, tree[p].rson);
    return flag;
}

int merge(int x, int y, int l, int r)
{
    if (x == 0)
        return y;
    if (y == 0)
        return x;
    if (l == r)
        return x;
    int p = ++stot, mid = (l + r) >> 1;
    tree[p].lson = merge(tree[x].lson, tree[y].lson, l, mid);
    tree[p].rson = merge(tree[x].rson, tree[y].rson, mid + 1, r);
    return p;
}

void insert(int c)
{
    int pre = last_ptr, p = last_ptr = ++ptot;
    nodes[p].len = nodes[pre].len + 1;
    roots[p] = update(nodes[p].len, 1, n, roots[p]);
    for (; pre != 0 && nodes[pre].ch[c] == 0; pre = nodes[pre].link)
        nodes[pre].ch[c] = p;
    if (pre == 0)
        nodes[p].link = 1;
    else
    {
        int q = nodes[pre].ch[c];
        if (nodes[q].len == nodes[pre].len + 1)
            nodes[p].link = q;
        else
        {
            int clone = ++ptot;
            nodes[clone] = nodes[q];
            nodes[clone].len = nodes[pre].len + 1;
            nodes[p].link = nodes[q].link = clone;
            for (; nodes[pre].ch[c] == q; pre = nodes[pre].link)
                nodes[pre].ch[c] = clone;
        }
    }
}

void dfs(int u)
{
    for (int i = head[u]; i != -1; i = edges[i].nxt)
        dfs(edges[i].to), roots[u] = merge(roots[u], roots[edges[i].to], 1, n);
}

int main()
{
    memset(head, -1, sizeof(head));
    scanf("%s", str + 1), n = strlen(str + 1);
    for (int i = 1; i <= n; i++)
        insert(str[i] - 'a');
    for (int i = 2; i <= ptot; i++)
        addpath(fa[i] = nodes[i].link, i);
    dfs(1), scanf("%d", &q);
    while (q--)
    {
        static char T[MAX_N];
        int L, R, len, p = 1, i;
        scanf("%d%d%s", &L, &R, T + 1), len = strlen(T + 1);
        for (i = 1;; i++)
        {
            nxt[i] = -1;
            for (int digit = max(T[i] - 'a' + 1, 0); digit < 26; digit++)
                if (nodes[p].ch[digit] != 0 && query(L + i - 1, R, 1, n, roots[nodes[p].ch[digit]]))
                {
                    nxt[i] = digit;
                    break;
                }
            int np = nodes[p].ch[T[i] - 'a'];
            if (np == 0 || i == len + 1 || !query(L + i - 1, R, 1, n, roots[np]))
                break;
            p = np;
        }
        while (i && nxt[i] == -1)
            i--;
        if (i == 0)
            puts("-1");
        else
        {
            for (int j = 1; j < i; j++)
                putchar(T[j]);
            putchar(nxt[i] + 'a'), puts("");
        }
    }
    return 0;
}