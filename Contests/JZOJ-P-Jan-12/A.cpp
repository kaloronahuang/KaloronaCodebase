// A.cpp
#include <bits/stdc++.h>

using namespace std;

const int MAX_N = 2e6 + 200, bitnum = 17;
typedef unsigned long long ull;

int n, q, head[MAX_N], current, sid[MAX_N], tp_tot, ans[MAX_N];
char str[MAX_N];
set<int> st[MAX_N];

struct edge
{
    int to, nxt;
} edges[MAX_N << 1];

struct triple
{
    int x, y, d;
    bool operator<(const triple &rhs) const { return x < rhs.x; }
} tps[MAX_N << 1], queries[MAX_N];

void addpath(int src, int dst)
{
    edges[current].to = dst, edges[current].nxt = head[src];
    head[src] = current++;
}

void fileIO()
{
    freopen("history.in", "r", stdin);
    freopen("history.out", "w", stdout);
}

struct node
{
    int ch[2], link, dep;
} nodes[MAX_N];

int roots[MAX_N], atPos[MAX_N], ptot = 1, last_ptr = 1;
int fa[20][MAX_N], tree[MAX_N];

inline int lowbit(int x) { return x & (-x); }

void update(int x, int d)
{
    for (; x <= n; x += lowbit(x))
        tree[x] = max(tree[x], d);
}

int query(int x, int ret = 0)
{
    for (; x; x -= lowbit(x))
        ret = max(ret, tree[x]);
    return ret;
}

void insert(int c, int pos)
{
    int pre = last_ptr, p = last_ptr = ++ptot;
    nodes[p].dep = nodes[pre].dep + 1, st[p].insert(pos);
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
            nodes[q].link = nodes[p].link = clone;
            while (pre && nodes[pre].ch[c] == q)
                nodes[pre].ch[c] = clone, pre = nodes[pre].link;
        }
    }
}

void dfs(int u)
{
    for (int i = head[u]; i != -1; i = edges[i].nxt)
    {
        dfs(edges[i].to);
        if (st[sid[edges[i].to]].size() > st[sid[u]].size())
            swap(sid[edges[i].to], sid[u]);
        for (set<int>::iterator it = st[sid[edges[i].to]].begin(); it != st[sid[edges[i].to]].end(); it++)
        {
            set<int>::iterator tmp = st[sid[u]].upper_bound(*it);
            if (tmp != st[sid[u]].end())
                tps[++tp_tot] = triple{*it, *tmp, nodes[u].dep};
            if (tmp != st[sid[u]].begin())
                tps[++tp_tot] = triple{*(--tmp), *it, nodes[u].dep};
            st[sid[u]].insert(*it);
        }
    }
}

int main()
{
    memset(head, -1, sizeof(head));
    // fileIO();
    scanf("%d%d%s", &n, &q, str + 1);
    for (int i = 1; i <= n; i++)
        insert(str[i] - '0', i);
    sid[1] = 1;
    for (int i = 2; i <= ptot; i++)
        addpath(nodes[i].link, i), sid[i] = i;
    dfs(1);
    for (int i = 1; i <= q; i++)
        scanf("%d%d", &queries[i].x, &queries[i].y), queries[i].d = i;
    sort(tps + 1, tps + 1 + tp_tot), sort(queries + 1, queries + 1 + q);
    int tp_ptr = tp_tot;
    for (int q_ptr = q; q_ptr >= 1; q_ptr--)
    {
        while (tp_ptr >= 1 && tps[tp_ptr].x >= queries[q_ptr].x)
            update(tps[tp_ptr].y, tps[tp_ptr].d), tp_ptr--;
        ans[queries[q_ptr].d] = query(queries[q_ptr].y);
    }
    for (int i = 1; i <= q; i++)
        printf("%d\n", ans[i]);
    return 0;
}