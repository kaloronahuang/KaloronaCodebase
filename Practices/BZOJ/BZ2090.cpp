// BZ2090.cpp
#include <bits/stdc++.h>

using namespace std;

const int MAX_N = 1e6 + 200, MAX_M = 5e6 + 200;

int n, m, ai[MAX_N], nodes[3][MAX_M], dp[MAX_N];
char str[MAX_N];

inline int lowbit(int x) { return x & (-x); }

void update(int idx, int x, int d)
{
    for (; x < MAX_M; x += lowbit(x))
        nodes[idx][x] = max(nodes[idx][x], d);
}

int query(int idx, int x, int ret = 0)
{
    for (; x; x -= lowbit(x))
        ret = max(ret, nodes[idx][x]);
    return ret;
}

int main()
{
    char tmp[2];
    scanf("%d%d", &n, &m);
    for (int i = 1; i <= n; i++)
        scanf("%d", &ai[i]);
    for (int i = 1; i <= m; i++)
        scanf("%s", tmp), str[i] = tmp[0];
    for (int i = m + 1; i <= n; i++)
        str[i] = str[(i - 1) % m + 1];
    int ans = 0;
    for (int i = 1; i <= n; i++)
    {
        dp[i] = max(nodes[2][ai[i]], max(query(0, ai[i] - 1), query(1, MAX_M - ai[i]))) + 1;
        ans = max(ans, dp[i]);
        if (str[dp[i]] == '=')
            nodes[2][ai[i]] = max(nodes[2][ai[i]], dp[i]);
        else if (str[dp[i]] == '<')
            update(0, ai[i], dp[i]);
        else
            update(1, MAX_M - ai[i] + 1, dp[i]);
    }
    printf("%d\n", ans);
    return 0;
}