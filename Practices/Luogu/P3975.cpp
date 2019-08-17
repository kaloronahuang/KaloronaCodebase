// P3975.cpp
#include <bits/stdc++.h>

using namespace std;

const int MAX_N = 1e6 + 7;

struct node
{
    int dep, link, size, dp;
    int ch[27];
} nodes[MAX_N << 1];

struct edge
{
    int to, nxt;
} edges[MAX_N << 1];

int head[MAX_N << 1], current, tot, last_cur, t, rk, n;
int rgt[MAX_N << 1], sum[MAX_N << 1];
char str[MAX_N];

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

void insert(int ch)
{
    int cur = ++tot;
    nodes[cur].dep = nodes[last_cur].dep + 1;
    rgt[cur] = 1;
    int p = last_cur;
    while (p && nodes[p].ch[ch] == 0)
    {
        nodes[p].ch[ch] = cur;
        p = nodes[p].link;
    }

    if (p == 0)
        nodes[cur].link = 1;
    else
    {
        int q = nodes[p].ch[ch];

        if (nodes[p].dep + 1 == nodes[q].dep)
            nodes[cur].link = q;
        else
        {
            int clone = ++tot;
            nodes[clone].dep = nodes[p].dep + 1;
            memcpy(nodes[clone].ch, nodes[q].ch, sizeof(nodes[q].ch));
            nodes[clone].link = nodes[q].link;
            while (p && nodes[p].ch[ch] == q)
            {
                nodes[p].ch[ch] = clone;
                p = nodes[p].link;
            }
            nodes[q].link = nodes[cur].link = clone;
        }
    }

    last_cur = cur;
}

void dfs_right(int u)
{
    if (t == 0)
        rgt[u] = 1;
    for (int i = head[u]; i != -1; i = edges[i].nxt)
        dfs_right(edges[i].to), rgt[u] += ((t == 1) ? rgt[edges[i].to] : 0);
}

int dfs_sum(int u)
{
    if (sum[u] != -1)
        return sum[u];
    sum[u] = rgt[u];
    for (int i = 0; i < 26; i++)
        if (nodes[u].ch[i])
            sum[u] += dfs_sum(nodes[u].ch[i]);
    return sum[u];
}

void print(int u, int k)
{
    if (k <= rgt[u])
        return;
    k -= rgt[u];
    for (int i = 0; i < 26; i++)
        if (nodes[u].ch[i])
        {
            if (k > sum[nodes[u].ch[i]])
            {
                k -= sum[nodes[u].ch[i]];
                continue;
            }
            printf("%c", i + 'a');
            print(nodes[u].ch[i], k);
            return;
        }
}

int main()
{
    memset(head, -1, sizeof(head)), memset(sum, -1, sizeof(sum));
    sam_initialize();
    scanf("%s%d%d", str + 1, &t, &rk);
    n = strlen(str + 1);
    for (int i = 1; i <= n; i++)
        insert(str[i] - 'a');
    for (int i = 2; i <= tot; i++)
        addpath(nodes[i].link, i);
    dfs_right(1);
    rgt[1] = 0;
    dfs_sum(1);
    if (sum[1] < rk)
        printf("-1");
    else
        print(1, rk);
    return 0;
}

