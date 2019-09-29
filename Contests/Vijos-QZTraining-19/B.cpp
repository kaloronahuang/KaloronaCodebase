// B.cpp
#include <bits/stdc++.h>

using namespace std;

const int MAX_N = 100100;

int head[MAX_N], current, n, k, T, cnt, deg[MAX_N];
bool vis[MAX_N];

struct edge
{
    int to, nxt;
} edges[MAX_N << 1];

void addpath(int src, int dst)
{
    edges[current].to = dst, edges[current].nxt = head[src];
    head[src] = current++, deg[src]++;
}

bool dfs(int u, int fat)
{
    if (k == 0)
        return false;
    // leaf;
    if (deg[u] == 1 && u != fat)
        return (vis[fat] == false && vis[u] == false);
    for (int i = head[u]; i != -1; i = edges[i].nxt)
        if (edges[i].to != fat)
        {
            bool toSave = dfs(edges[i].to, u);
            if (k == 0)
                return false;
            if (toSave && k >= 2)
            {
                cnt++, k -= 2;
                vis[u] = vis[edges[i].to] = true;
                if (k == 0)
                    break;
            }
        }
    return (vis[u] == false && vis[fat] == false);
}

int main()
{
    scanf("%d", &T);
    while (T--)
    {
        cnt = 0, memset(head, -1, sizeof(head)), current = 0;
        memset(vis, false, sizeof(vis)), memset(deg, 0, sizeof(deg));
        scanf("%d%d", &n, &k);
        for (int i = 1, tmp; i <= n - 1; i++)
            scanf("%d", &tmp), addpath(i + 1, tmp), addpath(tmp, i + 1);
        dfs(1, 1), cnt += k;
        printf("%d\n", cnt);
    }
    return 0;
}