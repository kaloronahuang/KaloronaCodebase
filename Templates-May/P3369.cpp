// P3369.cpp
#include <bits/stdc++.h>

using namespace std;

const int MAX_N = 1e5 + 200;

int q, ch[MAX_N][2], val[MAX_N], cnt[MAX_N], siz[MAX_N], fa[MAX_N], root, ptot;

#define lson (ch[p][0])
#define rson (ch[p][1])

// Splay;

int check(int p) { return ch[fa[p]][1] == p; }

void pushup(int p) { siz[p] = siz[lson] + siz[rson] + cnt[p]; }

void rotate(int x)
{
    int y = fa[x], z = fa[y], dir = check(x), w = ch[x][dir ^ 1];
    fa[x] = z;
    if (z)
        ch[z][check(y)] = x;
    fa[y] = x, ch[x][dir ^ 1] = y;
    fa[w] = y, ch[y][dir] = w;
    pushup(y), pushup(x);
}

void splay(int p, int goal = 0)
{
    if (p == 0)
        return;
    for (int fat = fa[p]; fat = fa[p], fat != goal; rotate(p))
        if (fa[fat] != goal)
            rotate(check(p) == check(fat) ? fat : p);
    if (goal == 0)
        root = p;
}

int find(int v)
{
    int p = root;
    while (p && val[p] != v && ch[p][v > val[p]])
        p = ch[p][v > val[p]];
    splay(p);
    return p;
}

void insert(int v)
{
    int p = root, pre = 0;
    while (p && val[p] != v)
        pre = p, p = ch[p][v > val[p]];
    if (p)
        cnt[p]++;
    else
    {
        p = ++ptot, val[p] = v, cnt[p] = siz[p] = 1;
        ch[p][0] = ch[p][1] = 0, fa[p] = pre;
        if (pre)
            ch[pre][v > val[pre]] = p;
    }
    splay(p);
}

int previous(int v)
{
    int p = find(v);
    if (val[p] < v)
        return p;
    p = lson;
    while (rson)
        p = rson;
    return p;
}

int succ(int v)
{
    int p = find(v);
    if (val[p] > v)
        return p;
    p = rson;
    while (lson)
        p = lson;
    return p;
}

void remove(int val)
{
    int pre = previous(val), suc = succ(val);
    splay(pre), splay(suc, pre);
    int p = ch[suc][0];
    cnt[p]--;
    if (cnt[p] == 0)
        ch[suc][0] = fa[p] = 0;
    else
        splay(p);
}

int getRank(int v)
{
    int p = find(v);
    return siz[lson] + 1;
}

int kth(int k)
{
    int p = root;
    if (siz[p] < k)
        return 0;
    while (true)
    {
        int lsiz = siz[lson];
        if (k <= lsiz)
            p = lson;
        else if (k <= lsiz + cnt[p])
            return val[p];
        else
            k -= lsiz + cnt[p], p = rson;
    }
}

int main()
{
    insert(-0x7fffffff), insert(0x7fffffff);
    scanf("%d", &q);
    while (q--)
    {
        int opt, x;
        scanf("%d%d", &opt, &x);
        if (opt == 1)
            insert(x);
        else if (opt == 2)
            remove(x);
        else if (opt == 3)
            printf("%d\n", getRank(x) - 1);
        else if (opt == 4)
            printf("%d\n", kth(x + 1));
        else if (opt == 5)
            printf("%d\n", val[previous(x)]);
        else
            printf("%d\n", val[succ(x)]);
    }
    return 0;
}