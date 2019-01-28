// P3369.cpp
#include <iostream>
#include <algorithm>
#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <ctime>
using namespace std;
const int MAX_N = 100020;
int ch[MAX_N][2], key[MAX_N], val[MAX_N], siz[MAX_N], tot, root;
void update(int x) { siz[x] = siz[ch[x][0]] + siz[ch[x][1]] + 1; }
void rotate(int &u, int dir)
{
    int t = ch[u][dir];
    ch[u][dir] = ch[t][!dir], ch[t][!dir] = u;
    update(u), update(t), u = t;
}
void insert(int x, int &u)
{
    if (u == 0)
    {
        u = ++tot;
        val[u] = x, siz[u] = 1, key[u] = rand();
        return;
    }
    siz[u]++;
    if (x <= val[u])
    {
        insert(x, ch[u][0]);
        if (key[ch[u][0]] < key[u])
            rotate(u, 0);
    }
    else
    {
        insert(x, ch[u][1]);
        if (key[ch[u][1]] < key[u])
            rotate(u, 1);
    }
    update(u);
}
void remove(int x, int &u)
{
    if (val[u] == x)
    {
        if (ch[u][0] * ch[u][1] == 0)
        {
            u = ch[u][0] + ch[u][1];
            return;
        }
        if (key[ch[u][0]] > key[ch[u][1]])
            rotate(u, 1), remove(x, ch[u][0]);
        else
            rotate(u, 0), remove(x, ch[u][1]);
    }
    else if (val[u] > x)
        remove(x, ch[u][0]);
    else
        remove(x, ch[u][1]);
    update(u);
}
int find(int u, int x)
{
    if (!u)
        return 1;
    if (val[u] >= x)
        return find(ch[u][0], x);
    return siz[ch[u][0]] + find(ch[u][1], x) + 1;
}
int revfind(int u, int rk)
{
    if (siz[ch[u][0]] + 1 == rk)
        return val[u];
    if (siz[ch[u][0]] >= rk)
        return revfind(ch[u][0], rk);
    return revfind(ch[u][1], rk - siz[ch[u][0]] - 1);
}
int previous(int u, int x)
{
    if (!u)
        return -2e9;
    if (val[u] < x)
        return max(val[u], previous(ch[u][1], x));
    return previous(ch[u][0], x);
}
int backward(int u, int x)
{
    if (!u)
        return 2e9;
    if (val[u] > x)
        return min(val[u], backward(ch[u][0], x));
    return backward(ch[u][1], x);
}
int main()
{
    srand(time(NULL));
    int n;
    scanf("%d", &n);
    while (n--)
    {
        int opt, x;
        scanf("%d%d", &opt, &x);
        switch (opt)
        {
        case 1:
            insert(x, root);
            break;
        case 2:
            remove(x, root);
            break;
        case 3:
            printf("%d\n", find(root, x));
            break;
        case 4:
            printf("%d\n", revfind(root, x));
            break;
        case 5:
            printf("%d\n", previous(root, x));
            break;
        case 6:
            printf("%d\n", backward(root, x));
            break;
        }
    }
    return 0;
}