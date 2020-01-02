// P2178.cpp
#include <bits/stdc++.h>

using namespace std;

const int MAX_N = 6e5 + 200;
typedef long long ll;
const ll INF = 0x3f3f3f3f3f3f3f3f;

struct node
{
    int ch[26], link, dep, siz;
} nodes[MAX_N << 1];

int last_ptr = 1, ptot = 1, head[MAX_N], current, n;
ll ai[MAX_N], max_val[MAX_N], min_val[MAX_N];
char str[MAX_N];
ll ans1[MAX_N], ans2[MAX_N];

struct edge
{
    int to, nxt;
} edges[MAX_N];

void addpath(int src, int dst)
{
    edges[current].to = dst, edges[current].nxt = head[src];
    head[src] = current++;
}

void insert(int c, int idx)
{
    int pre = last_ptr, p = last_ptr = ++ptot;
    nodes[p].dep = nodes[pre].dep + 1, nodes[p].siz = 1;
    min_val[p] = max_val[p] = ai[idx];
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

void init_tree()
{
    for (int i = 1; i <= ptot; i++)
        if (nodes[i].link != 0)
            addpath(nodes[i].link, i);
}

bool check(int u) { return max_val[u] != -INF && min_val[u] != INF; }

void dfs(int u)
{
    if (max_val[u] == 0 && min_val[u] == 0)
        max_val[u] = -INF, min_val[u] = INF;
    for (int i = head[u]; i != -1; i = edges[i].nxt)
    {
        dfs(edges[i].to);
        if (check(u) && check(edges[i].to))
            ans2[nodes[u].dep] = max(ans2[nodes[u].dep], max(1LL * max_val[u] * max_val[edges[i].to], 1LL * min_val[u] * min_val[edges[i].to]));
        ans1[nodes[u].dep] += 1LL * nodes[u].siz * nodes[edges[i].to].siz;
        nodes[u].siz += nodes[edges[i].to].siz;
        max_val[u] = max(max_val[u], max_val[edges[i].to]);
        min_val[u] = min(min_val[u], min_val[edges[i].to]);
    }
}

int main()
{
    memset(head, -1, sizeof(head));
    scanf("%d%s", &n, str + 1);
    for (int i = 1; i <= n; i++)
        scanf("%lld", &ai[i]);
    ans2[0] = -INF;
    for (int i = n; i >= 1; i--)
    {
        int ch = str[i] - 'a';
        ans2[i] = -INF, insert(ch, i);
    }
    init_tree(), dfs(1);
    for (int i = n - 1; i >= 0; i--)
        ans2[i] = max(ans2[i], ans2[i + 1]), ans1[i] += ans1[i + 1];
    for (int i = 0; i < n; i++)
        if (ans1[i] != 0)
            printf("%lld %lld\n", ans1[i], ans2[i]);
        else
            puts("0 0");
    return 0;
}