// P2463.cpp
#include <bits/stdc++.h>

using namespace std;

const int MAX_N = 1e5 + 200;

struct node
{
    map<int, int> ch;
    int link, dep;
} nodes[MAX_N << 1];

int ptot = 1, last_ptr = 1, n, m, seq[MAX_N], head[MAX_N], current;
bool tag[MAX_N], settings[MAX_N];

struct edge
{
    int to, nxt;
} edges[MAX_N << 1];

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
    for (int i = head[u]; i != -1; i = edges[i].nxt)
        dfs(edges[i].to), settings[u] |= settings[edges[i].to];
    tag[u] &= settings[u];
}

int main()
{
    memset(head, -1, sizeof(head));
    scanf("%d%d", &n, &m);
    for (int i = 1; i <= m; i++)
        scanf("%d", &seq[i]);
    seq[0] = seq[1];
    for (int i = 1; i <= m; i++)
        insert(seq[i] - seq[i - 1]);

    for (int i = 1; i <= ptot; i++)
        addpath(nodes[i].link, i);
    memset(tag, true, sizeof(tag));
    for (int T = 2; T <= n; T++)
    {
        memset(settings, false, sizeof(settings));
        scanf("%d", &m);
        for (int i = 1; i <= m; i++)
            scanf("%d", &seq[i]);
        seq[0] = seq[1];
        for (int i = 1, p = 1; i <= m; i++)
        {
            int c = seq[i] - seq[i - 1];
            while (p && nodes[p].ch[c] == 0)
                p = nodes[p].link;
            if (p == 0)
                p = 1;
            else
                p = nodes[p].ch[c];
            settings[p] = true;
        }
        dfs(1);
    }
    int ans = 0;
    for (int i = 1; i <= ptot; i++)
        if (tag[i])
            ans = max(ans, nodes[i].dep);
    printf("%d\n", ans);
    return 0;
}