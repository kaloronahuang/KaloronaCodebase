// P2042.cpp
#include <bits/stdc++.h>
using namespace std;
const int MAX_N = 1e6 + 17, INF = 0x3f3f3f3f;
int n, m, root, ch[MAX_N][2], siz[MAX_N];
int sum[MAX_N], val[MAX_N], fa[MAX_N], tot;
int lft[MAX_N], rig[MAX_N], maxInt[MAX_N], id[MAX_N];
bool rev[MAX_N], tag[MAX_N];
bool check(int x) { return ch[fa[x]][1] == x; }
void update(int x)
{
    int l = ch[x][0], r = ch[x][1];
    siz[x] = siz[l] + siz[r] + 1;
    sum[x] = sum[l] + sum[r];
    maxInt[x] = max(maxInt[l], max(maxInt[r], rig[l] + val[x] + lft[r]));
    lft[x] = max(lft[l], sum[l] + val[x] + lft[r]);
    rig[x] = max(rig[r], sum[r] + rig[l] + val[x]);
}
void pushdown(int x)
{
    int l = ch[x][0], r = ch[x][1];
    if (tag[x])
    {
        rev[x] = tag[x] = false;
        if (l)
            tag[l] = 1, val[l] = val[x], sum[l] = val[l] * siz[l];
        if (r)
            tag[r] = 1, val[r] = val[x], sum[r] = val[r] * siz[r];
        if (val[x] >= 0)
        {
            if (l)
                lft[l] = rig[l] = maxInt[l] = sum[l];
            if (r)
                lft[r] = rig[r] = maxInt[r] = sum[r];
        }
        else if (l)
            lft[l] = rig[l] = 0, maxInt[l] = val[l];
        if (r)
            lft[r] = rig[r] = 0, maxInt[r] = val[r];
    }
    if (rev[x])
    {
        rev[x] = false, rev[l] ^= 1, rev[r] ^= 1;
        swap(lft[l], rig[l]), swap(rig[r], lft[r]);
        swap(ch[l][0], ch[l][1]), swap(ch[r][0], ch[r][1]);
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