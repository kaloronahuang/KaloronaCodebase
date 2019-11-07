// P3623.cpp
#include <bits/stdc++.h>

using namespace std;

const int MAX_N = 2e4 + 200, MAX_E = 2e5 + 200;

struct edge
{
    int from, to, weight;
    bool operator<(const edge &c) const { return weight < c.weight; }
} org[MAX_E];

vector<edge> vec;

int fa[MAX_N], n, m, limit;

int find(int x) { return x == fa[x] ? x : fa[x] = find(fa[x]); }

int main()
{
    scanf("%d%d%d", &n, &m, &limit);
    for (int i = 1; i <= m; i++)
        scanf("%d%d%d", &org[i].from, &org[i].to, &org[i].weight);
    for (int i = 1; i <= n; i++)
        fa[i] = i;
    sort(org + 1, org + 1 + m), reverse(org + 1, org + 1 + m);
    int curt = 0;
    for (int i = 1; i <= m; i++)
    {
        int x = org[i].from, y = org[i].to;
        if (find(x) != find(y))
        {
            fa[find(x)] = find(y), curt += org[i].weight ^ 1;
            if (org[i].weight == 0)
                org[i].weight = -1;
        }
    }
    if (curt > limit)
        puts("no solution"), exit(0);
    for (int i = 1, cnt = 0; i <= n; i++)
    {
        if (find(i) == i)
            cnt++;
        if (cnt > 1)
            puts("no solution"), exit(0);
    }
    for (int i = 1; i <= n; i++)
        fa[i] = i;
    sort(org + 1, org + 1 + m), curt = 0;
    for (int i = 1; i <= m; i++)
    {
        int x = org[i].from, y = org[i].to;
        if (find(x) != find(y) && (org[i].weight == 1 || curt < limit))
        {
            fa[find(x)] = find(y);
            if (org[i].weight < 1)
                curt++, org[i].weight = 0;
            vec.push_back(org[i]);
        }
    }
    if (curt != limit)
        puts("no solution"), exit(0);
    for (int i = 1, cnt = 0; i <= n; i++)
    {
        if (find(i) == i)
            cnt++;
        if (cnt > 1)
            puts("no solution"), exit(0);
    }
    for (int i = 0, siz = vec.size(); i < siz; i++)
        printf("%d %d %d\n", vec[i].from, vec[i].to, vec[i].weight);
    return 0;
}