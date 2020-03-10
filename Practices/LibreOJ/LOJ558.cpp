// LOJ558.cpp
#include <bits/stdc++.h>

using namespace std;

const int MAX_N = 4e5 + 200;

typedef long long ll;

map<pair<int, int>, int> mp;

char cmdlet[20];

namespace LCT
{

int ch[MAX_N][2], fa[MAX_N], color[MAX_N], val[MAX_N], csiz[MAX_N], vcsiz[MAX_N];
ll lmn[MAX_N], rmn[MAX_N], dist[MAX_N], vsum[MAX_N];
bool tag[MAX_N];

#define lson (ch[p][0])
#define rson (ch[p][1])

void pushdown(int p)
{
    if (tag[p])
    {
        if (lson)
            tag[lson] ^= 1, swap(ch[lson][0], ch[lson][1]), swap(lmn[lson], rmn[lson]);
        if (rson)
            tag[rson] ^= 1, swap(ch[rson][0], ch[rson][1]), swap(lmn[rson], rmn[rson]);
        tag[p] = false;
    }
}

void pushup(int p)
{
    csiz[p] = color[p] + csiz[lson] + csiz[rson] + vcsiz[p];
    dist[p] = val[p] + dist[lson] + dist[rson];
    lmn[p] = lmn[lson] + lmn[rson] + vsum[p] + 1LL * (dist[lson] + val[p]) * (vcsiz[p] + color[p] + csiz[rson]);
    rmn[p] = rmn[lson] + rmn[rson] + vsum[p] + 1LL * (dist[rson] + val[p]) * (vcsiz[p] + color[p] + csiz[lson]);
}

int check(int p) { return ch[fa[p]][1] == p; }

bool isRoot(int p) { return ch[fa[p]][1] != p && ch[fa[p]][0] != p; }

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
            rotate(check(fat) == check(p) ? fat : p);
    pushup(p);
}

void access(int p)
{
    for (int pre = 0; p; pre = p, p = fa[p])
    {
        splay(p);
        vsum[p] += lmn[rson] - lmn[pre];
        vcsiz[p] += csiz[rson] - csiz[pre];
        rson = pre, pushup(p);
    }
}

void makeRoot(int p) { access(p), splay(p), tag[p] ^= 1, swap(lson, rson), swap(lmn[p], rmn[p]); }

void split(int x, int y) { makeRoot(x), access(y), splay(y); }

void link(int x, int y)
{
    makeRoot(x), makeRoot(y);
    fa[x] = y, splay(x);
    vsum[y] += lmn[x], vcsiz[y] += csiz[x];
}

void cut(int x, int y)
{
    split(x, y);
    fa[x] = ch[y][0] = 0;
    pushup(y);
}

} // namespace LCT

int n, m, q, etot;

int main()
{
    scanf("%d%d%d", &n, &m, &q);
    for (int i = 1, u, v, w; i <= m; i++)
    {
        scanf("%d%d%d", &u, &v, &w);
        if (u > v)
            swap(u, v);
        if (!mp.count(make_pair(u, v)))
            mp[make_pair(u, v)] = ++etot;
        int eid = n + mp[make_pair(u, v)];
        LCT::dist[eid] = LCT::val[eid] = w;
        LCT::link(u, eid), LCT::link(v, eid);
    }
    while (q--)
    {
        int u, v, w;
        scanf("%s", cmdlet + 1);
        if (cmdlet[1] == 'L')
        {
            scanf("%d%d%d", &u, &v, &w);
            if (u > v)
                swap(u, v);
            if (!mp.count(make_pair(u, v)))
                mp[make_pair(u, v)] = ++etot;
            int eid = n + mp[make_pair(u, v)];
            LCT::dist[eid] = LCT::val[eid] = w;
            LCT::link(u, eid), LCT::link(v, eid);
        }
        else if (cmdlet[1] == 'C')
        {
            scanf("%d%d", &u, &v);
            if (u > v)
                swap(u, v);
            int eid = n + mp[make_pair(u, v)];
            LCT::cut(u, eid), LCT::cut(v, eid);
        }
        else if (cmdlet[1] == 'F')
        {
            scanf("%d", &u);
            LCT::access(u), LCT::splay(u), LCT::color[u] ^= 1;
        }
        else
        {
            scanf("%d", &u);
            LCT::access(u), LCT::splay(u);
            printf("%lld\n", LCT::rmn[u]);
        }
    }
    return 0;
}