// B.cpp
#include <bits/stdc++.h>
using namespace std;
const int MAX_N = 110;
int n, m, h, ai[MAX_N], bi[MAX_N], tpv[MAX_N][MAX_N];
int main()
{
    scanf("%d%d%d", &n, &m, &h);
    for (int i = 1; i <= m; i++)
        scanf("%d", &bi[i]);
    for (int i = 1; i <= n; i++)
        scanf("%d", &ai[i]);
    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= m; j++)
            scanf("%d", &tpv[i][j]);
    for (int i = 1; i <= n; i++)
    {
        for (int j = 1; j <= m; j++)
            if (tpv[i][j] == 0)
                printf("%d ", 0);
            else
            {
                int hi = min(ai[i], bi[j]);
                printf("%d ", hi);
            }
        puts("");
    }
    return 0;
}