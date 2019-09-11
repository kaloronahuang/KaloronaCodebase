// CF1217D.cpp
#include <bits/stdc++.h>

using namespace std;

const int MAX_N = 5050, MAX_E = 5050;

int head[MAX_N], current, n, m, stat[MAX_N], res[MAX_N];
bool cycle;

struct edge
{
    int to, id, nxt;
} edges[MAX_E];

void dfs(int u)
{
    stat[u] = 1;
    for (int i = head[u]; i != -1; i = edges[i].nxt)
        if (stat[edges[i].to] == 0)
            dfs(edges[i].to), res[edges[i].id] = 1;
        else if (stat[edges[i].to] == 2)
            res[edges[i].id] = 1;
        else
            res[edges[i].id] = 2, cycle = true;
    stat[u] = 2;
}

int main()
{
    memset(head, -1, sizeof(head));
    scanf("%d%d", &n, &m);
    for (int i = 1, src, dst; i <= m; i++)
    {
        scanf("%d%d", &src, &dst);
        edges[current].to = dst, edges[current].nxt = head[src];
        edges[current].id = i, head[src] = current++;
    }
    for (int i = 1; i <= n; i++)
        if (stat[i] == 0)
            dfs(i);
    printf("%d\n", cycle ? 2 : 1);
    for (int i = 1; i <= m; i++)
        printf("%d ", res[i]);
    return 0;
}