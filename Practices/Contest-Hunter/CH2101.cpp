// CH2101.cpp
#include <iostream>
#include <cstdio>
#include <cstring>
#include <map>
#include <bitset>
#include <queue>
using namespace std;
const int maxn = 30020;
int head[maxn], indeg[maxn], N, M, current = 0;
map<pair<int, int>, bool> mp;
bitset<30020> seq[maxn];
struct edge
{
    int to, nxt;
} edges[maxn << 1];

void dfs(int u)
{
    seq[u].set(u, 1);
    for (int i = head[u]; i != -1; i = edges[i].nxt)
    {
        if ((seq[edges[i].to][edges[i].to]) == 0)
            dfs(edges[i].to);
        (seq[u]) |= (seq[edges[i].to]);
    }
}

int main()
{
    scanf("%d%d", &N, &M);
    memset(head, -1, sizeof(head));
    for (int i = 0; i < M; i++)
    {
        int u, v;
        scanf("%d%d", &u, &v);
        if (mp[make_pair(u, v)])
            continue;
        indeg[v]++;
        edges[current].to = v, edges[current].nxt = head[u], head[u] = current++;
        mp[make_pair(u, v)] = true;
    }
    for (int i = 1; i <= N; i++)
        if (indeg[i] == 0)
            dfs(i);
    for (int i = 1; i <= N; i++)
        printf("%d\n", seq[i].count());
    return 0;
}