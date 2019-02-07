// P2042.cpp
#include <bits/stdc++.h>
using namespace std;
const int MAX_N = 5e6, INF = 0x3f3f3f3f;
int n, m, root, ch[MAX_N][2], siz[MAX_N], val[MAX_N], fa[MAX_N], tot;
bool rev[MAX_N];
bool check(int x) { return ch[fa[x]][1] == x; }
void update(int x) { siz[x] = siz[ch[x][0]] + siz[ch[x][1]] + 1; }
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
    int y = fa[x], z = fa[y], dirx = check(x), b = ch[x][dirx ^ 1];
    ch[y][dirx] = b, fa[b] = y;
    ch[z][check(y)] = x, fa[x] = z;
    ch[x][dirx ^ 1] = y, fa[y] = x;
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
int main()
{
    return 0;
}