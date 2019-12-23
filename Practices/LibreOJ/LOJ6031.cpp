// LOJ6031.cpp
#include <bits/stdc++.h>

using namespace std;

const int MAX_N = 2e6 + 200, block_size = 330;

int head[MAX_N], current, fa[20][MAX_N], li[MAX_N], ri[MAX_N], m, n, q, k;
int cpos[MAX_N], clen[MAX_N];
char str[MAX_N], w[MAX_N];

struct edge
{
    int to, nxt;
} edges[MAX_N << 1];

void addpath(int src, int dst)
{
    edges[current].to = dst, edges[current].nxt = head[src];
    head[src] = current++;
}

namespace SAM
{

struct node
{
    int ch[26], link, dep, siz;
} nodes[MAX_N << 1];

int ptot = 1, last_ptr = 1;

void insert(int c)
{
    int pre = last_ptr, p = last_ptr = ++ptot;
    nodes[p].dep = nodes[pre].dep + 1, nodes[p].siz = 1;
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
            nodes[p].link = nodes[q].link = clone, nodes[clone].siz = 0;
            while (pre && nodes[pre].ch[c] == q)
                nodes[pre].ch[c] = clone, pre = nodes[pre].link;
        }
    }
}

void build_graph()
{
    for (int i = 1; i <= ptot; i++)
        if (nodes[i].link != 0)
            addpath(nodes[i].link, i), fa[0][i] = nodes[i].link;
}

void dfs(int u)
{
    for (int i = 1; i <= 19; i++)
        fa[i][u] = fa[i - 1][fa[i - 1][u]];
    for (int i = head[u]; i != -1; i = edges[i].nxt)
        dfs(edges[i].to), nodes[u].siz += nodes[edges[i].to].siz;
}

} // namespace SAM

void solve1()
{
    vector<int> buc[block_size][block_size];
    for (int i = 1; i <= m; i++)
        buc[li[i]][ri[i]].push_back(i);
    while (q--)
    {
        int a, b;
        long long ans = 0;
        scanf("%s%d%d", w + 1, &a, &b);
        a++, b++;
        for (int i = 1; i <= k; i++)
            for (int j = i, p = 1; j <= k; j++)
            {
                p = SAM::nodes[p].ch[w[j] - 'a'];
                if (p == 0)
                    break;
                int l = lower_bound(buc[i][j].begin(), buc[i][j].end(), a) - buc[i][j].begin();
                int r = upper_bound(buc[i][j].begin(), buc[i][j].end(), b) - buc[i][j].begin();
                ans += 1LL * (r - l) * SAM::nodes[p].siz;
            }
        printf("%lld\n", ans);
    }
}

void solve2()
{
    while (q--)
    {
        int a, b;
        long long ans = 0;
        scanf("%s%d%d", w + 1, &a, &b);
        a++, b++;
        for (int i = 1, p = 1, len = 0; i <= k; i++)
        {
            while (p && SAM::nodes[p].ch[w[i] - 'a'] == 0)
                p = SAM::nodes[p].link, len = SAM::nodes[p].dep;
            if (p == 0)
                p = 1;
            else
                p = SAM::nodes[p].ch[w[i] - 'a'];
            len += (p != 1);
            cpos[i] = p, clen[i] = len;
        }
        for (int idx = a; idx <= b; idx++)
        {
            int p = cpos[ri[idx]], dist = ri[idx] - li[idx] + 1;
            if (dist > clen[ri[idx]])
                continue;
            else if (dist == clen[ri[idx]])
            {
                ans += SAM::nodes[p].siz;
                continue;
            }
            for (int i = 19; i >= 0; i--)
                if (fa[i][p] && SAM::nodes[fa[i][p]].dep >= dist)
                    p = fa[i][p];
            ans += SAM::nodes[p].siz;
        }
        printf("%lld\n", ans);
    }
}

int main()
{
    memset(head, -1, sizeof(head));
    scanf("%d%d%d%d%s", &n, &m, &q, &k, str + 1);
    for (int i = 1; i <= n; i++)
        SAM::insert(str[i] - 'a');
    SAM::build_graph(), SAM::dfs(1);
    for (int i = 1; i <= m; i++)
        scanf("%d%d", &li[i], &ri[i]), li[i]++, ri[i]++;
    if (1LL * k <= block_size)
        solve1();
    else
        solve2();
    return 0;
}