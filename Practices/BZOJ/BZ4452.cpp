// BZ4452.cpp
#include <bits/stdc++.h>

using namespace std;

const int MAX_N = 3e5 + 200;

typedef pair<int, int> pii;

int n, m, q, ansBox[2][MAX_N], mem[MAX_N], siz[MAX_N], siz2[MAX_N], deg[MAX_N];
pii queries[MAX_N];

struct edge
{
    int u, v, w;
    bool operator<(const edge &rhs) const { return w < rhs.w; }
} edges[MAX_N];

int find(int x) { return mem[x] == x ? x : mem[x] = find(mem[x]); }

int main()
{
    scanf("%d%d", &n, &m);
    for (int i = 1; i <= m; i++)
        scanf("%d%d%d", &edges[i].u, &edges[i].v, &edges[i].w);
    sort(edges + 1, edges + 1 + m), scanf("%d", &q);
    for (int i = 1; i <= q; i++)
        scanf("%d", &queries[i].first), queries[i].second = i;
    sort(queries + 1, queries + 1 + q);
    reverse(edges + 1, edges + 1 + m), reverse(queries + 1, queries + 1 + q);
    for (int i = 1; i <= n; i++)
        mem[i] = i, siz[i] = 1;
    int cnt0 = n, cnt2 = 0, loop = 0, qptr = 1;
    for (int eptr = 1; eptr <= m; eptr++)
    {
        while (qptr <= q && queries[qptr].first > edges[eptr].w)
        {
            ansBox[0][queries[qptr].second] = n - cnt0 - cnt2 + loop;
            ansBox[1][queries[qptr].second] = eptr - 1 - cnt2 + loop;
            qptr++;
        }
        cnt0 -= (deg[edges[eptr].u] == 0) + (deg[edges[eptr].v] == 0);
        cnt2 -= (deg[edges[eptr].u] == 2) + (deg[edges[eptr].v] == 2);

        int u = find(edges[eptr].u), v = find(edges[eptr].v);
        loop -= (siz[u] == siz2[u]) + (u != v && siz[v] == siz2[v]);
        siz2[u] -= deg[edges[eptr].u] == 2;
        siz2[v] -= deg[edges[eptr].v] == 2;
        deg[edges[eptr].u]++, deg[edges[eptr].v]++;
        cnt2 += (deg[edges[eptr].u] == 2) + (deg[edges[eptr].v] == 2);
        siz2[u] += deg[edges[eptr].u] == 2;
        siz2[v] += deg[edges[eptr].v] == 2;
        if (u != v)
            mem[u] = v, siz[v] += siz[u], siz2[v] += siz2[u];
        loop += siz[v] == siz2[v];
    }
    while (qptr <= q)
    {
        ansBox[0][queries[qptr].second] = n - cnt0 - cnt2 + loop;
        ansBox[1][queries[qptr].second] = m - cnt2 + loop;
        qptr++;
    }
    for (int i = 1; i <= q; i++)
        printf("%d %d\n", ansBox[0][i], ansBox[1][i]);
    return 0;
}