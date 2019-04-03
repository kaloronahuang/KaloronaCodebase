// P2234.cpp
#include <bits/stdc++.h>
using namespace std;
const int MAX_N = 33767;
int n, val[MAX_N], ch[MAX_N][2], cnt[MAX_N], siz[MAX_N], fa[MAX_N], root, tot;
int check(int x) { return ch[fa[x]][1] == x; }
void pushup(int x)
{
    siz[x] = siz[ch[x][0]] + siz[ch[x][1]] + cnt[x];
}
void rotate(int x)
{
    int y = fa[x], z = fa[y], k = check(x), w = ch[x][k ^ 1];
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
        ch[cur][0] = ch[cur][1] = 0, fa[cur] = p;
        val[cur] = x, siz[cur] = cnt[cur] = 1;
    }
    splay(cur);
}
int pre(int x)
{
    find(x);
    if (val[root] <= x)
        return root;
    int cur = ch[root][0];
    while (ch[cur][1])
        cur = ch[cur][1];
    return cur;
}
int succ(int x)
{
    find(x);
    if (val[root] >= x)
        return root;
    int cur = ch[root][1];
    while (ch[cur][0])
        cur = ch[cur][0];
    return cur;
}
int main()
{
    scanf("%d", &n);
    insert(0x3f3f3f3f);
    insert(0xcfcfcfcf);
    int ans;
    scanf("%d", &ans), n--;
    insert(ans);
    for (int i = 1; i <= n; i++)
    {
        int x;
        scanf("%d", &x);
        int suc = succ(x), prv = pre(x);
        insert(x);
        ans += min(abs(val[suc] - x), abs(val[prv] - x));
    }
    printf("%d", ans);
    return 0;
}