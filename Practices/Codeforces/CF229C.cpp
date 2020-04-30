// CF229C.cpp
#include <bits/stdc++.h>

using namespace std;

const int MAX_N = 1e6 + 200;

typedef long long ll;

int n, m, deg[MAX_N];

int main()
{
    scanf("%d%d", &n, &m);
    for (int i = 1, u, v; i <= m; i++)
        scanf("%d%d", &u, &v), deg[u]++, deg[v]++;
    ll ans = 1LL * n * (n - 1) / 2 * (n - 2) / 3, acc = 0;
    for (int i = 1; i <= n; i++)
        acc += 1LL * deg[i] * (n - 1 - deg[i]);
    printf("%lld\n", ans - (acc >> 1));
    return 0;
}