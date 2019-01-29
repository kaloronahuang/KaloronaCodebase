// P3391.cpp
#include <iostream>
#include <cstdio>
#include <cstring>
using namespace std;
const int MAX_N = 100200;
int n, m, ch[MAX_N][2], val[MAX_N], cnt[MAX_N], fa[MAX_N], siz[MAX_N], root, tot, rev[MAX_N], tmpx, tmpy;
bool check(int x) { return ch[fa[x]][1] == x; }
void update(int x) { siz[x] = siz[ch[x][0]] + siz[ch[x][1]] + cnt[x]; }
void pushdown(int x)
{
    if (rev[x])
    {
        swap(ch[x][0], ch[x][1]);
        rev[ch[x][0]] ^= 1, rev[ch[x][1]] ^= 1;
        rev[x] = 0;
    }
}
void rotate(int x)
{
    int y = fa[x], z = fa[y], dir = check(x), w = ch[x][dir ^ 1];
    ch[y][dir] = w, fa[w] = y;
    ch[z][check(y)] = x, fa[x] = z;
    ch[x][dir ^ 1] = y, fa[y] = x;
    update(y), update(x);
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
    if (!goal)
        root = x;
}
void insert(int x)
{
    int cur = root, p = 0;
    while (cur && val[cur] != x)
        p = cur, cur = ch[cur][x > val[cur]];
    if (cur)
        cnt[cur]++;
    else
    {
        cur = ++tot;
        if (p)
            ch[p][x > val[p]] = cur;
        ch[cur][0] = ch[cur][1] = 0;
        val[cur] = x, fa[cur] = p;
        cnt[cur] = siz[cur] = 1;
    }
    splay(cur);
}
int kth(int k)
{
    int cur = root;
    while (true)
    {
        pushdown(cur);
        if (ch[cur][0] && k <= siz[ch[cur][0]])
            cur = ch[cur][0];
        else if (k > siz[ch[cur][0]] + cnt[cur])
            k -= siz[ch[cur][0]] + cnt[cur], cur = ch[cur][1];
        else
            return cur;
    }
}
void reverse(int l, int r)
{
    int x = kth(l), y = kth(r + 2);
    splay(x), splay(y, x);
    rev[ch[y][0]] ^= 1;
}
void output(int x)
{
    pushdown(x);
    if (ch[x][0])
        output(ch[x][0]);
    if (val[x] && val[x] <= n)
        printf("%d ", val[x]);
    if (ch[x][1])
        output(ch[x][1]);
}
int main()
{
    scanf("%d%d", &n, &m);
    for (int i = 0; i <= n + 1; i++)
        insert(i);
    while (m--)
        scanf("%d%d", &tmpx, &tmpy), reverse(tmpx, tmpy);
    output(root);
    return 0;
}