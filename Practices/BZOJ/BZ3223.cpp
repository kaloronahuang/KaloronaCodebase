// BZ3223.cpp
#include <bits/stdc++.h>

using namespace std;

const int MAX_N = 100100, INF = 0x3f3f3f3f;

int ch[MAX_N][2], tag[MAX_N], fa[MAX_N], root, n, siz[MAX_N], q, seq[MAX_N], val[MAX_N], stot;

void pushdown(int p)
{
    if (tag[p])
    {
        tag[ch[p][0]] ^= 1, tag[ch[p][1]] ^= 1;
        swap(ch[p][0], ch[p][1]);
        tag[p] = 0;
    }
}

void pushup(int p) { siz[p] = siz[ch[p][0]] + siz[ch[p][1]] + 1; }

int check(int p) { return ch[fa[p]][1] == p; }

void rotate(int x)
{
    int dir = check(x), y = fa[x], z = fa[y], w = ch[x][dir ^ 1];
    pushdown(y), pushdown(x);
    ch[y][dir] = w, fa[w] = y;
    ch[x][dir ^ 1] = y, fa[y] = x;
    fa[x] = z;
    if (z)
        ch[z][ch[z][1] == y] = x;
    pushup(y), pushup(x);
}

void splay(int p, int target = 0)
{
    for (int f = fa[p]; (f = fa[p]) != target; rotate(p))
        if (fa[f] != target)
            rotate(check(p) == check(f) ? f : p);
    if (target == 0)
        root = p;
}

int build(int l, int r, int fat)
{
    if (l > r)
        return 0;
    int mid = (l + r) >> 1, p = ++stot;
    fa[p] = fat, val[p] = seq[mid];
    ch[p][0] = build(l, mid - 1, p), ch[p][1] = build(mid + 1, r, p);
    pushup(p);
    return p;
}

int find(int x)
{
    int p = root;
    while (true)
    {
        pushdown(p);
        if (ch[p][0] && x <= siz[ch[p][0]])
            p = ch[p][0];
        else
        {
            x -= siz[ch[p][0]] + 1;
            if (x <= 0)
                return p;
            p = ch[p][1];
        }
    }
}

void print(int p)
{
    pushdown(p);
    if (ch[p][0])
        print(ch[p][0]);
    if (val[p] != INF && val[p] != -INF)
        printf("%d ", val[p]);
    if (ch[p][1])
        print(ch[p][1]);
}

int main()
{
    scanf("%d%d", &n, &q);
    for (int i = 1; i <= n; i++)
        seq[i + 1] = i;
    seq[1] = -INF, seq[n + 2] = INF;
    root = build(1, n + 2, 0);
    while (q--)
    {
        int l, r;
        scanf("%d%d", &l, &r);
        l = find(l), splay(l);
        r = find(r + 2), splay(r, l);
        tag[ch[ch[root][1]][0]] ^= 1;
    }
    print(root);
    return 0;
}