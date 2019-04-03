// P2042.cpp
#include <bits/stdc++.h>
using namespace std;
const int MAX_N = 20100;
int ch[MAX_N][2], fa[MAX_N], val[MAX_N], siz[MAX_N], cnt[MAX_N], sum[MAX_N], maxVal[MAX_N], root, tot;
int check(int x) { return ch[fa[x]][1] == x ? 1 : 0; }
void pushup(int x)
{
    siz[x] = siz[ch[x][0]] + siz[ch[x][1]] + cnt[x];
}
void rotate(int x)
{
    int y = fa[x], z = fa[y], w = ch[x][check(x) ^ 1], k = check(x);
    ch[y][k] = w, fa[w] = y;
    ch[z][check(y)] = x, fa[x] = z;
    ch[x][k ^ 1] = y, fa[y] = x;
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
    if (!goal)
        root = x;
}
void find(int x)
{
    if (!root)
        return;
    int cur = root;
    while (ch[cur][x > val[cur]] && x != val[cur])
        cur = ch[cur][x > val[cur]];
    splay(cur);
}
void insert(int x)
{
    int p = root, cur = 0;
    while (p && val[p] != x)
        cur = p, p = ch[p][x > val[p]];
    if (p)
        val[p]++;
    else
    {
        p = ++tot;
        if (cur)
            ch[cur][x > val[cur]] = p;
        ch[p][0] = ch[p][1] = 0;
        val[p] = x, fa[p] = cur;
        cnt[p] = siz[p] = 1;
    }
    splay(p);
}
void remove(int x)
{
}
int main()
{
    return 0;
}