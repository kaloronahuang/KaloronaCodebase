// P6478.cpp
#include <bits/stdc++.h>

using namespace std;

const int MAX_N = 5050, mod = 998244353;

int n, head[MAX_N], current, fac[MAX_N], fac_inv[MAX_N], dp[MAX_N][MAX_N], tmp[MAX_N][2], curt[MAX_N][MAX_N][2], siz[MAX_N], cnt[MAX_N][2], g[MAX_N];
char str[MAX_N];

struct edge
{
    int to, nxt;
} edges[MAX_N << 1];

void addpath(int src, int dst)
{
    edges[current].to = dst, edges[current].nxt = head[src];
    head[src] = current++;
}

int binomial(int n_, int k_) { return 1LL * fac[n_] * fac_inv[k_] % mod * fac_inv[n_ - k_] % mod; }

void dfs(int u, int fa)
{
    curt[u][0][0] = 1;
    siz[u] = 1, cnt[u][0] = (str[u] == '0'), cnt[u][1] = (str[u] == '1');
    for (int i = head[u]; i != -1; i = edges[i].nxt)
        if (edges[i].to != fa)
        {
            dfs(edges[i].to, u);
            memset(tmp, 0, sizeof(tmp));
            for (int a = 0; a <= min(cnt[u][0], cnt[u][1]); a++)
                for (int b = 0; b <= min(cnt[edges[i].to][0], cnt[edges[i].to][1]); b++)
                {
                    tmp[a + b][0] = (0LL + tmp[a + b][0] + 1LL * curt[u][a][0] * dp[edges[i].to][b] % mod) % mod;
                    tmp[a + b][1] = (0LL + tmp[a + b][1] + 1LL * curt[u][a][1] * dp[edges[i].to][b] % mod) % mod;
                    int rem0 = cnt[edges[i].to][0] - b, rem1 = cnt[edges[i].to][1] - b;
                    if (a + b < ((siz[u] + siz[edges[i].to]) >> 1))
                        if (str[u] == '0' && rem1)
                            tmp[a + b + 1][1] = (0LL + tmp[a + b + 1][1] + 1LL * dp[edges[i].to][b] * curt[u][a][0] % mod * rem1 % mod) % mod;
                        else if (str[u] == '1' && rem0)
                            tmp[a + b + 1][1] = (0LL + tmp[a + b + 1][1] + 1LL * dp[edges[i].to][b] * curt[u][a][0] % mod * rem0 % mod) % mod;
                }
            memcpy(curt[u], tmp, sizeof(curt[u]));
            siz[u] += siz[edges[i].to];
            cnt[u][0] += cnt[edges[i].to][0], cnt[u][1] += cnt[edges[i].to][1];
        }
    for (int i = 0; i <= (siz[u] >> 1); i++)
        dp[u][i] = (0LL + curt[u][i][0] + curt[u][i][1]) % mod;
    return;
}

int main()
{
    memset(head, -1, sizeof(head));
    scanf("%d%s", &n, str + 1);
    for (int i = fac[0] = 1; i <= n; i++)
        fac[i] = 1LL * fac[i - 1] * i % mod;
    fac_inv[0] = fac_inv[1] = 1;
    for (int i = 2; i <= n; i++)
        fac_inv[i] = 1LL * (mod - mod / i) * fac_inv[mod % i] % mod;
    for (int i = 2; i <= n; i++)
        fac_inv[i] = 1LL * fac_inv[i] * fac_inv[i - 1] % mod;
    for (int i = 1, u, v; i <= n - 1; i++)
        scanf("%d%d", &u, &v), addpath(u, v), addpath(v, u);
    dfs(1, 0);
    for (int i = 0; i <= (n >> 1); i++)
        g[i] = (0LL + 1LL * dp[1][i] * fac[(n >> 1) - i] % mod) % mod;
    for (int i = 0; i <= (n >> 1); i++)
    {
        int ans = 0;
        for (int j = i, opt = 1; j <= (n >> 1); j++, opt = mod - opt)
            ans = (0LL + ans + 1LL * opt * binomial(j, i) % mod * g[j] % mod) % mod;
        printf("%d\n", ans);
    }
    return 0;
}