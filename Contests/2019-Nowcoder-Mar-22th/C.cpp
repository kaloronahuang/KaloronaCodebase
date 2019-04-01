// C.cpp
#include <bits/stdc++.h>
using namespace std;
const int MAX_N = 30;
int n, m, T, k;
double f[MAX_N];
bool vis[MAX_N];
int main()
{
    scanf("%d%d%d%d", &n, &m, &T, &k);
    memset(vis, 0, sizeof(vis));
    vis[n] = 1;
    for (int t = 1; t <= T; t++)
        for (int j = 1; j <= m; j++)
            f[j] = ((T - 1) * (f[j - 1] + k * (j - 1)) * vis[j - 1] + (f[j] + j * k) * vis[j]) / T;
    double ans = 0;
    for (int i = 1; i <= m; i++)
        ans += f[i];
    printf("%lf", ans);
    return 0;
}