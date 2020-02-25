// LOJ3089.cpp
#include <bits/stdc++.h>

using namespace std;

const int MAX_N = 2020;
const double eps = 1e-5;

int n, m, tag[MAX_N], nodes[MAX_N][10], ptot, fail[MAX_N], pre[MAX_N][MAX_N];
char T[MAX_N], tmp[MAX_N], last_c[MAX_N][MAX_N], ans[MAX_N];
double weight[MAX_N], dp[MAX_N][MAX_N];

void insert(char *str, int val)
{
    int p = 0;
    for (int i = 1; str[i] != '\0'; i++)
    {
        if (nodes[p][str[i] - '0'] == 0)
            nodes[p][str[i] - '0'] = ++ptot;
        p = nodes[p][str[i] - '0'];
    }
    tag[p]++, weight[p] = log(val);
}

void build()
{
    queue<int> q;
    for (int i = 0; i < 10; i++)
        if (nodes[0][i])
            q.push(nodes[0][i]);
    while (!q.empty())
    {
        int u = q.front();
        q.pop();
        weight[u] += weight[fail[u]], tag[u] += tag[fail[u]];
        for (int i = 0; i < 10; i++)
            if (nodes[u][i] == 0)
                nodes[u][i] = nodes[fail[u]][i];
            else
                fail[nodes[u][i]] = nodes[fail[u]][i], q.push(nodes[u][i]);
    }
}

void update(int i, int j, int k)
{
    int dst = nodes[j][k];
    if (dp[i][dst] < dp[i - 1][j] + weight[dst])
        dp[i][dst] = dp[i - 1][j] + weight[dst], pre[i][dst] = j, last_c[i][dst] = k + '0';
}

bool check(double mid)
{
    for (int i = 0; i <= ptot; i++)
        weight[i] -= mid * tag[i];
    for (int i = 0; i <= n; i++)
        for (int j = 0; j <= ptot; j++)
            dp[i][j] = -1e9;
    dp[0][0] = 0;
    for (int i = 1; i <= n; i++)
        for (int j = 0; j <= ptot; j++)
            if (T[i] == '.')
                for (int k = 0; k < 10; k++)
                    update(i, j, k);
            else
                update(i, j, T[i] - '0');
    double ans = -1e9;
    for (int i = 0; i <= ptot; i++)
        ans = max(ans, dp[n][i]);
    for (int i = 0; i <= ptot; i++)
        weight[i] += mid * tag[i];
    return ans > 0;
}

int main()
{
    scanf("%d%d%s", &n, &m, T + 1);
    for (int i = 1, val; i <= m; i++)
        scanf("%s%d", tmp + 1, &val), insert(tmp, val);
    build();
    double l = 0, r = 30, res;
    while (r - l > eps)
        if (check((l + r) / 2))
            res = l = (l + r) / 2;
        else
            r = (l + r) / 2;
    check(res);
    int last_ptr = 0;
    for (int i = 1; i <= ptot; i++)
        if (dp[n][i] > dp[n][last_ptr])
            last_ptr = i;
    for (int i = n; i >= 1; i--)
        ans[i] = last_c[i][last_ptr], last_ptr = pre[i][last_ptr];
    printf("%s\n", ans + 1);
    return 0;
}