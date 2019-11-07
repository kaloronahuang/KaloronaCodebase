// BZ1196.cpp
#include <bits/stdc++.h>

using namespace std;

const int MAX_N = 1e4 + 200;

int n, m, k, fa[MAX_N];

struct edge
{
    int from, to, c1, c2;
} orgs[MAX_N * 20];

int find(int x) { return x == fa[x] ? x : fa[x] = find(fa[x]); }

bool check(int mid)
{
    for (int i = 1; i <= n; i++)
        fa[i] = i;
    int cnt = 0;
    // first-class road;
    for (int i = 1; i <= m; i++)
    {
        if (orgs[i].c1 > mid)
            continue;
        if (find(orgs[i].from) != find(orgs[i].to))
            fa[find(orgs[i].from)] = find(orgs[i].to), cnt++;
    }
    if (cnt < k)
        return false;
    for (int i = 1; i <= m; i++)
    {
        if (orgs[i].c2 > mid)
            continue;
        if (find(orgs[i].from) != find(orgs[i].to))
            fa[find(orgs[i].from)] = find(orgs[i].to), cnt++;
    }
    return cnt == n - 1;
}

int main()
{
    scanf("%d%d%d", &n, &k, &m), m--;
    for (int i = 1; i <= m; i++)
        scanf("%d%d%d%d", &orgs[i].from, &orgs[i].to, &orgs[i].c1, &orgs[i].c2);
    int l = 1, r = 3e4, ans;
    while (l <= r)
    {
        int mid = (l + r) >> 1;
        if (check(mid))
            r = mid - 1, ans = mid;
        else
            l = mid + 1;
    }
    printf("%d", ans);
    return 0;
}