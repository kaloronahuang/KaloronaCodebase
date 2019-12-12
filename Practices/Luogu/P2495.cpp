// P2495.cpp
#include <bits/stdc++.h>
#define ll long long

using namespace std;

const int MAX_N = 5e5 + 200, INF = 0x3f3f3f3f;

int head[MAX_N], current, n, q, dep[MAX_N], fa[20][MAX_N];
int kseq[MAX_N], inbound[MAX_N], outbound[MAX_N], ptot;
ll dp[MAX_N], min_val[MAX_N];
bool vis[MAX_N];

struct edge
{
    int to, nxt, weight;
} edges[MAX_N << 1];

void addpath(int src, int dst, int weight)
{
    edges[current].to = dst, edges[current].nxt = head[src];
    edges[current].weight = weight, head[src] = current++;
}

bool compare(const int &rhs1, const int &rhs2) { return (rhs1 > 0 ? inbound[rhs1] : outbound[-rhs1]) <
                                                        (rhs2 > 0 ? inbound[rhs2] : outbound[-rhs2]); }

void dfs(int u)
{
    dep[u] = dep[fa[0][u]] + 1, inbound[u] = ++ptot;
    for (int i = head[u]; i != -1; i = edges[i].nxt)
        if (edges[i].to != fa[0][u])
        {
            fa[0][edges[i].to] = u;
            min_val[edges[i].to] = min(min_val[u], 1LL * edges[i].weight);
            dfs(edges[i].to);
        }
    outbound[u] = ++ptot;
}

int getLCA(int x, int y)
{
    if (dep[x] < dep[y])
        swap(x, y);
    for (int i = 19; i >= 0; i--)
        if (dep[fa[i][x]] >= dep[y])
            x = fa[i][x];
    if (x == y)
        return x;
    for (int i = 19; i >= 0; i--)
        if (fa[i][x] != fa[i][y])
            x = fa[i][x], y = fa[i][y];
    return fa[0][x];
}

int main()
{
    memset(head, -1, sizeof(head)), scanf("%d", &n);
    for (int i = 1, u, v, w; i < n; i++)
        scanf("%d%d%d", &u, &v, &w), addpath(u, v, w), addpath(v, u, w);
    min_val[1] = INF, dfs(1);
    for (int i = 1; i < 20; i++)
        for (int j = 1; j <= n; j++)
            fa[i][j] = fa[i - 1][fa[i - 1][j]];
    scanf("%d", &q);
    while (q--)
    {
        int ktot;
        scanf("%d", &ktot);
        for (int i = 1; i <= ktot; i++)
            scanf("%d", &kseq[i]), vis[kseq[i]] = true, dp[kseq[i]] = min_val[kseq[i]];
        sort(kseq + 1, kseq + 1 + ktot, compare);
        for (int i = 2; i <= ktot; i++)
        {
            int lca = getLCA(kseq[i - 1], kseq[i]);
            if (vis[lca] == false)
                kseq[++ktot] = lca, vis[lca] = true;
        }
        // process the way out;
        for (int i = 1, siz = ktot; i <= siz; i++)
            kseq[++ktot] = -kseq[i];
        if (vis[1] == false)
            kseq[++ktot] = 1, kseq[++ktot] = -1;
        sort(kseq + 1, kseq + 1 + ktot, compare);
        stack<int> st;
        for (int idx = 1; idx <= ktot; idx++)
            if (kseq[idx] > 0)
                st.push(kseq[idx]);
            else
            {
                int p = st.top();
                st.pop();
                if (p != 1)
                    dp[st.top()] += min(dp[p], min_val[p]);
                else
                    printf("%lld\n", dp[1]);
                dp[p] = 0, vis[p] = false;
            }
    }
    return 0;
}