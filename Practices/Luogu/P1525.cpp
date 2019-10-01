// P1525.cpp
#include <bits/stdc++.h>

using namespace std;

const int MAX_N = 2e4 + 200;

int fa[MAX_N], n, m, enemy[MAX_N];

struct edge
{
    int from, to, weight;
    bool operator<(const edge &e) const { return weight > e.weight; }
} edges[210000];

int find(int x) { return x == fa[x] ? x : fa[x] = find(fa[x]); }

void unite(int x, int y)
{
    fa[find(x)] = find(y);
}

int main()
{
    scanf("%d%d", &n, &m);
    for (int i = 1; i <= n; i++)
        fa[i] = i;
    for (int i = 1; i <= m; i++)
        scanf("%d%d%d", &edges[i].from, &edges[i].to, &edges[i].weight);
    sort(edges + 1, edges + 1 + m);
    for (int i = 1; i <= m + 1; i++)
        if (fa[find(edges[i].from)] == fa[find(edges[i].to)])
            printf("%d", edges[i].weight), exit(0);
        else
        {
            if (!enemy[edges[i].from])
                enemy[edges[i].from] = edges[i].to;
            else
                unite(enemy[edges[i].from], edges[i].to);
            if (!enemy[edges[i].to])
                enemy[edges[i].to] = edges[i].from;
            else
                unite(enemy[edges[i].to], edges[i].from);
        }
    return 0;
}