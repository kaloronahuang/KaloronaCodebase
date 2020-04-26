// CF1278D.cpp
#include <bits/stdc++.h>

using namespace std;

const int MAX_N = 5e5 + 200;

int n, head[MAX_N], current, li[MAX_N], ri[MAX_N];
vector<int> subtree[MAX_N];

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
    int sum = 0, son = 0;
    for (int i = head[u]; i != -1; i = edges[i].nxt)
        if (edges[i].to != fa)
        {
            dfs(edges[i].to, u);
            sum += subtree[edges[i].to].size() << 1, son = subtree[edges[i].to].size() >= subtree[son].size() ? edges[i].to : son;
        }
    if (son == 0)
    {
        subtree[u].push_back(u), li[u] = 1, ri[u] = 2;
        return;
    }
    swap(subtree[u], subtree[son]);
    int last_r = ri[son];
    sum -= subtree[u].size() << 1, sum++, ri[son] += sum;
    for (int i = head[u]; i != -1; i = edges[i].nxt)
        if (edges[i].to != fa && edges[i].to != son)
        {
            int delta = last_r - 1;
            for (int j = 0, siz = subtree[edges[i].to].size(); j < siz; j++)
                li[subtree[edges[i].to][j]] += delta, ri[subtree[edges[i].to][j]] += delta, subtree[u].push_back(subtree[edges[i].to][j]);
            last_r = ri[edges[i].to], sum -= subtree[edges[i].to].size() << 1, ri[edges[i].to] += sum, subtree[edges[i].to].clear();
        }
    subtree[u].push_back(u), li[u] = last_r, ri[u] = ri[son] + 1;
}

int main()
{
    memset(head, -1, sizeof(head));
    scanf("%d", &n);
    for (int i = 1, u, v; i <= n - 1; i++)
        scanf("%d%d", &u, &v), addpath(u, v), addpath(v, u);
    dfs(1, 0);
    for (int i = 1; i <= n; i++)
        printf("%d %d\n", li[i], ri[i]);
    return 0;
}