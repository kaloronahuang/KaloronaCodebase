// luogu-judger-enable-o2
// P2596.cpp
#include <bits/stdc++.h>
using namespace std;
const int MAX_N = 160800;
int ch[MAX_N][2], siz[MAX_N], fa[MAX_N], val[MAX_N], pos[MAX_N], tot;
int root;
char opt[20];

int check(int x) { return ch[fa[x]][1] == x; }

void pushup(int x)
{
    siz[x] = siz[ch[x][0]] + siz[ch[x][1]] + 1;
    pos[val[ch[x][0]]] = ch[x][0], pos[val[ch[x][1]]] = ch[x][1];
}

void rotate(int x)
{
    int y = fa[x], z = fa[y], dir = check(x), w = ch[x][dir ^ 1];
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
            if (check(x) == check(y))
                rotate(y);
            else
                rotate(x);
        rotate(x);
    }
    pos[val[x]] = x;
    if (!goal)
        root = x;
}

void insert(int x)
{
    val[++tot] = x, siz[tot] = 1, pos[x] = tot;
    ch[tot][0] = ch[tot][1] = 0;
    if (tot > 1)
    {
        ch[tot - 1][1] = tot, fa[tot] = tot - 1;
        splay(tot);
    }
}

int find(int x, int k)
{
    int y = ch[x][0];
    if (siz[y] + 1 == k)
        return x;
    else if (siz[y] >= k)
        return find(y, k);
    else
        return find(ch[x][1], k - siz[y] - 1);
}

void top(int x)
{
    x = pos[x];
    splay(x);
    if (ch[x][0] == 0)
        return;
    if (ch[x][1] == 0)
        ch[x][1] = ch[x][0], ch[x][0] = 0;
    else
    {
        int y = find(root, siz[ch[x][0]] + 2);
        fa[ch[root][0]] = y;
        ch[y][0] = ch[root][0];
        ch[root][0] = 0;
        splay(y);
    }
}

void bottom(int x)
{
    x = pos[x];
    splay(x);
    if (ch[x][1] == 0)
        return;
    if (ch[x][0] == 0)
        ch[x][0] = ch[x][1], ch[x][1] = 0;
    else
    {
        int y = find(root, siz[ch[x][0]]);
        fa[ch[root][1]] = y;
        ch[y][1] = ch[root][1];
        ch[root][1] = 0;
        splay(y);
    }
}

void ins(int x, int d)
{
    if (d == 0)
        return;
    splay(pos[x]);
    int y = find(root, d == 1 ? siz[ch[pos[x]][0]] + 2 : siz[ch[pos[x]][0]]);
    int x1 = val[y], x2 = pos[x];
    swap(pos[x], pos[x1]);
    swap(val[x2], val[y]);
}

int main()
{
    int n, m, tmpx, tmpy;
    scanf("%d%d", &n, &m);
    root = 1;
    for (int i = 1; i <= n; i++)
        scanf("%d", &tmpx), insert(tmpx);
    while (m--)
    {
        scanf("%s", opt);
        switch (opt[0])
        {
        case 'T':
            scanf("%d", &tmpx), top(tmpx);
            break;
        case 'B':
            scanf("%d", &tmpx), bottom(tmpx);
            break;
        case 'I':
            scanf("%d%d", &tmpx, &tmpy), ins(tmpx, tmpy);
            break;
        case 'A':
            scanf("%d", &tmpx);
            splay(pos[tmpx]), printf("%d\n", siz[ch[pos[tmpx]][0]]);
            break;
        case 'Q':
            scanf("%d", &tmpx);
            printf("%d\n", val[find(root, tmpx)]);
            break;
        }
    }
    return 0;
}