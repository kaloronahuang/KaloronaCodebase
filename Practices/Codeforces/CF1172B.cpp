// CF1172B.cpp
#include <bits/stdc++.h>

using namespace std;

const int MAX_N = 2e5 + 200, mod = 998244353;

int n, deg[MAX_N], ans = 1;

int main()
{
    scanf("%d", &n), ans = n;
    for (int i = 1, u, v; i <= n - 1; i++)
    {
        scanf("%d%d", &u, &v), deg[u]++, deg[v]++;
        ans = 1LL * ans * deg[u] % mod * deg[v] % mod;
    }
    printf("%d\n", ans);
    return 0;
}