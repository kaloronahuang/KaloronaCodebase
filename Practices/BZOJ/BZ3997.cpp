// BZ3997.cpp
#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

const int MAX_N = 1100;

int T, n, m, ai[MAX_N][MAX_N];
ll f[MAX_N][MAX_N], sufmax[MAX_N][MAX_N];

int main()
{
    scanf("%d", &T);
    while (T--)
    {
        scanf("%d%d", &n, &m);
        for (int i = 1; i <= n; i++)
            for (int j = 1; j <= m; j++)
                scanf("%d", &ai[i][j]);
        memset(f, 0, sizeof(f)), memset(sufmax, 0, sizeof(sufmax));
        for (int i = 1; i <= n; i++)
            for (int j = m; j >= 1; j--)
            {
                f[i][j] = sufmax[i - 1][j + 1] + ai[i][j];
                sufmax[i][j] = max(f[i][j], max(sufmax[i - 1][j], sufmax[i][j + 1]));
            }
        printf("%lld\n", sufmax[n][1]);
    }
    return 0;
}