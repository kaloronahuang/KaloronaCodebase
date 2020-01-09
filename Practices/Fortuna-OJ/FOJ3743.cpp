// FOJ3743.cpp
#include <bits/stdc++.h>

using namespace std;

const int MAX_N = 1e5 + 200;

void fileIO() { freopen("alice.in", "r", stdin), freopen("alice.out", "w", stdout); }

int head[MAX_N], current, last[MAX_N], ai[MAX_N], n, nodes[MAX_N], dfn[MAX_N], ptot;

struct edge
{
    int to, nxt;
} edges[MAX_N << 1];

void addpath(int src, int dst)
{
    edges[current].to = dst, edges[current].nxt = head[src];
    head[src] = current++;
}

inline int lowbit(int x) { return x & (-x); }

void update(int x, int d)
{
    for (; x <= n; x += lowbit(x))
        nodes[x] = max(nodes[x], d);
}

int query(int x, int ret = 0)
{
    for (; x; x -= lowbit(x))
        ret = max(ret, nodes[x]);
    return ret;
}

void dfs(int u)
{
    dfn[u] = ++ptot;
    for (int i = head[u]; i != -1; i = edges[i].nxt)
        dfs(edges[i].to);
}

int main()
{
    fileIO();
    memset(head, -1, sizeof(head));
    scanf("%d", &n), last[0] = n + 1;
    for (int i = 1; i <= n; i++)
    {
        scanf("%d", &ai[i]);
        addpath(last[ai[i] - 1], i), last[ai[i]] = i;
    }
    dfs(n + 1);
    // now we got {x_i} = {dfn_i};
    long long ans = 0;
    for (int i = n, len; i >= 1; i--)
        len = query(dfn[i] - 1) + 1, ans += 1LL * len, update(dfn[i], len);
    printf("%lld\n", ans);
    return 0;
}