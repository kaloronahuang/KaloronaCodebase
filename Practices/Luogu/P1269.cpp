// P1269.cpp
#include <bits/stdc++.h>

using namespace std;

const int MAX_N = 20010;

int head[MAX_N], current, captive, ans, n;
bool flag = false;

struct edge
{
    int to, nxt, weight;
} edges[MAX_N << 1];

void addpath(int src, int dst, int weight)
{
    edges[current].to = dst, edges[current].nxt = head[src];
    edges[current].weight = weight, head[src] = current++;
}

int dfs(int u, int fa)
{
    int longest = 0, up_weight = 0;
    for (int i = head[u]; i != -1; i = edges[i].nxt)
        if (edges[i].to != fa)
            longest = max(longest, dfs(edges[i].to, u) + edges[i].weight), flag |= (captive <= edges[i].weight);
        else
            up_weight = edges[i].weight;
    if (longest + up_weight > captive)
        return (ans++) & 0;
    else
        return longest;
}

int main()
{
    memset(head, -1, sizeof(head));
    scanf("%d", &n);
    for (int i = 1, k, tmpx, tmpy; i <= n; i++)
    {
        scanf("%d", &k);
        while (k--)
            scanf("%d%d", &tmpx, &tmpy), addpath(i, tmpx, tmpy);
    }
    scanf("%d", &captive), dfs(1, 0);
    if (flag)
        puts("No solution.");
    else
        printf("%d", ans);
    return 0;
}