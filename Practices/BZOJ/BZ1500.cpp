// BZ1500.cpp
#include <bits/stdc++.h>

using namespace std;

const int MAX_N = 1e6 + 2000, INF = 0x3f3f3f3f;

int n, q, ptot, seq[MAX_N], root, idx[MAX_N];
int ch[MAX_N][2], fa[MAX_N], val[MAX_N], siz[MAX_N], sum[MAX_N], lsum[MAX_N], msum[MAX_N], rsum[MAX_N], tag_val[MAX_N];
bool rev[MAX_N], tag[MAX_N];
char cmd[30];
queue<int> recBin;

#define lson ch[p][0]
#define rson ch[p][1]

int read()
{
    int x = 0, f = 1;
    char ch = getchar();
    while (!isdigit(ch))
    {
        if (ch == '-')
            f = -1;
        ch = getchar();
    }
    while (isdigit(ch))
        x = (x << 3) + (x << 1) + ch - '0', ch = getchar();
    return x * f;
}

void clear(int p) { return (void)(siz[p] = lson = rson = val[p] = tag_val[p] = fa[p] = tag[p] = rev[p] = 0); }

int newNodeId()
{
    if (!recBin.empty())
    {
        int p = recBin.front();
        clear(p), recBin.pop();
        return p;
    }
    return ++ptot;
}

void newNode(int p, int v)
{
    msum[p] = sum[p] = v, siz[p] = 1;
    tag[p] = rev[p] = false;
    lsum[p] = rsum[p] = max(v, 0);
}

void pushup(int p)
{
    siz[p] = siz[lson] + siz[rson] + 1;
    sum[p] = sum[lson] + sum[rson] + val[p];
    msum[p] = max(max(msum[lson], msum[rson]), rsum[lson] + val[p] + lsum[rson]);
    lsum[p] = max(lsum[lson], sum[lson] + val[p] + lsum[rson]);
    rsum[p] = max(rsum[rson], sum[rson] + val[p] + rsum[lson]);
}

void update_val(int p, int v)
{
    if (p == 0)
        return;
    tag[p] = true, tag_val[p] = v;
    val[p] = v, sum[p] = siz[p] * v;
    lsum[p] = rsum[p] = max(0, sum[p]);
    msum[p] = max(sum[p], val[p]);
}

void reverse(int p)
{
    rev[p] ^= 1, swap(lson, rson);
    swap(lsum[p], rsum[p]);
}

void pushdown(int p)
{
    if (tag[p])
        update_val(lson, tag_val[p]), update_val(rson, tag_val[p]), tag[p] = false;
    if (rev[p])
        reverse(lson), reverse(rson), rev[p] = false;
}

int build(int l, int r, int fat)
{
    if (l > r)
        return 0;
    int mid = (l + r) >> 1, p = idx[mid];
    fa[p] = fat;
    if (l == r)
        newNode(p, seq[l]);
    lson = build(l, mid - 1, p), rson = build(mid + 1, r, p);
    val[p] = seq[mid], tag[p] = false, rev[p] = false;
    pushup(p);
    return p;
}

int check(int p) { return ch[fa[p]][1] == p; }

void rotate(int x)
{
    int y = fa[x], z = fa[y], dir = check(x), w = ch[x][dir ^ 1];
    fa[x] = z;
    if (z != 0)
        ch[z][ch[z][1] == y] = x;
    fa[w] = y, ch[y][dir] = w;
    fa[y] = x, ch[x][dir ^ 1] = y;
    pushup(y), pushup(x);
}

void splay(int p, int goal = 0)
{
    for (int fat = fa[p]; (fat = fa[p]) != goal; rotate(p))
        if (fa[fat] != goal)
            rotate(check(p) == check(fat) ? fat : p);
    if (goal == 0)
        root = p;
}

int atRank(int k)
{
    int p = root;
    while (true)
    {
        pushdown(p);
        if (k <= siz[lson])
            p = lson;
        else
        {
            k -= siz[lson] + 1;
            if (k <= 0)
                return p;
            p = rson;
        }
    }
}

void remove(int p)
{
    if (lson)
        remove(lson);
    if (rson)
        remove(rson);
    recBin.push(p), clear(p);
}

int split(int pos, int len)
{
    int l = atRank(pos), r = atRank(pos + len + 1);
    splay(l), splay(r, l);
    return ch[r][0];
}

int main()
{
    scanf("%d%d", &n, &q);
    for (int i = 1; i <= n; i++)
        scanf("%d", &seq[i + 1]), idx[i] = i;
    msum[0] = seq[1] = seq[n + 2] = -INF, idx[n + 1] = n + 1, idx[n + 2] = n + 2;
    root = build(1, n + 2, 0), ptot = n + 2;
    while (q--)
    {
        scanf("%s", cmd + 1);
        if (cmd[1] == 'I')
        {
            // insert;
            int tot, posi;
            scanf("%d%d", &posi, &tot);
            for (int i = 1; i <= tot; i++)
                scanf("%d", &seq[i]), idx[i] = newNodeId();
            int rot = build(1, tot, 0), l = atRank(posi + 1), r = atRank(posi + 2);
            splay(l), splay(r, l);
            fa[rot] = r, ch[r][0] = rot;
            pushup(r), pushup(l);
        }
        else if (cmd[1] == 'D')
        {
            int tot, posi;
            scanf("%d%d", &posi, &tot);
            int node = split(posi, tot), f = fa[node];
            remove(node), ch[f][0] = 0;
            pushup(f), pushup(fa[f]);
        }
        else if (cmd[1] == 'M' && cmd[3] == 'K')
        {
            int tot, posi, ci, node, f;
            scanf("%d%d%d", &posi, &tot, &ci), node = split(posi, tot), f = fa[node];
            update_val(node, ci), pushup(f), pushup(fa[f]);
        }
        else if (cmd[1] == 'M')
        {
            printf("%d\n", msum[root]);
        }
        else if (cmd[1] == 'R')
        {
            int tot, posi;
            scanf("%d%d", &posi, &tot);
            int node = split(posi, tot), f = fa[node];
            if (tag[node])
                continue;
            reverse(node), pushup(f), pushup(fa[f]);
        }
        else if (cmd[1] == 'G')
        {
            int tot, posi;
            scanf("%d%d", &posi, &tot);
            int node = split(posi, tot);
            printf("%d\n", sum[node]);
        }
    }
    return 0;
}