// T19705.cpp
#include <bits/stdc++.h>

using namespace std;

const int MAX_N = 101000, MAX_M = 200100, mod = 998244353;

int n, m, idx, head[MAX_N], current, deg[MAX_N], f[MAX_N][550], S[550][550];

struct edge
{
    int to, nxt;
} edges[MAX_M];

void addpath(int src, int dst)
{
    edges[current].to = dst, edges[current].nxt = head[src];
    head[src] = current++;
}

void solve()
{
    queue<int> q;
    q.push(1), f[1][0] = 1;
    while (!q.empty())
    {
        int u = q.front();
        q.pop();
        for (int i = head[u]; i != -1; i = edges[i].nxt)
        {
            f[edges[i].to][0] = (0LL + f[edges[i].to][0] + f[u][0]) % mod;
            for (int j = 1; j <= idx; j++)
                f[edges[i].to][j] = (0LL + f[edges[i].to][j] + f[u][j - 1] + f[u][j]) % mod;
            if (--deg[edges[i].to] == 0)
                q.push(edges[i].to);
        }
    }
}

int main()
{
    memset(head, -1, sizeof(head));
    scanf("%d%d%d", &n, &m, &idx);
    for (int i = 1, u, v; i <= m; i++)
        scanf("%d%d", &u, &v), addpath(u, v), deg[v]++;
    solve();
    S[0][0] = 1;
    for (int i = 1; i <= idx; i++)
        for (int j = 1; j <= idx; j++)
            S[i][j] = (0LL + 1LL * j * S[i - 1][j] % mod + S[i - 1][j - 1]) % mod;
    for (int i = 1; i <= n; i++)
    {
        int ans = 0, bas = 1;
        for (int j = 0; j <= idx; j++)
        {
            if (j > 0)
                bas = 1LL * bas * j % mod;
            ans = (0LL + ans + 1LL * bas * S[idx][j] % mod * f[i][j] % mod) % mod;
        }
        printf("%d\n", ans);
    }
    return 0;
}