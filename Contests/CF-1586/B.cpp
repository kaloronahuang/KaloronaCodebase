// B.cpp
#include <bits/stdc++.h>

using namespace std;

const int MAX_N = 1e5 + 200;

int T, n, m;
bool vis[MAX_N];

int main()
{
    scanf("%d", &T);
    while (T--)
    {
        scanf("%d%d", &n, &m);
        for (int i = 1, a, b, c; i <= m; i++)
            scanf("%d%d%d", &a, &b, &c), vis[b] = true;
        int pt = -1;
        for (int i = 1; i <= n; i++)
            if (!vis[i])
                pt = i;
        for (int i = 1; i <= n; i++)
            if (i != pt)
                printf("%d %d\n", i, pt);
        for (int i = 1; i <= n; i++)
            vis[i] = false;
    }
    return 0;
}