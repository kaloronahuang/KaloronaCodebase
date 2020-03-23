// C.cpp
#include <bits/stdc++.h>

using namespace std;

const int MAX_N = 1e6 + 200;

int n, m, head[MAX_N], current;
vector<int> vec;
bool vis[MAX_N], aff[MAX_N];

struct edge
{
    int to, nxt;
} edges[MAX_N];

void addpath(int src, int dst)
{
    edges[current].to = dst, edges[current].nxt = head[src];
    head[src] = current++;
}

int main()
{
    memset(head, -1, sizeof(head));
    scanf("%d%d", &n, &m);
    for (int i = 1, u, v; i <= m; i++)
        scanf("%d%d", &u, &v), addpath(u, v);
    for (int u = 1; u <= n; u++)
        if (!vis[u])
        {
            vis[u] = aff[u] = true;
            for (int i = head[u]; i != -1; i = edges[i].nxt)
                vis[edges[i].to] = true;
        }
    for (int u = n; u >= 1; u--)
        if (aff[u])
            for (int i = head[u]; i != -1; i = edges[i].nxt)
                aff[edges[i].to] = false;
    for (int i = 1; i <= n; i++)
        if (aff[i])
            vec.push_back(i);
    printf("%lld\n", 1LL * vec.size());
    for (auto x : vec)
        printf("%d ", x);
    puts("");
    return 0;
}