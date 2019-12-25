// P3346.cpp
#include <bits/stdc++.h>

using namespace std;

const int MAX_N = 4e6 + 200;

int head[MAX_N], current, n, ctot, val[MAX_N], deg[MAX_N];

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
    int ch[10], dep, link;
} nodes[MAX_N];

int ptot = 1, last_ptr = 1;

int insert(int pre, int c)
{
    if (nodes[pre].ch[c] == 0)
    {
        int p = last_ptr = ++ptot;
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
                nodes[q].link = nodes[p].link = clone;
                while (pre && nodes[pre].ch[c] == q)
                    nodes[pre].ch[c] = clone, pre = nodes[pre].link;
            }
        }
    }
    else
    {
        int q = nodes[pre].ch[c];
        if (nodes[q].dep == nodes[pre].dep + 1)
            last_ptr = q;
        else
        {
            int clone = last_ptr = ++ptot;
            nodes[clone] = nodes[q], nodes[clone].dep = nodes[pre].dep + 1;
            nodes[q].link = clone;
            while (pre && nodes[pre].ch[c] == q)
                nodes[pre].ch[c] = clone, pre = nodes[pre].link;
        }
    }

    return last_ptr;
}

void dfs(int u, int fa, int p)
{
    int pt = insert(p, val[u]);
    for (int i = head[u]; i != -1; i = edges[i].nxt)
        if (edges[i].to != fa)
            dfs(edges[i].to, u, pt);
}

long long calc()
{
    long long ans = 0;
    for (int i = 1; i <= ptot; i++)
        ans += nodes[i].dep - nodes[nodes[i].link].dep;
    return ans;
}

} // namespace SAM

int main()
{
    memset(head, -1, sizeof(head));
    scanf("%d%d", &n, &ctot);
    for (int i = 1; i <= n; i++)
        scanf("%d", &val[i]);
    for (int i = 1, u, v; i <= n - 1; i++)
        scanf("%d%d", &u, &v), addpath(u, v), addpath(v, u), deg[u]++, deg[v]++;
    for (int i = 1; i <= n; i++)
        if (deg[i] == 1)
            SAM::dfs(i, 0, 1);
    printf("%lld\n", SAM::calc());
    return 0;
}