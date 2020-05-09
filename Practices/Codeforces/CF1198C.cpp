// CF1198C.cpp
#include <bits/stdc++.h>

using namespace std;

const int MAX_N = 1e6 + 200;

int T, n, m, etot, ptot, edges[MAX_N];
bool flag[MAX_N];

int main()
{
    scanf("%d", &T);
    while (T--)
    {
        scanf("%d%d", &n, &m), etot = ptot = 0;
        memset(flag, false, sizeof(bool) * ((3 * n) + 10));
        for (int i = 1, u, v; i <= m; i++)
        {
            scanf("%d%d", &u, &v);
            if (flag[u] == false && flag[v] == false)
                edges[++etot] = i, flag[u] = flag[v] = true, ptot += 2;
        }
        if ((n * 3) - ptot >= n)
        {
            puts("IndSet");
            for (int i = 1, cnt = 0; i <= (n * 3) && cnt < n; i++)
                if (flag[i] == false)
                    printf("%d ", i), cnt++;
        }
        else if (etot >= n)
        {
            puts("Matching");
            for (int i = 1; i <= n; i++)
                printf("%d ", edges[i]);
        }
        else
            printf("Impossible");
        puts("");
    }
    return 0;
}