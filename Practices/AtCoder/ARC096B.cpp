// ARC096B.cpp
#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

const int MAX_N = 2e5 + 200;

int n, q[MAX_N];
ll prefix[2][MAX_N], C, ans, f[MAX_N], g[MAX_N];

int main()
{
    scanf("%d%lld", &n, &C);
    for (int i = 1; i <= n; i++)
        scanf("%lld%lld", &prefix[0][i], &prefix[1][i]);
    for (int i = 1; i <= (n << 1); i++)
        prefix[1][i] += prefix[1][i - 1];
    for (int i = 1; i <= n; i++)
        f[i] = prefix[1][i] - prefix[0][i], ans = max(ans, f[i]);
    for (int i = n; i >= 1; i--)
        g[i] = prefix[1][n] - prefix[1][i - 1] - (C - prefix[0][i]), ans = max(ans, g[i]);
    ll mx_val = 0;
    for (int i = 2; i <= n; i++)
        mx_val = max(mx_val, f[i - 1]), ans = max(ans, mx_val + g[i] - (C - prefix[0][i]));
    mx_val = 0;
    for (int i = n - 1; i >= 1; i--)
        mx_val = max(mx_val, g[i + 1]), ans = max(ans, mx_val + f[i] - prefix[0][i]);
    printf("%lld\n", ans);
    return 0;
}