// BZ2555.cpp
#include <bits/stdc++.h>

using namespace std;

const int MAX_N = 6010000;

int q, mask, ch[MAX_N << 1][2], fa[MAX_N << 1], siz[MAX_N << 1], tag[MAX_N << 1], ptot = 1, last_ptr = 1;
char str[MAX_N], cmdlet[5];

struct node
{
    int ch[26], dep, link;
} nodes[MAX_N];

#define lson (ch[p][0])
#define rson (ch[p][1])

// LCT;

bool isRoot(int p) { return ch[fa[p]][0] != p && ch[fa[p]][1] != p; }

int check(int p) { return ch[fa[p]][1] == p; }

void rotate(int x)
{
    int y = fa[x], z = fa[y], dir = check(x), w = ch[x][dir ^ 1];
    fa[x] = z;
    if (!isRoot(y))
        ch[z][check(y)] = x;
    fa[y] = x, ch[x][dir ^ 1] = y;
    fa[w] = y, ch[y][dir] = w;
}

void pushdown(int p)
{
    if (tag[p])
    {
        siz[lson] += tag[p], siz[rson] += tag[p];
        tag[lson] += tag[p], tag[rson] += tag[p];
        tag[p] = 0;
    }
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
}

void access(int p)
{
    for (int pre = 0; p; pre = p, p = fa[p])
        splay(p), rson = pre;
}

void link(int x, int y) { fa[x] = y, access(y), splay(y), tag[y] += siz[x], siz[y] += siz[x]; }

void cut(int x) { access(x), splay(x), tag[ch[x][0]] -= siz[x], siz[ch[x][0]] -= siz[x], ch[x][0] = fa[ch[x][0]] = 0; }

#undef rson
#undef lson

void insert(int c)
{
    int pre = last_ptr, p = last_ptr = ++ptot;
    nodes[p].dep = nodes[pre].dep + 1, siz[p] = 1;
    while (pre && nodes[pre].ch[c] == 0)
        nodes[pre].ch[c] = p, pre = nodes[pre].link;
    if (pre == 0)
        nodes[p].link = 1, link(p, 1);
    else
    {
        int q = nodes[pre].ch[c];
        if (nodes[q].dep == nodes[pre].dep + 1)
            nodes[p].link = q, link(p, q);
        else
        {
            int clone = ++ptot;
            nodes[clone] = nodes[q], nodes[clone].dep = nodes[pre].dep + 1;
            cut(q), nodes[p].link = nodes[q].link = clone, link(p, clone), link(q, clone), link(clone, nodes[clone].link);
            while (pre && nodes[pre].ch[c] == q)
                nodes[pre].ch[c] = clone, pre = nodes[pre].link;
        }
    }
}

void decode()
{
    int len = strlen(str), tmp = mask;
    for (int i = 0; i < len; i++)
        tmp = (tmp * 131 + i) % len, swap(str[i], str[tmp]);
}

int main()
{
    scanf("%d%s", &q, str);
    for (int i = 0; str[i]; i++)
        insert(str[i] - 'A');
    while (q--)
    {
        scanf("%s%s", cmdlet, str), decode();
        if (cmdlet[0] == 'A')
            for (int i = 0; str[i]; i++)
                insert(str[i] - 'A');
        else
        {
            int p = 1;
            bool flag = true;
            for (int i = 0; str[i]; i++)
                if (nodes[p].ch[str[i] - 'A'])
                    p = nodes[p].ch[str[i] - 'A'];
                else
                {
                    puts("0"), flag = false;
                    break;
                }
            if (flag)
                splay(p), printf("%d\n", siz[p]), mask ^= siz[p];
        }
    }
    return 0;
}