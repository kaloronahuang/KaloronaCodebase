// B.cpp
#include <bits/stdc++.h>
#define ll long long

using namespace std;

const int MAX_N = 2020;

int fa[MAX_N], n, m;
double ans = (double)(0x3f3f3f3f);

struct edge
{
    int from, to, weight;
    double cmp;
    bool operator<(const edge &d) const { return cmp < d.cmp; }
} edges[MAX_N];

int find(int x) { return x == fa[x] ? fa[x] : fa[x] = find(fa[x]); }

void kruskal(double avg)
{
    double sqr = 0;
    double len = 0;
    for (int i = 1; i <= n; i++)
        fa[i] = i;
    for (int i = 1; i <= m; i++)
        edges[i].cmp = 1.0 * (avg - 1.0 * edges[i].weight) * (avg - 1.0 * edges[i].weight);
    sort(edges + 1, edges + 1 + m);
    int cnt = 0;
    queue<int> q;
    for (int i = 1; i <= m; i++)
    {
        int x = edges[i].from, y = edges[i].to;
        if (find(x) != find(y))
            fa[fa[x]] = fa[y], cnt++, len += edges[i].weight, q.push(i);
    }
    len /= (n - 1);
    while (!q.empty())
    {
        int u = q.front();
        sqr += (edges[u].weight - len) * (edges[u].weight - len);
        q.pop();
    }
    if (cnt == n - 1)
        ans = min(ans, sqrt(sqr / (n - 1)));
}

int main()
{
    scanf("%d%d", &n, &m);
    for (int i = 1; i <= m; i++)
        scanf("%d%d%d", &edges[i].from, &edges[i].to, &edges[i].weight);
    for (double avg = 0.25; avg <= 100; avg += 0.25)
        kruskal(avg);
    printf("%.4lf", ans);
    return 0;
}