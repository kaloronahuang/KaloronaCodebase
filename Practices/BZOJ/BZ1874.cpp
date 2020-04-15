// BZ1874.cpp
#include <bits/stdc++.h>

using namespace std;

const int MAX_N = 1100;

int n, m, ai[MAX_N], bi[MAX_N], range, sg[MAX_N];
bool vis[MAX_N];

int main()
{
    scanf("%d", &n);
    for (int i = 1; i <= n; i++)
        scanf("%d", &ai[i]), range = max(range, ai[i]);
    scanf("%d", &m);
    for (int i = 1; i <= m; i++)
        scanf("%d", &bi[i]);
    for (int i = 1; i <= range; i++)
    {
        memset(vis, false, sizeof(vis));
        for (int j = 1; bi[j] <= i && j <= m; j++)
            vis[sg[i - bi[j]]] = true;
        for (int j = 0; j <= range; j++)
            if (vis[j] == false)
            {
                sg[i] = j;
                break;
            }
    }
    int ans = 0;
    for (int i = 1; i <= n; i++)
        ans ^= sg[ai[i]];
    if (ans == 0)
        puts("NO");
    else
    {
        puts("YES");
        for (int i = 1; i <= n; i++)
            for (int j = 1; j <= m; j++)
                if (ai[i] >= bi[j] && sg[ai[i] - bi[j]] == (ans ^ sg[ai[i]]))
                    printf("%d %d\n", i, bi[j]), exit(0);
    }

    return 0;
}