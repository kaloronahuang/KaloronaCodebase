// CF715E.cpp
#include <bits/stdc++.h>

using namespace std;

const int MAX_N = 2500, mod = 998244353;

int ai[MAX_N], bi[MAX_N], n, binomial[MAX_N][MAX_N], arrange[MAX_N][MAX_N], stiring[MAX_N][MAX_N];
int nxt[MAX_N], deg[MAX_N], cnt[10], f[MAX_N], g[MAX_N], h[MAX_N], ans[MAX_N];
bool vis[MAX_N];

void dfs(int u, int org)
{
    vis[u] = true;
    if (nxt[u])
        if (vis[nxt[u]] == false)
            dfs(nxt[u], org);
        else
            cnt[2]++;
    else if (u > n && org > n)
        cnt[3]++;
    else if (u <= n && org > n)
        cnt[0]++;
    else if (u > n && org <= n)
        cnt[1]++;
}

void preprocess()
{
    for (int i = 1; i <= (n << 1); vis[i] = true, i++)
        ;
    binomial[0][0] = arrange[0][0] = stiring[0][0] = 1;
    for (int i = 1; i <= n; i++)
    {
        arrange[i][0] = binomial[i][0] = 1;
        for (int j = 1; j <= i; j++)
        {
            stiring[i][j] = (0LL + stiring[i - 1][j - 1] + 1LL * (i - 1) * stiring[i - 1][j] % mod) % mod;
            binomial[i][j] = (0LL + binomial[i - 1][j - 1] + binomial[i - 1][j]) % mod;
            arrange[i][j] = 1LL * arrange[i][j - 1] * (i - j + 1) % mod;
        }
    }
}

void build_graph()
{
    for (int i = 1; i <= n; i++)
    {
        if (ai[i] == 0)
            ai[i] = i + n;
        if (bi[i] == 0)
            bi[i] = i + n;
        vis[ai[i]] = vis[bi[i]] = false;
        if (ai[i] <= n || bi[i] <= n)
            nxt[ai[i]] = bi[i], deg[bi[i]]++;
    }
    for (int i = 1; i <= (n << 1); i++)
        if (vis[i] == false && deg[i] == 0)
            dfs(i, i);
    for (int i = 1; i <= (n << 1); i++)
        if (vis[i] == false)
            dfs(i, i);
}

void process(int *dp, int limit)
{
    for (int i = 0; i <= limit; i++)
        for (int j = i; j <= limit; j++)
            dp[i] = (0LL + dp[i] + 1LL * binomial[limit][j] * stiring[j][i] % mod * arrange[limit - j + cnt[3]][limit - j] % mod) % mod;
    for (int i = 0, tmp = 0; i <= limit; i++, tmp = 0)
    {
        for (int j = i, opt = 1; j <= limit; j++, opt = mod - opt)
            tmp = (0LL + tmp + 1LL * opt * dp[j] % mod * binomial[j][i] % mod) % mod;
        dp[i] = tmp;
    }
}

int main()
{
    scanf("%d", &n);
    for (int i = 1; i <= n; i++)
        scanf("%d", &ai[i]);
    for (int i = 1; i <= n; i++)
        scanf("%d", &bi[i]);
    preprocess(), build_graph();
    process(f, cnt[0]), process(g, cnt[1]);
    for (int i = 0; i <= n; i++)
        for (int j = 0; j <= i; j++)
            h[i] = (0LL + h[i] + 1LL * f[i - j] * g[j] % mod) % mod;
    for (int i = 0; i <= n; i++)
    {
        for (int j = 0; j <= i; j++)
            ans[i] = (0LL + ans[i] + 1LL * h[j] * stiring[cnt[3]][i - j] % mod) % mod;
        ans[i] = 1LL * ans[i] * arrange[cnt[3]][cnt[3]] % mod;
    }
    for (int i = 0; i < n; i++)
        printf("%d ", n - i - cnt[2] >= 0 ? ans[n - i - cnt[2]] : 0);
    putchar('\n');
    return 0;
}