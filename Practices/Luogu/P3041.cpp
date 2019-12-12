// P3041.cpp
#include <bits/stdc++.h>

using namespace std;

const int MAX_N = 1e4 + 200;

int nodes[MAX_N][3], fail[MAX_N], tag[MAX_N], n, k, ptot, dp[1010][1010];
char opt[MAX_N];

void insert(char *str)
{
    int p = 0;
    for (int i = 1; str[i] != '\0'; i++)
    {
        if (nodes[p][str[i] - 'A'] == 0)
            nodes[p][str[i] - 'A'] = ++ptot;
        p = nodes[p][str[i] - 'A'];
    }
    tag[p]++;
}

void bfs()
{
    queue<int> q;
    for (int i = 0; i < 3; i++)
        if (nodes[0][i])
            q.push(nodes[0][i]), fail[nodes[0][i]] = 0;
    while (!q.empty())
    {
        int u = q.front();
        q.pop();
        for (int i = 0; i < 3; i++)
            if (nodes[u][i])
                q.push(nodes[u][i]), fail[nodes[u][i]] = nodes[fail[u]][i];
            else
                nodes[u][i] = nodes[fail[u]][i];
        tag[u] += tag[fail[u]];
    }
}

int main()
{
    scanf("%d%d", &n, &k);
    for (int i = 1; i <= n; i++)
        scanf("%s", opt + 1), insert(opt);
    bfs();
    for (int i = 0; i <= k; i++)
        for (int j = 1; j <= ptot; j++)
            dp[i][j] = -0x3f3f3f3f;
    for (int i = 1; i <= k; i++)
        for (int pt = 0; pt <= ptot; pt++)
            for (int digit = 0; digit < 3; digit++)
                if (nodes[pt][digit])
                    dp[i][nodes[pt][digit]] = max(dp[i][nodes[pt][digit]], dp[i - 1][pt] + tag[nodes[pt][digit]]);
    int ans = 0;
    for (int pt = 0; pt <= ptot; pt++)
        ans = max(ans, dp[k][pt]);
    printf("%d\n", ans);
    return 0;
}