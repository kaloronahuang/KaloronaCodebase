// road.cpp
// #pragma GCC optimize(2)
#include <bits/stdc++.h>

using namespace std;

const int MAX_N = 8e5 + 200, INF = 0x3f3f3f3f;

int n, m, ptot, eu[MAX_N], ev[MAX_N], ew[MAX_N];

struct compare
{
    bool operator()(const int &rhs1, const int &rhs2) { return ew[rhs1] > ew[rhs2] || (ew[rhs1] == ew[rhs2] && rhs1 > rhs2); }
};

set<int, compare> st;

// LCT part;

int ch[MAX_N][2], fa[MAX_N], val[MAX_N], idx[MAX_N], siz[MAX_N], vsiz[MAX_N], self[MAX_N];
bool tag[MAX_N];

#define lson (ch[p][0])
#define rson (ch[p][1])

void pushdown(int p)
{
    if (tag[p])
    {
        swap(lson, rson);
        tag[lson] ^= 1, tag[rson] ^= 1;
        tag[p] = 0;
    }
}

void pushup(int p)
{
    idx[p] = p;
    if (val[idx[lson]] > val[idx[p]])
        idx[p] = idx[lson];
    if (val[idx[rson]] > val[idx[p]])
        idx[p] = idx[rson];
    siz[p] = siz[lson] + siz[rson] + vsiz[p] + self[p];
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
        splay(p), vsiz[p] += siz[rson] - siz[pre], rson = pre, pushup(p);
}

void makeRoot(int p) { access(p), splay(p), tag[p] ^= 1, pushdown(p); }

int find(int p)
{
    access(p), splay(p);
    while (lson)
        p = lson;
    splay(p);
    return p;
}

void removeEdge(int id)
{
    st.erase(id), makeRoot(id), access(id);
    splay(eu[id]), fa[eu[id]] = 0, splay(ev[id]), fa[ev[id]] = 0;
}

void fileIO()
{
    freopen("road12.in", "r", stdin);
    freopen("road12.out", "w", stdout);
}

int main()
{
    // fileIO();
    scanf("%d%d", &n, &m), ptot = n;
    if (n & 1)
    {
        while (m--)
            puts("-1");
        return 0;
    }
    for (int i = 1; i <= n; i++)
        siz[i] = self[i] = 1;
    for (int i = 1; i <= (n >> 1); i++)
    {
        ptot++, eu[ptot] = (i << 1) - 1, ev[ptot] = (i << 1), ew[ptot] = INF;
        idx[ptot] = ptot, val[ptot] = INF, fa[(i << 1) - 1] = fa[i << 1] = ptot;
        vsiz[ptot] += siz[i << 1] + siz[(i << 1) - 1], st.insert(ptot);
    }
    while (m--)
    {
        ptot++, scanf("%d%d%d", &eu[ptot], &ev[ptot], &ew[ptot]);
        int u = eu[ptot], v = ev[ptot], w = ew[ptot];
        makeRoot(u);
        if (find(v) != u)
        {
            idx[ptot] = val[ptot] = w;
            makeRoot(v), fa[u] = fa[v] = ptot;
            vsiz[ptot] += siz[u] + siz[v], st.insert(ptot);
        }
        else
        {
            access(v), splay(v);
            int removeId = idx[v];
            if (ew[removeId] > w)
            {
                idx[ptot] = ptot, val[ptot] = w;
                removeEdge(removeId);
                makeRoot(u), makeRoot(v), fa[u] = fa[v] = ptot;
                vsiz[ptot] += siz[u] + siz[v], st.insert(ptot);
            }
        }
        while (true)
        {
            int eid = *st.begin(), siz = st.size();
            makeRoot(eu[eid]), access(eid);
            if (vsiz[eid] & 1)
                break;
            else
                removeEdge(eid);
        }
        int ans = ew[*st.begin()];
        printf("%d\n", ans == INF ? -1 : ans);
    }
    return 0;
}