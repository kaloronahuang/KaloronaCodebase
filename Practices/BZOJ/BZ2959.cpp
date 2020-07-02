// BZ2959.cpp
#include <bits/stdc++.h>

using namespace std;

const int MAX_N = 1.5e5 + 200;

int n, q, ch[MAX_N][2], fa[MAX_N], val[MAX_N], sum[MAX_N], mem[2][MAX_N], oval[MAX_N];
bool tag[MAX_N];

#define lson (ch[p][0])
#define rson (ch[p][1])

// LCT;

int find(int id, int x) { return mem[id][x] == x ? x : mem[id][x] = find(id, mem[id][x]); }

void pushup(int p) { sum[p] = sum[lson] + sum[rson] + val[p]; }

bool isRoot(int p) { return ch[find(0, fa[p])][0] != p && ch[find(0, fa[p])][1] != p; }

int check(int p) { return ch[find(0, fa[p])][1] == p; }

void pushdown(int p)
{
    if (tag[p])
    {
        if (lson)
            swap(ch[lson][0], ch[lson][1]), tag[lson] ^= 1;
        if (rson)
            swap(ch[rson][0], ch[rson][1]), tag[rson] ^= 1;
        tag[p] = false;
    }
}

void rotate(int x)
{
    int y = find(0, fa[x]), z = find(0, fa[y]), dir = check(x), w = ch[x][dir ^ 1];
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
        update(find(0, fa[p]));
    pushdown(p);
}

void splay(int p)
{
    update(p);
    for (int fat = find(0, fa[p]); fat = find(0, fa[p]), !isRoot(p); rotate(p))
        if (!isRoot(fat))
            rotate(check(p) == check(fat) ? fat : p);
}

void access(int p)
{
    for (int pre = 0; p; pre = p, p = find(0, fa[p]))
        splay(p), rson = pre, pushup(p);
}

void makeRoot(int p) { access(p), splay(p), swap(lson, rson), tag[p] ^= 1; }

void dfs(int u, int src)
{
    mem[0][u] = src, pushdown(u);
    for (int i = 0; i < 2; i++)
        if (ch[u][i])
            dfs(ch[u][i], src);
}

int main()
{
    scanf("%d%d", &n, &q);
    for (int i = 1; i <= n; i++)
        mem[0][i] = mem[1][i] = i, scanf("%d", &val[i]), sum[i] = oval[i] = val[i];
    while (q--)
    {
        int opt, a, b;
        scanf("%d%d%d", &opt, &a, &b);
        if (opt == 1)
        {
            a = find(0, a), b = find(0, b);
            if (a == b)
                continue;
            makeRoot(a), access(b), splay(b);
            if (find(1, a) != find(1, b))
                fa[a] = b, mem[1][find(1, a)] = mem[1][find(1, b)];
            else
                // minimize the loop;
                val[b] = sum[b], dfs(b, b), ch[b][0] = ch[b][1] = 0, pushup(b);
        }
        else if (opt == 2)
        {
            int fx = find(0, a);
            splay(fx), val[fx] -= oval[a] - b, oval[a] = b, pushup(fx);
        }
        else
        {
            a = find(0, a), b = find(0, b);
            if (find(1, a) != find(1, b))
                puts("-1");
            else
                makeRoot(a), access(b), splay(b), printf("%d\n", sum[b]);
        }
    }
    return 0;
}