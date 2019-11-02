// P1986.cpp
#include <bits/stdc++.h>

using namespace std;

const int MAX_N = 30100;

struct segment
{
    int l, r, c;
    bool operator<(const segment &nd) const { return r < nd.r || (r == nd.r && l < nd.l); }
} segs[MAX_N];

int n, m;
bool vis[MAX_N];

int main()
{
    scanf("%d%d", &n, &m);
    for (int i = 1; i <= m; i++)
        scanf("%d%d%d", &segs[i].l, &segs[i].r, &segs[i].c);
    sort(segs + 1, segs + 1 + m);
    int ans = 0;
    for (int i = 1; i <= m; i++)
    {
        for (int j = segs[i].l; j <= segs[i].r; j++)
            segs[i].c -= (vis[j] == true);
        for (int j = segs[i].r; j >= segs[i].l && segs[i].c > 0; j--)
            segs[i].c -= (vis[j] == false), ans += (vis[j] == false), vis[j] = true;
    }
    printf("%d", ans);
    return 0;
}