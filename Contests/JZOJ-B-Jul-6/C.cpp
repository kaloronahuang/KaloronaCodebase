// C.cpp
#include <bits/stdc++.h>

using namespace std;

const int MAX_N = 1e6 + 200;

int n, m, head[MAX_N], current, fa[MAX_N], upward[MAX_N];
int dp[MAX_N][2];
bool tag[MAX_N];

struct edge
{
    int to, nxt, weight;
} edges[MAX_N << 1];

void addpath(int src, int dst, int weight)
{
    edges[current].to = dst, edges[current].weight = weight;
    edges[current].nxt = head[src], head[src] = current++;
}

void preprocess(int u)
{
    dp[u][1] = edges[upward[u]].weight;
    for (int i = head[u]; i != -1; i = edges[i].nxt)
        if (edges[i].to != fa[u])
        {
            fa[edges[i].to] = u, upward[edges[i].to] = i;
            preprocess(edges[i].to);
            if (tag[edges[i].to])
                dp[u][0] += dp[edges[i].to][1];
            else 
                dp[u][0] += min(dp[edges[i].to][0], dp[edges[i].to][1]);
        }
}

int main()
{
    memset(head, -1, sizeof(head));
    scanf("%d%d", &n, &m);
    for (int i = 1, u, v, c; i <= n - 1; i++)
        scanf("%d%d%d", &u, &v, &c), addpath(u, v, c), addpath(v, u, c);
    for (int i = 1, tmp; i <= m; i++)
        scanf("%d", &tmp), tag[tmp] = true;
    preprocess(1);
    printf("%d", dp[1][0]);
    return 0;
}