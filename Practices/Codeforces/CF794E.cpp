// CF794E.cpp
#include <bits/stdc++.h>

using namespace std;

const int MAX_N = 3e5 + 200;

int n, ai[MAX_N], g[MAX_N], f[MAX_N], ans[MAX_N];

int main()
{
    scanf("%d", &n);
    for (int i = 1; i <= n; i++)
        scanf("%d", &ai[i]), ans[1] = max(ans[1], ai[i]);
    for (int i = 1; i < n; i++)
        f[min(i, n - i)] = max(f[min(i, n - i)], max(ai[i], ai[i + 1]));
    for (int i = 2; i < n; i++)
        g[min(i - 1, n - i)] = max(g[min(i - 1, n - i)], max(min(ai[i - 1], ai[i]), min(ai[i], ai[i + 1])));
    for (int i = (n >> 1); i >= 1; i--)
    {
        ans[i << 1] = max(ans[(i + 1) << 1], f[i]);
        ans[i << 1 | 1] = max(ans[(i + 1) << 1 | 1], g[i]);
    }
    for (int i = n; i >= 1; i--)
        printf("%d ", ans[i]);
    return 0;
}