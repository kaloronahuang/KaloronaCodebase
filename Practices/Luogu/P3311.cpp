// P3311.cpp
#include <bits/stdc++.h>

using namespace std;

const int MAX_N = 3300, mod = 1e9 + 7;

int nodes[MAX_N][10], fail[MAX_N], ptot, m, n, dp[2][MAX_N][2];
bool tag[MAX_N];
char opt[MAX_N], upper[MAX_N];

void insert(char *str)
{
    int p = 0;
    for (int i = 1; str[i] != '\0'; i++)
    {
        if (nodes[p][str[i] - '0'] == 0)
            nodes[p][str[i] - '0'] = ++ptot;
        p = nodes[p][str[i] - '0'];
    }
    tag[p] = true;
}

void bfs()
{
    queue<int> q;
    for (int i = 0; i < 10; i++)
        if (nodes[0][i])
            q.push(nodes[0][i]), fail[nodes[0][i]] = 0;
    while (!q.empty())
    {
        int u = q.front();
        q.pop(), tag[u] |= tag[fail[u]];
        for (int i = 0; i < 10; i++)
            if (nodes[u][i])
                fail[nodes[u][i]] = nodes[fail[u]][i], q.push(nodes[u][i]);
            else
                nodes[u][i] = nodes[fail[u]][i];
    }
}

int main()
{
    scanf("%s%d", upper + 1, &m), n = strlen(upper + 1);
    for (int i = 1; i <= m; i++)
        scanf("%s", opt + 1), insert(opt);
    bfs();
    for (int i = 1; i < upper[1] - '0'; i++)
        dp[1][nodes[0][i]][0] += 1;
    dp[1][nodes[0][upper[1] - '0']][1] += 1;
    for (int i = 2; i <= n; i++)
    {
        memset(dp[i & 1], 0, sizeof(dp[i & 1]));
        for (int bit = 1; bit <= 9; bit++)
            dp[i & 1][nodes[0][bit]][0] = (dp[i & 1][nodes[0][bit]][0] + 1) % mod;
        for (int pt = 0; pt <= ptot; pt++)
        {
            if (tag[pt])
                continue;
            if (dp[!(i & 1)][pt][0])
                for (int bit = 0; bit < 10; bit++)
                {
                    if (tag[nodes[pt][bit]])
                        continue;
                    dp[i & 1][nodes[pt][bit]][0] = (1LL * dp[i & 1][nodes[pt][bit]][0] + 1LL * dp[!(i & 1)][pt][0]) % mod;
                }
            if (dp[!(i & 1)][pt][1])
                for (int bit = 0; bit < upper[i] - '0'; bit++)
                {
                    if (tag[nodes[pt][bit]])
                        continue;
                    dp[i & 1][nodes[pt][bit]][0] = (1LL * dp[i & 1][nodes[pt][bit]][0] + 1LL * dp[!(i & 1)][pt][1]) % mod;
                }
            if (tag[nodes[pt][upper[i] - '0']])
                continue;
            dp[i & 1][nodes[pt][upper[i] - '0']][1] = (1LL * dp[i & 1][nodes[pt][upper[i] - '0']][1] + 1LL * dp[!(i & 1)][pt][1]) % mod;
        }
    }
    int ans = 0;
    for (int i = 0; i <= ptot; i++)
        if (!tag[i])
        {
            ans = (1LL * ans + dp[n & 1][i][0] + dp[n & 1][i][1]) % mod;
            // printf("%d %d\n", dp[n & 1][i][0], dp[n & 1][i][1]);
        }
    printf("%d\n", ans);
    return 0;
}