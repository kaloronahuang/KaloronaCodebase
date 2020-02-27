// BZ3210.cpp
#include <bits/stdc++.h>

using namespace std;

const int MAX_N = 1e5 + 200;

int n, xi[MAX_N], yi[MAX_N];

int main()
{
    scanf("%d", &n);
    for (int i = 1, x, y; i <= n; i++)
        scanf("%d%d", &x, &y), xi[i] = x + y, yi[i] = y - x;
    sort(xi + 1, xi + 1 + n), sort(yi + 1, yi + 1 + n);
    long long ans = 1e18;
    for (int i = -1; i <= 1; i++)
        for (int j = -1; j <= 1; j++)
        {
            int x = xi[(1 + n) >> 1] + i, y = yi[(1 + n) >> 1] + j;
            if ((x ^ y) & 1)
                continue;
            long long pans = 0;
            for (int i = 1; i <= n; i++)
                pans += abs(xi[i] - x) + abs(yi[i] - y);
            ans = min(ans, pans);
        }
    printf("%lld\n", ans >> 1);
    return 0;
}