// P4185.cpp
#include <bits/stdc++.h>

using namespace std;

const int MAX_N = 1e5 + 200;

int fa[MAX_N], upper[MAX_N], n, q, siz[MAX_N], anses[MAX_N];

struct edge
{
    int from, to, relate;
    bool operator<(const edge &nd) const { return relate < nd.relate; }
} edges[MAX_N];

struct query
{
    int k, pt, id;
    bool operator<(const query &nd) const { return k < nd.k; }
} queries[MAX_N];

int find(int x) { return x == fa[x] ? x : fa[x] = find(fa[x]); }

int main()
{
    scanf("%d%d", &n, &q);
    for (int i = 1; i <= n; i++)
        fa[i] = i, siz[i] = 1;
    for (int i = 1; i < n; i++)
        scanf("%d%d%d", &edges[i].from, &edges[i].to, &edges[i].relate);
    sort(edges + 1, edges + n), reverse(edges + 1, edges + n);
    for (int i = 1; i <= q; i++)
        scanf("%d%d", &queries[i].k, &queries[i].pt), queries[i].id = i;
    sort(queries + 1, queries + 1 + q), reverse(queries + 1, queries + 1 + q);
    int sidecur = 1;
    for (int i = 1; i <= q; i++)
    {
        while (edges[sidecur].relate >= queries[i].k && sidecur < n)
        {
            siz[find(edges[sidecur].from)] += siz[find(edges[sidecur].to)];
            fa[find(edges[sidecur].to)] = find(edges[sidecur].from);
            sidecur++;
        }
        anses[queries[i].id] = siz[find(queries[i].pt)];
    }
    for (int i = 1; i <= q; i++)
        printf("%d\n", anses[i] - 1);
    return 0;
}