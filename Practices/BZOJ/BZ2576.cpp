// BZ2576.cpp
#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

const int MAX_N = 110, MAX_K = 19;

int n, m, k, id[MAX_K], tag[MAX_N], trans[1 << MAX_K][MAX_K];
bool mp[MAX_N][MAX_N], G[MAX_N][MAX_N];
ll dp[1 << MAX_K][MAX_K];

int dfs(int S, int u)
{
    if (trans[S][u] != -1)
        return trans[S][u];
    int ret = 1 << u;
    for (int i = 0; i < k; i++)
        if (G[u][i] && !(S & (1 << i)))
            ret |= dfs(S ^ (1 << i), i);
    return trans[S][u] = ret;
}

ll solve(int S, int u)
{
    if (dp[S][u] != -1)
        return dp[S][u];
    if (trans[S][u] == 1 << u)
        return S == (1 << k) - 1 || G[u][k] == false;
    ll ret = 0;
    for (int i = 0; i < k; i++)
        if (G[u][i] && !(S & (1 << i)))
            ret += 1LL * solve(S ^ (1 << i), i) * solve(S | trans[S | 1 << i][i], u);
    return dp[S][u] = ret;
}

int main()
{
    scanf("%d%d%d", &n, &m, &k);
    for (int i = 1, u, v; i <= m; i++)
        scanf("%d%d", &u, &v), mp[u][v] = mp[v][u] = true;
    k++;
    for (int i = 1; i <= n; i++)
        tag[i] = k;
    for (int i = 0; i < k - 1; i++)
        scanf("%d", &id[i]), tag[id[i]] = i, G[k - 1][i] = G[i][k - 1] = true;
    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= n; j++)
            G[tag[i]][tag[j]] |= mp[i][j];
    memset(dp, -1, sizeof(dp)), memset(trans, -1, sizeof(trans));
    for (int i = 0; i < (1 << k); i++)
        for (int j = 0; j < k; j++)
            if (i & (1 << j))
                dfs(i, j);
    printf("%lld\n", solve(1 << (k - 1), k - 1));
    return 0;
}