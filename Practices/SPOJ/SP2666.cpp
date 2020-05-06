// SP2666.cpp
#include <bits/stdc++.h>

using namespace std;

const int MAX_N = 4e5 + 200, INF = 0x3f3f3f3f;

int n, head[MAX_N], current, q;
int ch[MAX_N][2], fa[MAX_N], sum[MAX_N], col[MAX_N], len[MAX_N], lmx[MAX_N], rmx[MAX_N];
int cmx[MAX_N], w[MAX_N], ans;
multiset<int> vchain[MAX_N], vpath[MAX_N];
char cmdlet[20];

#define lson (ch[p][0])
#define rson (ch[p][1])

struct edge
{
    int to, nxt, weight;
} edges[MAX_N << 1];

void addpath(int src, int dst, int weight)
{
    edges[current].to = dst, edges[current].nxt = head[src];
    edges[current].weight = weight, head[src] = current++;
}

int check(int p) { return ch[fa[p]][1] == p; }

bool isRoot(int p) { return ch[fa[p]][0] != p && ch[fa[p]][1] != p; }

int first(multiset<int> &rhs) { return rhs.empty() ? -INF : *rhs.begin(); }

int second(multiset<int> &rhs) { return rhs.size() >= 2 ? *(++rhs.begin()) : -INF; }

void pushup(int p)
{
    sum[p] = sum[lson] + sum[rson] + len[p];
    int vchain_len = max(w[p], first(vchain[p]));
    int lft = max(vchain_len, rmx[lson] + len[p]), rig = max(vchain_len, lmx[rson]);
    lmx[p] = max(lmx[lson], sum[lson] + len[p] + rig);
    rmx[p] = max(rmx[rson], sum[rson] + lft);
    cmx[p] = max({rmx[lson] + len[p] + rig, lmx[rson] + lft, cmx[lson], cmx[rson], first(vpath[p]), first(vchain[p]) + second(vchain[p])});
    if (w[p] == 0)
        cmx[p] = max(cmx[p], max(0, first(vchain[p])));
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

void splay(int p)
{
    for (int fat = fa[p]; fat = fa[p], !isRoot(p); rotate(p))
        if (!isRoot(fat))
            rotate(check(p) == check(fat) ? fat : p);
}

void access(int p)
{
    for (int pre = 0; p; pre = p, p = fa[p])
    {
        splay(p);
        if (rson)
            vpath[p].insert(cmx[rson]), vchain[p].insert(lmx[rson]);
        if (pre)
            vpath[p].erase(vpath[p].find(cmx[pre])), vchain[p].erase(vchain[p].find(lmx[pre]));
        rson = pre, pushup(p);
    }
}

void modify(int p)
{
    access(p), splay(p), col[p] ^= 1;
    w[p] = col[p] ? -INF : 0;
    pushup(p), ans = cmx[p];
}

void dfs(int u, int fat)
{
    for (int i = head[u]; i != -1; i = edges[i].nxt)
        if (edges[i].to != fat)
        {
            fa[edges[i].to] = u;
            len[edges[i].to] = edges[i].weight, dfs(edges[i].to, u);
            vchain[u].insert(lmx[edges[i].to]), vpath[u].insert(cmx[edges[i].to]);
        }
    pushup(u);
}

int main()
{
    memset(head, -1, sizeof(head));
    scanf("%d", &n);
    for (int i = 1, u, v, w; i <= n - 1; i++)
        scanf("%d%d%d", &u, &v, &w), addpath(u, v, w), addpath(v, u, w);
    for (int i = 0; i <= n; i++)
        lmx[i] = rmx[i] = cmx[i] = -INF;
    dfs(1, 0), ans = cmx[1], scanf("%d", &q);
    while (q--)
    {
        scanf("%s", cmdlet + 1);
        int x;
        if (cmdlet[1] == 'C')
            scanf("%d", &x), modify(x);
        else
            ans < 0 ? puts("They have disappeared.") : printf("%d\n", ans);
    }
    return 0;
}