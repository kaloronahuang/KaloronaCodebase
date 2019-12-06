// P4052.cpp
#include <bits/stdc++.h>

using namespace std;

const int MAX_N = 10010, mod = 10007;

int nodes[MAX_N][26], ptot, fail[MAX_N], n, m, dp[105][MAX_N];
bool tag[MAX_N];
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
    tag[p] |= true;
}

void build_fail()
{
    queue<int> q;
    for (int i = 0; i < 26; i++)
        if (nodes[0][i] != 0)
            q.push(nodes[0][i]), fail[nodes[0][i]] = 0;
    while (!q.empty())
    {
        int u = q.front();
        q.pop();
        for (int i = 0; i < 26; i++)
            if (nodes[u][i] == 0)
                nodes[u][i] = nodes[fail[u]][i];
            else
            {
                fail[nodes[u][i]] = nodes[fail[u]][i];
                tag[nodes[u][i]] |= tag[nodes[fail[u]][i]];
                q.push(nodes[u][i]);
            }
    }
}

int main()
{
    scanf("%d%d", &n, &m);
    for (int i = 1; i <= n; i++)
        scanf("%s", opt + 1), insert(opt);
    build_fail(), dp[0][0] = 1;
    for (int i = 1; i <= m; i++)
        for (int j = 0; j <= ptot; j++)
            for (int bit = 0; bit < 26; bit++)
                if (tag[nodes[j][bit]] == false)
                    dp[i][nodes[j][bit]] = (1LL * dp[i][nodes[j][bit]] + dp[i - 1][j]) % mod;
    int ans = 0;
    for (int i = 0; i <= ptot; i++)
        ans = (1LL * ans + dp[m][i]) % mod;
    int sum = 1;
    for (int i = 1; i <= m; i++)
        sum = 1LL * sum * 26 % mod;
    printf("%d\n", (sum - ans + mod) % mod);
    return 0;
}