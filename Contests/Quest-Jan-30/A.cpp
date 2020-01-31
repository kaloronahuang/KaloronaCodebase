// A.cpp
#include <bits/stdc++.h>

using namespace std;

const int MAX_N = 3e5 + 200;

int n, q, typ, mem[MAX_N];
pair<int, int> diameters[MAX_N];

inline char nc()
{
    static char buf[100000], *p1 = buf, *p2 = buf;
    return p1 == p2 && (p2 = (p1 = buf) + fread(buf, 1, 100000, stdin), p1 == p2) ? EOF : *p1++;
}

int read()
{
    int x = 0, f = 1;
    char ch = nc();
    while (!isdigit(ch))
    {
        if (ch == '-')
            f = -1;
        ch = nc();
    }
    while (isdigit(ch))
        x = (x << 3) + (x << 1) + ch - '0', ch = nc();
    return x * f;
}

int find(int x) { return mem[x] == x ? x : mem[x] = find(mem[x]); }

namespace LCT
{

int ch[MAX_N][2], fa[MAX_N], siz[MAX_N];
bool revTag[MAX_N];

#define lson (ch[p][0])
#define rson (ch[p][1])

// splay backend;

bool isRoot(int p) { return ch[fa[p]][0] != p && ch[fa[p]][1] != p; }

int check(int p) { return ch[fa[p]][1] == p; }

void pushup(int p) { siz[p] = siz[lson] + siz[rson] + 1; }

void pushdown(int p)
{
    if (revTag[p])
    {
        swap(lson, rson);
        revTag[lson] ^= 1, revTag[rson] ^= 1;
        revTag[p] = 0;
    }
}

void rotate(int x)
{
    int y = fa[x], z = fa[y], dir = check(x), w = ch[x][dir ^ 1];
    fa[x] = z;
    if (!isRoot(y))
        ch[z][check(y)] = x;
    fa[y] = x, ch[x][dir ^ 1] = y;
    fa[w] = y, ch[y][dir] = w;
    pushup(y), pushup(x);
}

void update(int p)
{
    if (!isRoot(p))
        update(fa[p]);
    pushdown(p);
}

void splay(int p)
{
    update(p);
    for (int fat = fa[p]; fat = fa[p], !isRoot(p); rotate(p))
        if (!isRoot(fat))
            rotate(check(p) == check(fat) ? fat : p);
}

// lct utilities;

void access(int p)
{
    for (int pre = 0; p; pre = p, p = fa[p])
        splay(p), rson = pre, pushup(p);
}

void makeRoot(int p) { access(p), splay(p), revTag[p] ^= 1, pushdown(p); }

void split(int x, int y) { makeRoot(x), access(y), splay(y); }

void link(int x, int y) { makeRoot(x), fa[x] = y; }

int getDist(int x, int y)
{
    split(x, y);
    return siz[y] - 1;
}

#undef rson
#undef lson

} // namespace LCT

int main()
{
    // freopen("hike1.in", "r", stdin);
    scanf("%d%d%d", &typ, &n, &q);
    for (int i = 1; i <= n; i++)
        mem[i] = i, diameters[i] = make_pair(i, i);
    int lastans = 0;
    while (q--)
    {
        int opt, u, v;
        scanf("%d%d", &opt, &u);
        if (opt == 1)
        {
            scanf("%d", &v);
            u ^= (typ * lastans), v ^= (typ * lastans), LCT::link(u, v);
            // merge the diameter;
            int fu = find(u), fv = find(v);
            pair<int, int> du = diameters[fu], dv = diameters[fv], ans;
            mem[fu] = fv;

            int u1 = du.first, v1 = du.second, d1 = LCT::getDist(u1, v1);
            int u2 = dv.first, v2 = dv.second, d2 = LCT::getDist(u2, v2);

            int u3 = du.first, v3 = dv.second, d3 = LCT::getDist(u3, v3);
            int u4 = dv.first, v4 = du.second, d4 = LCT::getDist(u4, v4);

            int u5 = du.first, v5 = dv.first, d5 = LCT::getDist(u5, v5);
            int u6 = dv.second, v6 = du.second, d6 = LCT::getDist(u6, v6);

            int ans_u = u1, ans_v = v1, ans_d = d1;

            if (d2 > ans_d)
                ans_u = u2, ans_v = v2, ans_d = d2;
            if (d3 > ans_d)
                ans_u = u3, ans_v = v3, ans_d = d3;
            if (d4 > ans_d)
                ans_u = u4, ans_v = v4, ans_d = d4;
            if (d5 > ans_d)
                ans_u = u5, ans_v = v5, ans_d = d5;
            if (d6 > ans_d)
                ans_u = u6, ans_v = v6, ans_d = d6;

            diameters[fv] = make_pair(ans_u, ans_v);
        }
        else
            u ^= (typ * lastans), printf("%d\n", lastans = max(LCT::getDist(u, diameters[find(u)].first), LCT::getDist(u, diameters[find(u)].second)));
    }
    return 0;
}