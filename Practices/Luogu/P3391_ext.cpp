// P3391_ext.cpp
#include <bits/stdc++.h>

using namespace std;

const int MAX_N = 1e5 + 200, INF = 0x3f3f3f3f;

int ch[MAX_N][2], fa[MAX_N], ptot, siz[MAX_N], root, val[MAX_N], n, m, seq[MAX_N];
bool tag[MAX_N];

int check(int x) { return ch[fa[x]][1] == x; }

void pushup(int p)
{
    siz[p] = siz[ch[p][0]] + siz[ch[p][1]] + 1;
}

void pushdown(int p)
{
    if (tag[p])
    {
        tag[ch[p][0]] ^= 1, tag[ch[p][1]] ^= 1;
        swap(ch[p][0], ch[p][1]);
        tag[p] = 0;
    }
}

void rotate(int x)
{
    int y = fa[x], z = fa[y], dir = check(x), w = ch[x][dir ^ 1];
    pushdown(y), pushdown(x);
    ch[y][dir] = w, fa[w] = y;
    ch[z][check(y)] = x, fa[x] = z;
    ch[x][dir ^ 1] = y, fa[y] = x;
    pushup(y), pushup(x);
}

void splay(int x, int goal = 0)
{
    while (fa[x] != goal)
    {
        int y = fa[x], z = fa[y];
        if (z != goal)
            rotate(check(x) == check(y) ? y : x);
        rotate(x);
    }
    if (goal == 0)
        root = x;
}

int kth(int k)
{
    int p = root;
    while (true)
    {
        pushdown(p);
        if (ch[p][0] && k <= siz[ch[p][0]])
            p = ch[p][0];
        else
        {
            k -= siz[ch[p][0]] + 1;
            if (k <= 0)
                return p;
            p = ch[p][1];
        }
    }
}

void rev(int l, int r)
{
    l = kth(l), r = kth(r + 2);
    splay(l), splay(r, l);
    tag[ch[ch[root][1]][0]] ^= 1;
}

void output(int p)
{
    pushdown(p);
    if (ch[p][0])
        output(ch[p][0]);
    if (val[p] <= n && val[p] >= 1)
        printf("%d ", val[p]);
    if (ch[p][1])
        output(ch[p][1]);
}

int build(int l, int r, int fat)
{
    if (l > r)
        return 0;
    int p = ++ptot, mid = (l + r) >> 1;
    fa[p] = fat, val[p] = seq[mid];
    ch[p][0] = build(l, mid - 1, p), ch[p][1] = build(mid + 1, r, p);
    pushup(p);
    return p;
}

int main()
{
    scanf("%d%d", &n, &m);
    for (int i = 1; i <= n; i++)
        seq[i + 1] = i;
    seq[1] = -INF, seq[n + 2] = INF;
    root = build(1, n + 2, 0);
    while (m--)
    {
        int l, r;
        scanf("%d%d", &l, &r), rev(l, r);
    }
    output(root);
    return 0;
}
