// P3247.cpp
#include <bits/stdc++.h>

using namespace std;

const int MAX_N = 2e5 + 200;

int n, m, q, mem[MAX_N], maxa[MAX_N], maxb[MAX_N], siz[MAX_N], block_siz, block_tot;
bool ans[MAX_N];

struct edge
{
    int u, v, a, b, id;
} edges[MAX_N], queries[MAX_N], cqueries[MAX_N];

struct historyMark
{
    int id, org_fa, curt_node, org_a, org_b, org_siz;
};
stack<historyMark> stk;

inline char gc()
{
    static char buf[1000000], *p1 = buf, *p2 = buf;
    return p1 == p2 && (p2 = (p1 = buf) + fread(buf, 1, 1000000, stdin), p1 == p2) ? EOF : *p1++;
}

int read()
{
    int x = 0, f = 1;
    char ch = gc();
    while (!isdigit(ch))
    {
        if (ch == '-')
            f = -1;
        ch = gc();
    }
    while (isdigit(ch))
        x = (x << 3) + (x << 1) + ch - '0', ch = gc();
    return f * x;
}

bool compareA(const edge &rhs1, const edge &rhs2) { return rhs1.a < rhs2.a || (rhs1.a == rhs2.a && rhs1.b < rhs2.b); }

bool compareB(const edge &rhs1, const edge &rhs2) { return rhs1.b < rhs2.b || (rhs1.b == rhs2.b && rhs1.a < rhs2.a); }

int find(int x) { return x == mem[x] ? x : find(mem[x]); }

void merge(int x, int y, int a, int b, bool saveHistroy = false)
{
    x = find(x), y = find(y);
    if (siz[x] > siz[y])
        swap(x, y);
    if (saveHistroy)
    {
        historyMark curt;
        curt.id = x, curt.curt_node = y;
        curt.org_a = maxa[y], curt.org_b = maxb[y];
        curt.org_fa = mem[x], curt.org_siz = siz[y];
        stk.push(curt);
    }
    if (x == y)
    {
        maxa[x] = max(maxa[x], a), maxb[x] = max(maxb[x], b);
        return;
    }
    mem[x] = y, siz[y] += siz[x], maxa[y] = max({maxa[y], maxa[x], a}), maxb[y] = max({maxb[y], maxb[x], b});
}

void undo()
{
    while (!stk.empty())
    {
        historyMark curt = stk.top();
        stk.pop();
        mem[curt.id] = curt.org_fa;
        siz[curt.curt_node] = curt.org_siz;
        maxa[curt.curt_node] = curt.org_a;
        maxb[curt.curt_node] = curt.org_b;
    }
}

int main()
{
    n = read(), m = read();
    for (int i = 1; i <= m; i++)
        edges[i].u = read(), edges[i].v = read(), edges[i].a = read(), edges[i].b = read(), edges[i].id = i;
    q = read();
    for (int i = 1; i <= q; i++)
        queries[i].u = read(), queries[i].v = read(), queries[i].a = read(), queries[i].b = read(), queries[i].id = i;
    sort(edges + 1, edges + 1 + m, compareA);
    sort(queries + 1, queries + 1 + q, compareB);
    block_siz = sqrt(m);
    for (int i = 1; i <= m; i += block_siz)
    {
        int qtot = 0;
        for (int j = 1; j <= q; j++)
            if (queries[j].a >= edges[i].a && (i + block_siz > m || queries[j].a < edges[i + block_siz].a))
                cqueries[++qtot] = queries[j];
        sort(edges + 1, edges + 1 + i, compareB);
        for (int j = 1; j <= n; j++)
            siz[j] = 1, mem[j] = j, maxa[j] = maxb[j] = -1;
        for (int j = 1, ptr = 1; j <= qtot; j++)
        {
            for (; ptr < i && edges[ptr].b <= cqueries[j].b; ptr++)
                merge(edges[ptr].u, edges[ptr].v, edges[ptr].a, edges[ptr].b, false);
            for (int k = i; k <= i + block_siz - 1 && k <= m; k++)
                if (edges[k].a <= cqueries[j].a && edges[k].b <= cqueries[j].b)
                    merge(edges[k].u, edges[k].v, edges[k].a, edges[k].b, true);
            int x = find(cqueries[j].u), y = find(cqueries[j].v);
            ans[cqueries[j].id] |= (x == y && maxa[x] == cqueries[j].a && maxb[x] == cqueries[j].b);
            undo();
        }
    }
    for (int i = 1; i <= q; i++)
        puts(ans[i] ? "Yes" : "No");
    return 0;
}