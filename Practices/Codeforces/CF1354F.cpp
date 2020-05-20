// CF1354F.cpp
#include <bits/stdc++.h>

using namespace std;

const int MAX_N = 81;

int T, n, m, dp[MAX_N][MAX_N], trans[MAX_N][MAX_N];
bool turn[MAX_N];

struct node
{
    int ai, bi, id;
    bool operator<(const node& rhs) const { return bi < rhs.bi; }
} nodes[MAX_N];

int main()
{
    scanf("%d", &T);
    while (T--)
    {
        scanf("%d%d", &n, &m);
        for (int i = 1; i <= n; i++)
            scanf("%d%d", &nodes[i].ai, &nodes[i].bi), nodes[i].id = i;
        sort(nodes + 1, nodes + 1 + n), memset(dp, 0xcf, sizeof(dp));
        memset(trans, 0, sizeof(trans)), memset(turn, 0, sizeof(turn)), dp[0][0] = 0;
        for (int i = 1; i <= n; i++)
            for (int j = 0; j <= min(i, m); j++)
            {
                if (dp[i - 1][j] >= 0)
                    dp[i][j] = dp[i - 1][j] + nodes[i].bi * (m - 1), trans[i][j] = 0;
                if (j > 0 && dp[i - 1][j - 1] >= 0 && dp[i - 1][j - 1] + nodes[i].ai + nodes[i].bi * (j - 1) > dp[i][j])
                    dp[i][j] = dp[i - 1][j - 1] + nodes[i].ai + nodes[i].bi * (j - 1), trans[i][j] = 1;
            }
        for (int i = n, acc = m; i >= 1; i--)
            if (trans[i][acc] == 1)
                acc--, turn[nodes[i].id] = true;
        printf("%d\n", m + (n - m) * 2);
        int last_pos = -1;
        for (int i = 1, acc = 0; i <= n; i++)
            if (turn[nodes[i].id])
            {
                acc++;
                if (acc == m)
                {
                    last_pos = nodes[i].id;
                    break;
                }
                printf("%d ", nodes[i].id);
            }
        for (int i = 1; i <= n; i++)
            if (!turn[i])
                printf("%d %d ", i, -i);
        printf("%d\n", last_pos);
    }
    return 0;
}