// P1963.cpp
#include <bits/stdc++.h>

using namespace std;

const int MAX_N = 2e4 + 200, INF = 0x3f3f3f3f;

int head[MAX_N], n, seq[MAX_N], current, match[MAX_N], rev[MAX_N];
bool vis[MAX_N];

struct edge
{
    int to, nxt;
} edges[MAX_N << 1];

void addpath(int src, int dst)
{
    edges[current].to = dst, edges[current].nxt = head[src];
    head[src] = current++;
}

int dfs(int u)
{
    if (vis[u])
        return 0;
    vis[u] = true;
    for (int i = head[u]; i != -1; i = edges[i].nxt)
        if (!match[edges[i].to] || dfs(match[edges[i].to]))
        {
            match[edges[i].to] = u;
            return 1;
        }
    return 0;
}

int main()
{
    memset(head, -1, sizeof(head));
    scanf("%d", &n);
    for (int i = 0; i < n; i++)
    {
        scanf("%d", &seq[i]);
        int A = (i + seq[i]) % n, B = (i + n - seq[i]) % n;
        addpath(i, max(A, B)), addpath(i, min(A, B));
    }
    int ans = 0;
    for (int i = n - 1; i >= 0; i--)
    {
        memset(vis, false, sizeof(vis));
        ans += dfs(i);
    }
    if (ans == n)
    {
        for (int i = 0; i < n; i++)
            rev[match[i]] = i;
        for (int i = 0; i < n; i++)
            printf("%d ", rev[i]);
        puts("");
    }
    else
        puts("No Answer");
    return 0;
}