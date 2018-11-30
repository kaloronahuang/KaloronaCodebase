// POJ3764.cpp
#include <iostream>
#include <cstdio>
#include <cstring>
using namespace std;
const int maxn = 100000 * 33;
int trie[maxn][2], current = 2, head[maxn], currente, n, x, y, wt, dist[maxn];
// graph data structure;
struct edge
{
    int to, next, weight;
} edges[maxn];
void addedge(int a, int b, int w)
{
    edges[currente].to = b;
    edges[currente].weight = w;
    edges[currente].next = head[a];
    head[a] = currente++;
}
void insert(int num)
{
    int pnode = 1;
    for (int i = 30; i >= 0; i--)
    {
        int bit = (num >> i) & 1;
        if (trie[pnode][bit] == 0)
            trie[pnode][bit] = current++;
        pnode = trie[pnode][bit];
    }
}
int getBiggest(int num)
{
    int pnode = 1, ans = 0;
    for (int i = 30; i >= 0; i--)
    {
        int bit = (num >> i) & 1;
        if (trie[pnode][bit ^ 1] != 0)
            ans |= (1 << i), pnode = trie[pnode][bit ^ 1];
        else
            pnode = trie[pnode][bit];
    }
    return ans;
}
void dfs(int u, int v)
{
    for (int i = head[u]; i != -1; i = edges[i].next)
    {
        if (edges[i].to == v)
            continue;
        dist[edges[i].to] = dist[u] ^ edges[i].weight;
        insert(dist[edges[i].to]);
        dfs(edges[i].to, u);
    }
}
int main()
{
    while (scanf("%d", &n) != EOF)
    {
        fill(head, head + maxn, -1);
        memset(trie, 0, sizeof(trie));
        currente = 0, current = 2;
        for (int i = 0; i < n - 1; i++)
            scanf("%d%d%d", &x, &y, &wt), addedge(x, y, wt), addedge(y, x, wt);
        dfs(0, 0);
        int ans = 0;
        for (int i = 0; i < n; i++)
            ans = max(ans, getBiggest(dist[i]));
        printf("%d\n", ans);
    }
    return 0;
}