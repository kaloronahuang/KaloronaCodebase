// FOJ4300.cpp
#include <bits/stdc++.h>

using namespace std;

const int MAX_N = 1e6 + 200;

typedef long long ll;

int n, bi[MAX_N];
bool vis[MAX_N];

int main()
{
    freopen("building.in", "r", stdin);
    freopen("building.out", "w", stdout);
    scanf("%d", &n);
    for (int i = 1; i < n; i++)
        scanf("%d", &bi[i]);
    ll ans = 0;
    vis[0] = true;
    int pos = 0;
    for (int i = 1; i <= n - 1; i++)
    {
        vis[bi[i]] = true;
        if (!vis[bi[i] - 1])
            if (pos == 0)
                pos = bi[i] - 1, vis[bi[i] - 1] = true;
            else
                puts("0"), exit(0);
    }
    if (pos != 0)
    {
        int i, j;
        for (i = 0; i < n; i++)
            if (bi[i] == pos - 1)
                break;
        for (j = 0; j < n; j++)
            if (bi[j] == pos + 1)
                break;
        printf("%d\n", max(0, j - i));
    }
    else
    {
        memset(vis, false, sizeof(vis));
        int cur = 0;
        for (int i = 0; i < n; i++)
        {
            if (!vis[bi[i]])
                vis[bi[i]] = true, cur++;
            ans += cur;
            if (i > 0 && vis[bi[i] - 1])
                ans--;
        }
        printf("%lld\n", ans);
    }

    return 0;
}