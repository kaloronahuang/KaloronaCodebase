// B.cpp
#include <bits/stdc++.h>

using namespace std;

const int MAX_N = 1e5 + 200;

typedef pair<int, int> pii;

int n, m, head[MAX_N], current, parity[MAX_N];
bool inst[MAX_N], vis[MAX_N];
vector<pii> ansBox;

struct edge
{
    int to, nxt;
} edges[MAX_N << 1];

void addpath(int src, int dst)
{
    edges[current].to = dst, edges[current].nxt = head[src];
    head[src] = current++;
}

bool dfs(int u, int fa)
{
    vis[u] = inst[u] = true;
    for (int i = head[u]; i != -1; i = edges[i].nxt)
        if (!vis[edges[i].to] && edges[i].to != fa)
        {
            bool res = dfs(edges[i].to, u);
            parity[u] ^= !res;
            if (res)
                ansBox.push_back(make_pair(edges[i].to, u));
            else
                ansBox.push_back(make_pair(u, edges[i].to));
        }
    inst[u] = false;
    for (int i = head[u]; i != -1; i = edges[i].nxt)
        if (inst[edges[i].to] && edges[i].to != fa)
            if (parity[u])
                parity[u] ^= 1, ansBox.push_back(make_pair(u, edges[i].to));
            else
                parity[edges[i].to] ^= 1, ansBox.push_back(make_pair(edges[i].to, u));
    return parity[u];
}

int main()
{
    memset(head, -1, sizeof(head));
    scanf("%d%d", &n, &m);
    for (int i = 1, u, v; i <= m; i++)
        scanf("%d%d", &u, &v), addpath(u, v), addpath(v, u);
    if (!dfs(1, 0))
        for (pii x : ansBox)
            printf("%d %d\n", x.first, x.second);
    else
        puts("-1");
    return 0;
}