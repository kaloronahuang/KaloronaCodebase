// P4103.cpp
#include <bits/stdc++.h>

using namespace std;

const int MAX_N = 2001000;

int n, current, head[MAX_N], lft[MAX_N], rig[MAX_N], ptot, q, siz[MAX_N];
int seq[MAX_N << 2], dep[MAX_N], upward[20][MAX_N];
bool vis[MAX_N];
long long dp[MAX_N], m_val[2][MAX_N];

struct edge
{
    int to, nxt;
} edges[MAX_N << 1];

bool compare(const int &rhs1, const int &rhs2) { return (rhs1 > 0 ? lft[rhs1] : rig[-rhs1]) < (rhs2 > 0 ? lft[rhs2] : rig[-rhs2]); }

void addpath(int src, int dst)
{
    edges[current].to = dst, edges[current].nxt = head[src];
    head[src] = current++;
}

void dfs(int u, int fa)
{
    lft[u] = ++ptot, dep[u] = dep[fa] + 1, upward[0][u] = fa;
    for (int i = head[u]; i != -1; i = edges[i].nxt)
        if (edges[i].to != fa)
            dfs(edges[i].to, u);
    rig[u] = ++ptot;
}

int getLCA(int x, int y)
{
    if (dep[x] < dep[y])
        swap(x, y);
    for (int i = 19; i >= 0; i--)
        if (dep[upward[i][x]] >= dep[y])
            x = upward[i][x];
    if (x == y)
        return x;
    for (int i = 19; i >= 0; i--)
        if (upward[i][x] != upward[i][y])
            x = upward[i][x], y = upward[i][y];
    return upward[0][x];
}

int main()
{
    memset(head, -1, sizeof(head));
    scanf("%d", &n);
    for (int i = 1, u, v; i <= n - 1; i++)
        scanf("%d%d", &u, &v), addpath(u, v), addpath(v, u);
    dfs(1, 0);
    for (int i = 1; i < 20; i++)
        for (int j = 1; j <= n; j++)
            upward[i][j] = upward[i - 1][upward[i - 1][j]];
    scanf("%d", &q), memset(m_val[0], 0x3f, sizeof(m_val[0]));
    while (q--)
    {
        int k, tot = 0;
        long long ans1 = 0, ans2 = 0x3f3f3f3f3f3f3f3f, ans3 = 0;
        scanf("%d", &k), tot = k;
        for (int i = 1; i <= k; i++)
            scanf("%d", &seq[i]), vis[seq[i]] = true, siz[seq[i]] = 1, m_val[0][seq[i]] = 0;
        sort(seq + 1, seq + 1 + tot, compare);
        for (int i = 2; i <= k; i++)
        {
            int lca = getLCA(seq[i - 1], seq[i]);
            if (vis[lca] == false)
                seq[++tot] = lca, vis[lca] = true;
        }
        for (int i = 1, siz = tot; i <= siz; i++)
            seq[++tot] = -seq[i];

        sort(seq + 1, seq + 1 + tot, compare);

        stack<int> st;
        for (int idx = 1; idx <= tot; idx++)
        {
            if (seq[idx] > 0)
                st.push(seq[idx]);
            else
            {
                int u = st.top();
                st.pop();
                if (!st.empty())
                {
                    int fa = st.top();
                    long long dist = dep[u] - dep[fa];
                    dp[u] += siz[u] * dist;
                    ans1 += siz[fa] * dp[u] + siz[u] * dp[fa];
                    siz[fa] += siz[u], dp[fa] += dp[u];
                    m_val[0][u] += dist, ans2 = min(ans2, m_val[0][u] + m_val[0][fa]), m_val[0][fa] = min(m_val[0][fa], m_val[0][u]);
                    m_val[1][u] += dist, ans3 = max(ans3, m_val[1][u] + m_val[1][fa]), m_val[1][fa] = max(m_val[1][fa], m_val[1][u]);
                    int a = 10;
                }
                siz[u] = 0, dp[u] = 0, m_val[0][u] = 0x3f3f3f3f3f3f3f3f, m_val[1][u] = 0, vis[u] = false;
            }
        }
        printf("%lld %lld %lld\n", ans1, ans2, ans3);
    }
    return 0;
}