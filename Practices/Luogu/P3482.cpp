// P3482.cpp
#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

const int MAX_N = 1e6 + 200;

int n, wi[MAX_N], ai[MAX_N], bi[MAX_N], pi[MAX_N], cnt, min_val, gmin;
ll ans, acc;
bool vis[MAX_N];

void dfs(int u)
{
    cnt++, acc += wi[ai[u]], min_val = min(min_val, wi[ai[u]]), vis[u] = true;
    if (!vis[pi[bi[u]]])
        dfs(pi[bi[u]]);
}

int main()
{
    scanf("%d", &n), gmin = 0x3f3f3f3f;
    for (int i = 1; i <= n; i++)
        scanf("%d", &wi[i]), gmin = min(gmin, wi[i]);
    for (int i = 1; i <= n; i++)
        scanf("%d", &ai[i]), pi[ai[i]] = i;
    for (int i = 1; i <= n; i++)
        scanf("%d", &bi[i]);
    for (int i = 1; i <= n; i++)
        if (!vis[i])
        {
            acc = cnt = 0, min_val = 0x3f3f3f3f;
            dfs(i), ans += min(1LL * min_val * (cnt - 2) + acc, 1LL * gmin * (cnt + 1) + min_val + acc);
        }
    printf("%lld\n", ans);
    return 0;
}