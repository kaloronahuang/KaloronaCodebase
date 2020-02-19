// graph.cpp
#include <bits/stdc++.h>

using namespace std;

const int MAX_N = 1e6 + 200, MAX_E = 4e5 + 200;

typedef long long ll;

int n, A, B, q, mem[MAX_N], queries[MAX_N], idx[MAX_N];
ll ansBox[MAX_N];

struct edge
{
    int u, v, k, opt;
    ll weight;
    bool operator<(const edge &rhs) const { return weight < rhs.weight; }
} edges[MAX_E], gA[MAX_N], gB[MAX_N];

void fileIO()
{
    freopen("graph.in", "r", stdin);
    freopen("graph.out", "w", stdout);
}

int find(int x) { return mem[x] == x ? x : mem[x] = find(mem[x]); }

bool compare(int a, int b) { return queries[a] < queries[b]; }

#pragma region LCT

namespace LCT
{

int ch[MAX_N][2], fa[MAX_N], val[MAX_N];
bool tag[MAX_N];

#define lson (ch[p][0])
#define rson (ch[p][1])

void pushdown(int p)
{
    if (tag[p])
    {
        tag[lson] ^= 1, tag[rson] ^= 1;
        swap(lson, rson), tag[p] = false;
    }
}

bool isRoot(int p) { return ch[fa[p]][1] != p && ch[fa[p]][0] != p; }

int check(int p) { return ch[fa[p]][1] == p; }

void pushup(int p)
{
    val[p] = p;
    if (lson)
        val[p] = max(val[p], val[lson]);
    if (rson)
        val[p] = max(val[p], val[rson]);
}

void rotate(int x)
{
    int y = fa[x], z = fa[y], dir = check(x), w = ch[x][dir ^ 1];
    fa[x] = z;
    if (!isRoot(y))
        ch[z][check(y)] = x;
    fa[w] = y, ch[y][dir] = w;
    fa[y] = x, ch[x][dir ^ 1] = y;
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

void access(int p)
{
    for (int pre = 0; p; pre = p, p = fa[p])
        splay(p), rson = pre, pushup(p);
}

int find(int p)
{
    access(p), splay(p), pushdown(p);
    while (lson)
        pushdown(p = lson);
    splay(p);
    return p;
}

void makeRoot(int p) { access(p), splay(p), tag[p] ^= 1, pushdown(p); }

void split(int x, int y) { makeRoot(x), access(y), splay(y); }

void link(int x, int y) { makeRoot(x), fa[x] = y; }

void cut(int x, int y) { makeRoot(x), fa[y] = ch[x][1] = 0, pushup(x); }

#undef rson
#undef lson

} // namespace LCT

#pragma endregion

int main()
{
    // fileIO();
    scanf("%d%d%d%d", &n, &A, &B, &q);
    for (int i = 1; i <= A + B; i++)
    {
        scanf("%d%d%d", &edges[i].u, &edges[i].v, &edges[i].k);
        edges[i].opt = (i > A ? -1 : 1), edges[i].weight = edges[i].k;
    }
    ll coeff = 0, const_term = 0;
    sort(edges + 1, edges + A + 1), sort(edges + A + 1, edges + A + B + 1);
    for (int i = 1; i <= n; i++)
        mem[i] = i;
    for (int i = 1, cnt = 0; i <= A && cnt < n - 1; i++)
        if (find(edges[i].u) != find(edges[i].v))
        {
            coeff += edges[i].opt, const_term += edges[i].k;
            mem[find(edges[i].u)] = find(edges[i].v), gA[++cnt] = edges[i];
            // implement on LCT;
            LCT::link(edges[i].u, cnt + n), LCT::link(edges[i].v, cnt + n);
        }
    for (int i = 1; i <= n; i++)
        mem[i] = i;
    for (int i = A + 1, cnt = 0; i <= A + B && cnt < n - 1; i++)
        if (find(edges[i].u) != find(edges[i].v))
        {
            LCT::split(edges[i].u, edges[i].v);
            int biggest_val = LCT::val[edges[i].v];
            if (biggest_val > n)
            {
                // replace & calc the lowerbound;
                biggest_val -= n;
                edges[i].weight = (edges[i].k - gA[biggest_val].k + 1) / 2;
                LCT::splay(biggest_val + n), LCT::fa[LCT::ch[biggest_val + n][0]] = LCT::fa[LCT::ch[biggest_val + n][1]] = 0;
                LCT::link(edges[i].u, edges[i].v), edges[i].opt -= gA[biggest_val].opt, edges[i].k -= gA[biggest_val].k;
            }
            else
                edges[i].weight = 2e9;
            gB[++cnt] = edges[i], mem[find(edges[i].u)] = find(edges[i].v);
        }
    sort(gB + 1, gB + n);
    for (int i = 1; i <= q; i++)
        idx[i] = i, scanf("%d", &queries[i]);
    sort(idx + 1, idx + 1 + q, compare);
    for (int i = 1, ptr = 1; i <= q; i++)
    {
        while (ptr <= n - 1 && gB[ptr].weight <= queries[idx[i]])
            coeff += gB[ptr].opt, const_term += gB[ptr].k, ptr++;
        ansBox[idx[i]] = 1LL * coeff * queries[idx[i]] + const_term;
    }
    for (int i = 1; i <= q; i++)
        printf("%lld\n", ansBox[i]);
    return 0;
}