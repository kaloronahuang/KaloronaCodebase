// P3101.cpp
#include <bits/stdc++.h>
#define ll long long

using namespace std;

const int MAX_P = 520, MAX_N = MAX_P * MAX_P, dx[2] = {0, 1}, dy[2] = {1, 0};

struct edge
{
    int from, to;
    ll weight;
    bool operator<(const edge &nd) const { return weight < nd.weight; }
} edges[MAX_N << 1];

int n, m, T, fa[MAX_N], siz[MAX_N], current;
int height[MAX_P][MAX_P], tot, id[MAX_P][MAX_P], vis[MAX_N];

int find(int x) { return x == fa[x] ? x : fa[x] = find(fa[x]); }

int main()
{
    scanf("%d%d%d", &n, &m, &T);
    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= m; j++)
            scanf("%d", &height[i][j]);
    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= m; j++)
            id[i][j] = ++tot, fa[tot] = tot, siz[tot] = 1;
    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= m; j++)
        {
            int dot;
            scanf("%d", &dot);
            if (dot == 1)
                vis[id[i][j]] = 1;
            for (int x = 0; x < 2; x++)
                if (i + dx[x] <= n && j + dy[x] <= m)
                    edges[++current] = edge{id[i][j], id[i + dx[x]][j + dy[x]], abs(1LL * height[i][j] - 1LL * height[i + dx[x]][j + dy[x]])};
        }
    sort(edges + 1, edges + 1 + current);
    ll ans = 0;
    for (int idx = 1; idx <= current; idx++)
    {
        int x = edges[idx].from, y = edges[idx].to;
        int fx = find(x), fy = find(y);
        if (fx == fy)
            continue;
        if (siz[fx] + siz[fy] >= T)
        {
            if (siz[fx] < T)
                ans += vis[fx] * edges[idx].weight;
            if (siz[fy] < T)
                ans += vis[fy] * edges[idx].weight;
        }
        if (siz[fx] < siz[fy])
            swap(fx, fy);
        fa[fy] = fx, siz[fx] += siz[fy];
        vis[fx] += vis[fy];
    }
    printf("%lld", ans);
    return 0;
}