// C.cpp
#include <bits/stdc++.h>
#pragma GCC target("avx")
#pragma GCC optimize(2)
%:pragma GCC optimize(3)
%:pragma GCC optimize("Ofast")
%:pragma GCC optimize("inline")
%:pragma GCC optimize("-fgcse")
%:pragma GCC optimize("-fgcse-lm")
%:pragma GCC optimize("-fipa-sra")
%:pragma GCC optimize("-ftree-pre")
%:pragma GCC optimize("-ftree-vrp")
%:pragma GCC optimize("-fpeephole2")
%:pragma GCC optimize("-ffast-math")
%:pragma GCC optimize("-fsched-spec")
%:pragma GCC optimize("unroll-loops")
%:pragma GCC optimize("-falign-jumps")
%:pragma GCC optimize("-falign-loops")
%:pragma GCC optimize("-falign-labels")
%:pragma GCC optimize("-fdevirtualize")
%:pragma GCC optimize("-fcaller-saves")
%:pragma GCC optimize("-fcrossjumping")
%:pragma GCC optimize("-fthread-jumps")
%:pragma GCC optimize("-funroll-loops")
%:pragma GCC optimize("-fwhole-program")
%:pragma GCC optimize("-freorder-blocks")
%:pragma GCC optimize("-fschedule-insns")
%:pragma GCC optimize("inline-functions")
%:pragma GCC optimize("-ftree-tail-merge")
%:pragma GCC optimize("-fschedule-insns2")
%:pragma GCC optimize("-fstrict-aliasing")
%:pragma GCC optimize("-fstrict-overflow")
%:pragma GCC optimize("-falign-functions")
%:pragma GCC optimize("-fcse-skip-blocks")
%:pragma GCC optimize("-fcse-follow-jumps")
%:pragma GCC optimize("-fsched-interblock")
%:pragma GCC optimize("-fpartial-inlining")
%:pragma GCC optimize("no-stack-protector")
%:pragma GCC optimize("-freorder-functions")
%:pragma GCC optimize("-findirect-inlining")
%:pragma GCC optimize("-fhoist-adjacent-loads")
%:pragma GCC optimize("-frerun-cse-after-loop")
%:pragma GCC optimize("inline-small-functions")
%:pragma GCC optimize("-finline-small-functions")
%:pragma GCC optimize("-ftree-switch-conversion")
%:pragma GCC optimize("-foptimize-sibling-calls")
%:pragma GCC optimize("-fexpensive-optimizations")
%:pragma GCC optimize("-funsafe-loop-optimizations")
%:pragma GCC optimize("inline-functions-called-once")
%:pragma GCC optimize("-fdelete-null-pointer-checks")
#define lson ch[p][0]
#define rson ch[p][1]

using namespace std;

const int MAX_N = 1e5 + 200, INF = 0x3f3f3f3f;

int ch[MAX_N][2], fa[MAX_N], val[MAX_N], minVal[MAX_N], revTag[MAX_N];
int size[MAX_N], n, m, mem[MAX_N], sta[MAX_N];

#define rint register int

void write(int x){
    if(x>9) write(x/10);
    putchar(x%10+'0');
}

inline char nc()
{
    static char buf[100001], *p1 = buf, *p2 = buf;
    return p1 == p2 && (p2 = (p1 = buf) + fread(buf, 1, 100000, stdin), p1 == p2) ? EOF : *p1++;
}

inline int read()
{
    rint num = 0;
    char c;
    while (isspace(c = nc()))
        ;
    while (num = num * 10 + c - 48, isdigit(c = nc()))
        ;
    return num;
}

inline bool isRoot(rint p)
{
    return ch[fa[p]][0] != p && ch[fa[p]][1] != p;
}

inline int check(rint p) { return ch[fa[p]][1] == p; }

inline void clear(rint p) { lson = rson = fa[p] = val[p] = size[p] = revTag[p] = minVal[p] = 0; }

inline void pushUp(rint p)
{
    clear(0);
    size[p] = 1 + size[lson] + size[rson];
    minVal[p] = val[p];
    if (lson)
        minVal[p] = min(minVal[p], minVal[lson]);
    if (rson)
        minVal[p] = min(minVal[p], minVal[rson]);
}

inline void pushDown(rint p)
{
    if (revTag[p])
    {
        if (lson)
            revTag[lson] ^= 1, swap(ch[lson][0], ch[lson][1]);
        if (rson)
            revTag[rson] ^= 1, swap(ch[rson][0], ch[rson][1]);
        revTag[p] = 0;
    }
}

inline void update(rint x)
{
    rint tot = 0;
    sta[++tot] = x;
    while (!isRoot(x))
        x = fa[x], sta[++tot] = x;
    while (tot)
        pushDown(sta[tot--]);
}

inline void rotate(rint x)
{
    rint y = fa[x], z = fa[y], dir = check(x), w = ch[x][dir ^ 1];
    fa[x] = z;
    if (!isRoot(y))
        ch[z][check(y)] = x;
    ch[y][dir] = w, fa[w] = y;
    ch[x][dir ^ 1] = y, fa[y] = x;
    pushUp(y), pushUp(x), pushUp(z);
}

inline void splay(rint x)
{
    update(x);
    for (rint fat = fa[x]; fat = fa[x], !isRoot(x); rotate(x))
        if (!isRoot(fat))
            rotate(check(fat) == check(x) ? fat : x);
}

inline int access(rint x)
{
    rint fat = 0;
    for (; x != 0; fat = x, x = fa[x])
        splay(x), ch[x][1] = fat, pushUp(x);
    return fat;
}

inline void makeRoot(rint p)
{
    access(p), splay(p);
    swap(lson, rson), revTag[p] ^= 1;
}

inline int find(rint p)
{
    access(p), splay(p);
    while (lson)
        p = lson;
    splay(p);
    return p;
}

inline void link(rint x, rint y)
{
    makeRoot(x);
    if (find(y) == x)
        return;
    fa[x] = y;
}

inline void split(rint x, rint y)
{
    makeRoot(x);
    access(y), splay(y);
}

inline int lca(rint x, rint y)
{
    access(x);
    return access(y);
}

inline int findFa(rint x) { return mem[x] == x ? x : mem[x] = findFa(mem[x]); }

int main()
{
    /*
    freopen("money.in", "r", stdin);
    freopen("money.out", "w", stdout);
    */

    rint lastans = 0;
    n = read(), m = read();
    for (rint i = 1; i <= n; i++)
        mem[i] = i, val[i] = minVal[i] = INF;
    while (m--)
    {
        rint opt, a, b, c;
        opt = read(), a = read(), b = read();
        a = (a + lastans) % n + 1;
        b = (b + lastans) % n + 1;
        if (opt == 0)
        {
            c = read(), c = (c + lastans) % n + 1;
            mem[findFa(a)] = findFa(b);
            val[a] = minVal[a] = c;
            link(a, b);
        }
        else
        {
            if (findFa(a) != findFa(b))
            {
                write(lastans = 0), puts("");
                continue;
            }
            if (lca(a, b) == b)
            {
                rint root = findFa(b);
                split(a, b);
                write(lastans = minVal[ch[b][0]]), puts("");
                makeRoot(root);
            }
            else
                write(lastans = 0), puts("");
        }
    }
    return 0;
}