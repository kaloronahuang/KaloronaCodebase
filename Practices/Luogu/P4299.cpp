// P4299.cpp
#include <bits/stdc++.h>

using namespace std;

const int MAX_N = 101000, INF = 0x3f3f3f3f;

int head[MAX_N], current, n, q, ch[MAX_N][2], siz[MAX_N], fa[MAX_N], mem[MAX_N];
int xorsum, vsiz[MAX_N];
bool tag[MAX_N];
char opt[20];

// splay tree;

#define lson (ch[p][0])
#define rson (ch[p][1])
#define mid ((l + r) >> 1)

// utilities;

int find(int p) { return mem[p] == p ? p : mem[p] = find(mem[p]); }

void pushdown(int p)
{
    if (tag[p])
    {
        tag[lson] ^= 1, tag[rson] ^= 1;
        swap(lson, rson), tag[p] = 0;
    }
}

int isRoot(int p) { return ch[fa[p]][1] != p && ch[fa[p]][0] != p; }

int check(int p) { return ch[fa[p]][1] == p; }

void pushup(int p) { siz[p] = siz[lson] + siz[rson] + vsiz[p] + 1; }

void rotate(int x)
{
    int y = fa[x], z = fa[y], dir = check(x), w = ch[x][dir ^ 1];
    fa[x] = z;
    if (!isRoot(y))
        ch[z][check(y)] = x;
    ch[y][dir] = w, fa[w] = y;
    ch[x][dir ^ 1] = y, fa[y] = x;
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
    for (int fat = 0; p != 0; fat = p, p = fa[p])
        splay(p), vsiz[p] += siz[rson], vsiz[p] -= siz[rson = fat], pushup(p);
}

void makeRoot(int p)
{
    access(p), splay(p);
    tag[p] ^= 1, pushdown(p);
}

void split(int x, int y) { makeRoot(x), access(y), splay(y); }

void link(int x, int y)
{
    split(x, y);
    vsiz[fa[x] = y] += siz[x];
    pushup(y);
}

int find_mid(int p)
{
    int bit = siz[p] & 1, thershold = (siz[p] >> 1), ret_pt = INF;
    int lft_acc = 0, rig_acc = 0;
    while (p)
    {
        pushdown(p);
        int clft = lft_acc + siz[lson], crig = rig_acc + siz[rson];
        if (max(clft, crig) <= thershold)
        {
            // waits to be chosen;
            if (bit)
            {
                ret_pt = p;
                break;
            }
            else
                ret_pt = min(ret_pt, p);
        }
        if (clft < crig)
            // go to right side;
            lft_acc += siz[lson] + vsiz[p] + 1, p = rson;
        else
            rig_acc += siz[rson] + vsiz[p] + 1, p = lson;
    }
    splay(ret_pt);
    return ret_pt;
}

#undef mid
#undef rson
#undef lson

int main()
{
    scanf("%d%d", &n, &q);
    for (int i = 1; i <= n; i++)
        mem[i] = i, xorsum ^= i, siz[i] = 1;
    while (q--)
    {
        int x, y;
        scanf("%s", opt + 1);
        if (opt[1] == 'A')
        {
            scanf("%d%d", &x, &y);
            link(x, y), x = find(x), y = find(y);
            split(x, y);
            int mid = find_mid(y);
            xorsum ^= x ^ y ^ mid;
            mem[x] = mem[y] = mem[mid] = mid;
        }
        else if (opt[1] == 'Q')
            scanf("%d", &x), printf("%d\n", find(x));
        else
            printf("%d\n", xorsum);
    }
    return 0;
}