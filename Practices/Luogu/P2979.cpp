// P2979.cpp
#include <bits/stdc++.h>
using namespace std;
const int MAX_N = 120;
int n, t, p, vi[MAX_N], hi[MAX_N], f[2000];
int main()
{
    scanf("%d%d%d", &n, &t, &p);
    for (int i = 1; i <= n; i++)
    {
        scanf("%d%d", &vi[i], &hi[i]);
        for (int j = hi[i]; j <= (t * 5 / 4); j++)
            f[j] = max(f[j], f[j - hi[i]] + vi[i]);
    }
    int ans = f[t];
    for (int i = 1; i <= n; i++)
        if (hi[i] >= p)
            ans = max(ans, f[(t - hi[i]) * 5 / 4] + vi[i]);
    printf("%d", ans);
    return 0;
}