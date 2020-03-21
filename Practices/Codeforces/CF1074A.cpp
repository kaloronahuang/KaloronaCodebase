// CF1074A.cpp
#include <bits/stdc++.h>

using namespace std;

const int MAX_N = 1e5 + 200;

int n, m, ai[MAX_N], bi[MAX_N], cnt, ans;

int main()
{
    scanf("%d%d", &n, &m);
    for (int i = 1; i <= n; i++)
        scanf("%d", &ai[i]);
    sort(ai + 1, ai + 1 + n), ai[n + 1] = ans = 1e9;
    for (int i = 1, xl, xr, y; i <= m; i++)
    {
        scanf("%d%d%d", &xl, &xr, &y);
        if (xl == 1)
            bi[++cnt] = xr;
    }
    sort(bi + 1, bi + 1 + cnt);
    for (int i = 1; i <= n + 1; i++)
        ans = min(ans, int(i + cnt - (lower_bound(bi + 1, bi + 1 + cnt, ai[i]) - bi)));
    printf("%d\n", ans);
    return 0;
}