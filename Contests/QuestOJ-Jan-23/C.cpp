// C.cpp
#include <bits/stdc++.h>

using namespace std;

const int MAX_N = 4e5 + 200, bitnum = 133;
typedef unsigned long long ull;

int n, ch[MAX_N][27], fa[20][MAX_N], dep[MAX_N], str[MAX_N];
ull up[20][MAX_N], pownum[MAX_N];

namespace SubtaskChain
{

struct node
{
    int ch[27], dep, link, max_son;
} nodes[MAX_N << 1];

int idx[MAX_N << 1], bucket[MAX_N << 1], last_ptr = 1, ptot = 1, pos[MAX_N << 1];
int head[MAX_N << 1], current;

struct edge
{
    int to, nxt;
} edges[MAX_N << 2];

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

int gans = 0;

void dfs(int u)
{
    int lcsLength = nodes[u].dep;
    int mx_len = -1, second_mx_len = -1;
    for (int i = head[u]; i != -1; i = edges[i].nxt)
        if (nodes[edges[i].to].max_son >= mx_len)
            swap(mx_len, second_mx_len), mx_len = nodes[edges[i].to].max_son;
        else if (nodes[edges[i].to].max_son >= second_mx_len)
            second_mx_len = nodes[edges[i].to].max_son;
    if (second_mx_len != -1)
        gans = max(gans, lcsLength + min(mx_len, second_mx_len));
    for (int i = head[u]; i != -1; i = edges[i].nxt)
        dfs(edges[i].to);
}

void ChainHandler()
{
    memset(head, -1, sizeof(head));
    for (int i = 1; i <= n - 1; i++)
        insert(str[i]), pos[i] = last_ptr, nodes[last_ptr].max_son = i;
    for (int i = 1; i <= ptot; i++)
        bucket[nodes[i].dep]++;
    for (int i = 1; i <= ptot; i++)
        bucket[i] += bucket[i - 1];
    for (int i = 1; i <= ptot; i++)
        idx[bucket[nodes[i].dep]--] = i;
    for (int i = ptot; i >= 1; i--)
        if (nodes[idx[i]].link != 0)
        {
            nodes[nodes[idx[i]].link].max_son = max(nodes[nodes[idx[i]].link].max_son, nodes[idx[i]].max_son);
            addpath(nodes[idx[i]].link, idx[i]);
        }
    // well done;
    dfs(1), printf("%d\n", gans);
}

} // namespace SubtaskChain

void dfs(int u)
{
    dep[u] = dep[fa[0][u]] + 1;
    for (int i = 0; i < 27; i++)
        if (ch[u][i])
            dfs(ch[u][i]);
}

int getLCA(int x, int y)
{
    if (dep[x] < dep[y])
        swap(x, y);
    for (int i = 19; i >= 0; i--)
        if (dep[fa[i][x]] >= dep[y])
            x = fa[i][x];
    if (x == y)
        return x;
    for (int i = 19; i >= 0; i--)
        if (fa[i][x] != fa[i][y])
            x = fa[i][x], y = fa[i][y];
    return fa[0][x];
}

int main()
{
    // freopen("trie4.in", "r", stdin);
    bool chainFlag = true;
    scanf("%d", &n);
    for (int i = 2, fat, color; i <= n; i++)
        scanf("%d%d", &fat, &color), ch[fat][color] = i, fa[0][i] = fat, chainFlag &= (fat == i - 1), str[i - 1] = color, up[0][i] = color;
    if (chainFlag)
        SubtaskChain::ChainHandler(), exit(0);
    for (int i = pownum[0] = 1; i <= n; i++)
        pownum[i] = pownum[i - 1] * bitnum;
    for (int i = 1; i <= 19; i++)
        for (int j = 1; j <= n; j++)
            fa[i][j] = fa[i - 1][fa[i - 1][j]], up[i][j] = up[i - 1][fa[i - 1][j]] * pownum[1 << (i - 1)] + up[i - 1][j];
    int gans = 0;
    dfs(1);
    for (int i = 1; i <= n; i++)
        for (int j = i + 1; j <= n; j++)
        {
            int pans = dep[getLCA(i, j)] - 1;
            int x = i, y = j;
            for (int i = 19; i >= 0; i--)
                if ((1 << i) < dep[x] && (1 << i) < dep[y] && up[i][x] == up[i][y])
                    pans += (1 << i), x = fa[i][x], y = fa[i][y];
            gans = max(gans, pans);
        }
    printf("%d\n", gans);
    return 0;
}