// P3804.cpp
#include <bits/stdc++.h>

using namespace std;

const int MAX_N = 2e6 + 200;

int n, head[MAX_N], current;
long long ans = 0;
char str[MAX_N];

struct edge
{
    int to, nxt;
} edges[MAX_N << 1];

struct node
{
    int dep, link, dp;
    int child[26];
} nodes[MAX_N];
int tot, last_cur;

void addpath(int src, int dst)
{
    edges[current].to = dst, edges[current].nxt = head[src];
    head[src] = current++;
}

void sam_initialize()
{
    nodes[++tot].dep = 0, nodes[tot].link = 0;
    last_cur = tot;
}

void insert(char ch)
{
    int cur = ++tot;
    nodes[cur].dep = nodes[last_cur].dep + 1;
    nodes[cur].dp = 1;
    int p = last_cur;
    while (p && nodes[p].child[ch] == 0)
    {
        nodes[p].child[ch] = cur;
        p = nodes[p].link;
    }
    if (p == 0)
        nodes[cur].link = 1;
    else
    {
        int q = nodes[p].child[ch];
        if (nodes[p].dep + 1 == nodes[q].dep)
            nodes[cur].link = q;
        else
        {
            int clone = ++tot;
            nodes[clone].dep = nodes[p].dep + 1;
            memcpy(nodes[clone].child, nodes[q].child, sizeof(nodes[q].child));
            nodes[clone].link = nodes[q].link;
            while (p && nodes[p].child[ch] == q)
            {
                nodes[p].child[ch] = clone;
                p = nodes[p].link;
            }
            nodes[q].link = nodes[cur].link = clone;
        }
    }

    last_cur = cur;
}

void dfs(int u)
{
    for (int i = head[u]; i != -1; i = edges[i].nxt)
        if (edges[i].to != nodes[u].link)
            dfs(edges[i].to), nodes[u].dp += nodes[edges[i].to].dp;
    if (nodes[u].dp != 1)
        ans = max(ans, 1LL * nodes[u].dp * nodes[u].dep);
}

int main()
{
    memset(head, -1, sizeof(head));
    sam_initialize();
    scanf("%s", str + 1);
    n = strlen(str + 1);
    for (int i = 1; i <= n; i++)
        insert(str[i] - 'a');
    for (int i = 2; i <= tot; i++)
        addpath(nodes[i].link, i);
    dfs(1);
    printf("%lld", ans);
    return 0;
}
