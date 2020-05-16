// LOJ3049.cpp
#include <bits/stdc++.h>

using namespace std;

const int MAX_N = 2e6 + 200;

typedef pair<int, int> pii;
typedef long long ll;

int T, n, na, nb, li[MAX_N], ri[MAX_N], nid[MAX_N], m, up[20][MAX_N], pos[MAX_N], load[MAX_N], ptot = 1, last_ptr = 1;
int bucket[MAX_N], rk[MAX_N], deg[MAX_N], head[MAX_N], current, weights[MAX_N], que[MAX_N];
ll dist[MAX_N];
vector<pii> matches[MAX_N];
vector<int> G[MAX_N];
set<pii> judger;
char str[MAX_N];

int read()
{
    int x = 0, f = 1;
    char ch = getchar();
    while (!isdigit(ch))
    {
        if (ch == '-')
            f = -1;
        ch = getchar();
    }
    while (isdigit(ch))
        x = (x << 3) + (x << 1) + ch - '0', ch = getchar();
    return x * f;
}

struct node
{
    int ch[26], dep, link;
} nodes[MAX_N];

struct edge
{
    int to, nxt, weight;
} edges[(MAX_N << 2) + MAX_N];

void addpath(int src, int dst, int weight)
{
    edges[current].to = dst, edges[current].nxt = head[src];
    edges[current].weight = weight, head[src] = current++, deg[dst]++;
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

void radixSort()
{
    for (int i = 1; i <= ptot; i++)
        bucket[nodes[i].dep]++;
    for (int i = 1; i <= n; i++)
        bucket[i] += bucket[i - 1];
    for (int i = 1; i <= ptot; i++)
        rk[bucket[nodes[i].dep]--] = i;
    for (int i = 1; i <= ptot; i++)
        if (nodes[i].link)
            G[nodes[i].link].push_back(i), up[0][i] = nodes[i].link;
    for (int i = 1; i < 20; i++)
        for (int j = 1; j <= ptot; j++)
            up[i][j] = up[i - 1][up[i - 1][j]];
}

int jump(int p, int len)
{
    for (int i = 19; i >= 0; i--)
        if (nodes[up[i][p]].dep >= len)
            p = up[i][p];
    pii cmp = make_pair(p, len);
    if (judger.find(cmp) == judger.end())
        judger.insert(cmp), load[p]++;
    return p;
}

void dfs(int u, int fa)
{
    if (fa)
        addpath(fa, u, 0);
    sort(matches[u].begin(), matches[u].end());
    int ptr = 0, pre = u;
    if (!matches[u].empty())
    {
        nid[matches[u][0].second] = u;
        for (int i = 1, siz_ = matches[u].size(); i < siz_; i++)
            if (matches[u][i].first != matches[u][i - 1].first)
            {
                ptr = i;
                break;
            }
            else
                nid[matches[u][i].second] = u;
    }
    while (load[u] > 1)
    {
        ptot++, load[u]--;
        nid[matches[u][ptr].second] = ptot;
        for (int i = ptr + 1, siz_ = matches[u].size(); i < siz_; i++)
            if (matches[u][i].first != matches[u][i - 1].first)
            {
                ptr = i;
                break;
            }
            else
                nid[matches[u][i].second] = ptot;
        addpath(pre, ptot, 0), pre = ptot;
    }
    for (int v : G[u])
        dfs(v, pre);
}

int main()
{
    T = read();
    while (T--)
    {
        memset(head, -1, sizeof(int) * (ptot + 10)), current = 0;
        memset(load, 0, sizeof(int) * (ptot + 10)), memset(bucket, 0, sizeof(int) * (ptot + 10));
        memset(rk, 0, sizeof(int) * (ptot + 10)), memset(deg, 0, sizeof(int) * (ptot + 10));
        memset(weights, 0, sizeof(int) * (ptot + 10)), memset(dist, 0, sizeof(ll) * (ptot + 10));
        for (int i = 1; i <= ptot; i++)
        {
            memset(nodes[i].ch, 0, sizeof(nodes[i].ch)), nodes[i].dep = nodes[i].link = 0;
            G[i].clear(), matches[i].clear();
            for (int j = 0; j < 20; j++)
                up[j][i] = 0;
        }
        judger.clear(), ptot = last_ptr = 1;
        scanf("%s", str + 1), na = read(), n = strlen(str + 1);
        for (int i = n; i >= 1; i--)
            insert(str[i] - 'a'), pos[i] = last_ptr;
        radixSort();
        for (int i = 1; i <= na; i++)
            li[i] = read(), ri[i] = read(), nid[i] = jump(pos[li[i]], ri[i] - li[i] + 1);
        nb = read();
        for (int i = na + 1; i <= na + nb; i++)
            li[i] = read(), ri[i] = read(), nid[i] = jump(pos[li[i]], ri[i] - li[i] + 1);
        for (int i = 1; i <= na + nb; i++)
            matches[nid[i]].push_back(make_pair(ri[i] - li[i] + 1, i));
        dfs(1, 0);
        for (int i = 1; i <= na; i++)
            weights[nid[i]] = ri[i] - li[i] + 1;
        m = read();
        while (m--)
        {
            int u = read(), v = read();
            addpath(nid[u], nid[v + na], ri[u] - li[u] + 1);
        }
        int lft = 1, rig = 0;
        ll ans = 0;
        que[++rig] = 1;
        while (lft <= rig)
        {
            int u = que[lft++];
            ans = max(ans, 0LL + dist[u] + weights[u]);
            for (int i = head[u]; i != -1; i = edges[i].nxt)
            {
                dist[edges[i].to] = max(dist[edges[i].to], 0LL + dist[u] + edges[i].weight);
                if (--deg[edges[i].to] == 0)
                    que[++rig] = edges[i].to;
            }
        }
        if (*max_element(deg + 1, deg + 1 + ptot) > 0)
            puts("-1");
        else
            printf("%lld\n", ans);
    }
    return 0;
}