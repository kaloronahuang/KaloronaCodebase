// BZ2430.cpp
#include <bits/stdc++.h>

using namespace std;

const int MAX_N = 1e5 + 200;

int n, m, xi[MAX_N], yi[MAX_N];
long long ans;

int main()
{
    scanf("%d%d", &n, &m);
    for (int i = 1; i < n; i++)
        scanf("%d", &xi[i]);
    for (int i = 1; i < m; i++)
        scanf("%d", &yi[i]);
    sort(xi + 1, xi + n + 1), sort(yi + 1, yi + m + 1);
    reverse(xi + 1, xi + n + 1), reverse(yi + 1, yi + m + 1);
    int xptr = 1, yptr = 1;
    for (int i = 1; i <= n + m - 2; i++)
        if ((yptr > m && xptr <= n) || (xi[xptr] > yi[yptr]))
            ans += 1LL * yptr * xi[xptr++];
        else
            ans += 1LL * xptr * yi[yptr++];
    printf("%lld\n", ans);
    return 0;
}