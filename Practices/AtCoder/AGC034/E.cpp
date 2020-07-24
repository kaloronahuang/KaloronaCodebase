// E.cpp
#include <bits/stdc++.h>

using namespace std;

const int MAX_N = 2020;

// f[u] is the sum of depth;

int n, head[MAX_N], current, siz[MAX_N], f[MAX_N];
char S[MAX_N];

struct edge
{
    int to, nxt;
} edges[MAX_N << 1];

void addpath(int src, int dst)
{
    edges[current].to = dst, edges[current].nxt = head[src];
    head[src] = current++;
}

void dfs(int u, int fa)
{
    siz[u] = S[u] - '0', f[u] = 0;
    for (int i = head[u]; i != -1; i = edges[i].nxt)
        if (edges[i].to != fa)
            dfs(edges[i].to, u), siz[u] += siz[edges[i].to], f[u] += f[edges[i].to] + siz[edges[i].to];
}

int collect(int u, int fa)
{
    int mpos = 0;
    for (int i = head[u]; i != -1; i = edges[i].nxt)
        if (edges[i].to != fa && (mpos == 0 || f[mpos] < f[edges[i].to]))
            mpos = edges[i].to;
    if (mpos == 0)
        return 0;
    int verdict = collect(mpos, u) + siz[mpos];
    if (f[u] - f[mpos] - siz[mpos] >= verdict)
        // could be finished;
        return (f[u] & 1);
    // extra;
    return verdict - (f[u] - f[mpos] - siz[mpos]);
}

int main()
{
    memset(head, -1, sizeof(head));
    scanf("%d%s", &n, S + 1);
    for (int i = 1, u, v; i <= n - 1; i++)
        scanf("%d%d", &u, &v), addpath(u, v), addpath(v, u);
    int ans = 0x3f3f3f3f;
    for (int rt = 1; rt <= n; rt++)
    {
        dfs(rt, 0);
        if (collect(rt, 0) == 0)
            ans = min(ans, f[rt] >> 1);
    }
    if (ans == 0x3f3f3f3f)
        puts("-1");
    else
        printf("%d\n", ans);
    return 0;
}