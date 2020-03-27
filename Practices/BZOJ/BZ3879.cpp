// BZ3879.cpp
#include <bits/stdc++.h>

using namespace std;

const int MAX_N = 1e6 + 200;

typedef long long ll;

const ll mod = 23333333333333333;

int n, m, last_ptr = 1, ptot = 1, pos[MAX_N], fa[MAX_N], head[MAX_N], current;
int stot, st[20][MAX_N << 1], log2_[MAX_N << 1], dep[MAX_N], lca_pos[MAX_N], dfn[MAX_N], dtot;
int vseq[MAX_N * 13], vsiz;
char str[MAX_N * 3];

struct edge
{
    int to, nxt;
} edges[MAX_N * 5];

struct node
{
    int ch[26], link, dep;
} nodes[MAX_N];

void addpath(int src, int dst)
{
    edges[current].to = dst, edges[current].nxt = head[src];
    head[src] = current++;
}

void insert(int c)
{
    int pre = last_ptr, p = last_ptr = ++ptot;
    nodes[p].dep = nodes[pre].dep + 1;
    while (pre && nodes[pre].ch[c] == 0)
        nodes[pre].ch[c] = p, pre = nodes[pre].link;
    if (pre == 0)
        nodes[p].link = 1;
    else
    {
        int q = nodes[pre].ch[c];
        if (nodes[q].dep == nodes[pre].dep + 1)
            nodes[p].link = q;
        else
        {
            int clone = ++ptot;
            nodes[clone] = nodes[q], nodes[clone].dep = nodes[pre].dep + 1;
            nodes[p].link = nodes[q].link = clone;
            while (pre && nodes[pre].ch[c] == q)
                nodes[pre].ch[c] = clone, pre = nodes[pre].link;
        }
    }
}

void dfs(int u)
{
    st[0][++stot] = u, dfn[u] = ++dtot;
    lca_pos[u] = stot, dep[u] = dep[fa[u]] + 1;
    for (int i = head[u]; i != -1; i = edges[i].nxt)
        fa[edges[i].to] = u, dfs(edges[i].to), st[0][++stot] = u;
}

int gmin(int x, int y) { return dep[x] < dep[y] ? x : y; }

int getLCA(int x, int y)
{
    if (lca_pos[x] > lca_pos[y])
        swap(x, y);
    int d = log2_[lca_pos[y] - lca_pos[x] + 1];
    return gmin(st[d][lca_pos[x]], st[d][lca_pos[y] - (1 << d) + 1]);
}

namespace vtree
{

int ghead[MAX_N], siz[MAX_N], stk[MAX_N];
ll ans;

void addpath_g(int src, int dst)
{
    if (src == dst)
        return;
    edges[current].to = dst, edges[current].nxt = ghead[src];
    ghead[src] = current++;
}

void gdfs(int u)
{
    for (int i = ghead[u]; i != -1; i = edges[i].nxt)
    {
        gdfs(edges[i].to), ans += 1LL * nodes[u].dep * siz[edges[i].to] % mod * siz[u] % mod;
        siz[u] += siz[edges[i].to], ghead[edges[i].to] = -1, siz[edges[i].to] = 0;
    }
}

void build_virtual_tree()
{
    int org_current = current, tail = 0;
    stk[++tail] = 1;
    for (int i = 1; i <= vsiz; i++)
    {
        int lca = getLCA(vseq[i], stk[tail]);
        siz[vseq[i]] = 1;
        while (tail > 1 && dep[stk[tail - 1]] > dep[lca])
            addpath_g(stk[tail - 1], stk[tail]), tail--;
        if (dep[stk[tail]] > dep[lca])
            addpath_g(lca, stk[tail]), tail--;
        if (lca != stk[tail])
            stk[++tail] = lca;
        stk[++tail] = vseq[i];
    }
    while (tail > 1)
        addpath_g(stk[tail - 1], stk[tail]), tail--;
    ans = 0, gdfs(1), ghead[1] = -1, siz[1] = 0, current = org_current;
}

} // namespace vtree

int main()
{
    memset(head, -1, sizeof(head)), memset(vtree::ghead, -1, sizeof(vtree::ghead));
    scanf("%d%d%s", &n, &m, str + 1);
    for (int i = 1; i <= n; i++)
        insert(str[n - i + 1] - 'a'), pos[i] = last_ptr;
    for (int i = 1; i <= ptot; i++)
        if (nodes[i].link != 0)
            addpath(nodes[i].link, i);
    dfs(1);
    for (int i = 2; i <= stot; i++)
        log2_[i] = log2_[i >> 1] + 1;
    for (int i = 1; i < 20; i++)
        for (int j = 1; j + (1 << i) - 1 <= stot; j++)
            st[i][j] = gmin(st[i - 1][j], st[i - 1][j + (1 << (i - 1))]);
    while (m--)
    {
        scanf("%d", &vsiz);
        for (int i = 1; i <= vsiz; i++)
            scanf("%d", &vseq[i]), vseq[i] = pos[n - vseq[i] + 1];
        sort(vseq + 1, vseq + 1 + vsiz, [](const int &a, const int &b) { return dfn[a] < dfn[b]; });
        vsiz = unique(vseq + 1, vseq + 1 + vsiz) - vseq - 1, vtree::build_virtual_tree();
        printf("%lld\n", vtree::ans);
    }
    return 0;
}