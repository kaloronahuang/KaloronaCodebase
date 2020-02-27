// LOJ3105.cpp
#include <bits/stdc++.h>

using namespace std;

const int MAX_N = 1200100, INF = 0x3f3f3f3f;

typedef pair<int, int> pii;
typedef unsigned int ui;

int T, m, solved[MAX_N], penalty[MAX_N];
ui n, sed, last = 7;

ui randNum(ui &seed, ui last, const ui m)
{
    seed = seed * 17 + last;
    return seed % m + 1;
}

namespace Splay
{

int ch[MAX_N][2], fa[MAX_N], siz[MAX_N], cnt[MAX_N], root, ptot;
pii val[MAX_N];

#define lson (ch[p][0])
#define rson (ch[p][1])

// splay;

int check(int x) { return ch[fa[x]][1] == x; }

void pushup(int p) { siz[p] = siz[lson] + siz[rson] + cnt[p]; }

void rotate(int x)
{
    int y = fa[x], z = fa[y], dir = check(x), w = ch[x][dir ^ 1];
    fa[x] = z;
    if (z != 0)
        ch[z][check(y)] = x;
    fa[y] = x, ch[x][dir ^ 1] = y;
    fa[w] = y, ch[y][dir] = w;
    pushup(y), pushup(x);
}

void splay(int p, int goal = 0)
{
    for (int fat = fa[p]; fat = fa[p], fat != goal; rotate(p))
        if (fa[fat] != goal)
            rotate(check(fat) == check(p) ? fat : p);
    if (goal == 0)
        root = p;
}

int previous(pii key)
{
    int p = root, pre = 0;
    while (p)
        if (val[p] < key)
            pre = p, p = rson;
        else
            p = lson;
    return pre;
}

int backward(pii key)
{
    int p = root, pre = 0;
    while (p)
        if (val[p] > key)
            pre = p, p = lson;
        else
            p = rson;
    return pre;
}

void remove(pii key)
{
    int pre = previous(key), nxt = backward(key);
    splay(pre, 0), splay(nxt, pre);
    int pos = ch[nxt][0];
    if (cnt[pos] > 1)
        cnt[pos]--, splay(pos);
    else
        ch[nxt][0] = 0;
}

void insert(pii key)
{
    int p = root, pre = 0;
    while (p && key != val[p])
        pre = p, p = ch[p][key > val[p]];
    if (p)
        cnt[p]++;
    else
    {
        p = ++ptot, val[p] = key, siz[p] = 1;
        fa[p] = pre, cnt[p] = 1, lson = rson = 0;
        if (pre)
            ch[pre][val[p] > val[pre]] = p;
    }
    splay(p);
}

#undef rson
#undef lson

} // namespace Splay

int main()
{
    scanf("%d", &T);
    while (T--)
    {
        scanf("%u%d%u", &n, &m, &sed), Splay::root = Splay::ptot = 0;
        Splay::insert(make_pair(INF, -INF)), Splay::insert(make_pair(-INF, INF));
        memset(penalty, 0, sizeof(penalty)), memset(solved, 0, sizeof(solved));
        while (m--)
        {
            int pid, punish;
            pid = randNum(sed, last, n), punish = randNum(sed, last, n);
            if (solved[pid] > 0)
                Splay::remove(make_pair(solved[pid], -penalty[pid]));
            solved[pid]++, penalty[pid] += punish;
            Splay::insert(make_pair(solved[pid], -penalty[pid]));
            last = Splay::siz[Splay::ch[Splay::root][1]] - 1, printf("%u\n", last);
        }
    }
    return 0;
}