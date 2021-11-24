// B_new.cpp
#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

const int MAX_N = 1e5 + 200, MAX_M = 4e5 + 200, LOG = 33;

int n, m, head[MAX_N], current, col[MAX_N], siz[MAX_N];
bool flag_vad;

struct edge
{
    int to, nxt, weight;
} edges[MAX_M];

void addpath(int src, int dst, int weight)
{
    edges[current].to = dst, edges[current].weight = weight;
    edges[current].nxt = head[src], head[src] = current++;
}

void dfs(int u)
{
    for (int i = head[u]; i != -1; i = edges[i].nxt)
        if (col[edges[i].to] == -1)
        {
            col[edges[i].to] = col[u] ^ edges[i].weight;
            dfs(edges[i].to);
        }
        else
        {
            flag_vad &= ((col[edges[i].to] ^ col[u]) == edges[i].weight);
            if (!flag_vad)
                puts("-1"), exit(0);
        }
}

int main()
{
    memset(head, -1, sizeof(head)), memset(col, -1, sizeof(col));
    scanf("%d%d", &n, &m), flag_vad = true;
    for (int i = 1, u, v, w; i <= m; i++)
        scanf("%d%d%d", &u, &v, &w), addpath(u, v, w), addpath(v, u, w);
    for (int i = 1; i <= n; i++)
        if (col[i] == -1)
            col[i] = 0, dfs(i);
    return 0;
}