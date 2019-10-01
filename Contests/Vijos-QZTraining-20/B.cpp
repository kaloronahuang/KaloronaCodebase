// B.cpp
#include <bits/stdc++.h>

using namespace std;

const int MAX_N = 2020;

int n, seq[MAX_N], prime[MAX_N], tot, match[MAX_N];
bool vis[MAX_N], mp[MAX_N][MAX_N], flg[MAX_N];

bool dfs(int u)
{
    for (int v = 1; v <= n; v++)
        if (mp[u][v] && !flg[v])
        {
            flg[v] = true;
            if (!match[v] || dfs(match[v]))
            {
                match[v] = u;
                return true;
            }
        }
    return false;
}

int main()
{
    scanf("%d", &n);
    for (int i = 1; i <= n; i++)
        scanf("%d", &seq[i]);
    vis[1] = true;
    for (int i = 2; i < MAX_N; i++)
    {
        if (!vis[i])
            prime[++tot] = i;
        for (int j = 1; j <= tot && 1LL * i * prime[j] < MAX_N; j++)
        {
            vis[i * prime[j]] = true;
            if (i % prime[j] == 0)
                break;
        }
    }
    for (int i = 1; i <= n; i++)
        for (int j = i + 1; j <= n; j++)
            if (!vis[seq[i] + seq[j]])
                mp[i][j] = mp[j][i] = 1;
    int ans = 0;
    for (int i = 1; i <= n; i++)
    {
        memset(flg, 0, sizeof(flg));
        if ((seq[i] & 1) && dfs(i))
            ans++;
    }
    printf("%d", ans);
    return 0;
}