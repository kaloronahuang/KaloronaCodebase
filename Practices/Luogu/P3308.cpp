// P3308.cpp
#pragma GCC optimize("Ofast", "inline", "fast-math", "unroll-loops", "no-stack-protector")
#pragma GCC target("avx", "avx2", "sse4", "sse4.1", "sse4.2", "ssse3")
#include <bits/stdc++.h>

using namespace std;

const int MAX_N = 1505, INF = 0x3f3f3f3f;

int T, n, ai[MAX_N], bi[MAX_N], ci[MAX_N], current, head[MAX_N], start_pos, end_pos;
int dep[MAX_N], gS, gT, idx[MAX_N], dp[MAX_N], pos[MAX_N], cur[MAX_N];
bool vis[MAX_N];

const int SIZE = 1000000;

inline char nc()
{
    static char buf[SIZE], *p1 = buf + SIZE, *p2 = buf + SIZE;
    if (p1 == p2)
        p2 = (p1 = buf) + fread(buf, 1, SIZE, stdin);
    return p1 == p2 ? -1 : *p1++;
}

int read()
{
    int x = 0, f = 1;
    char ch = nc();
    while (!isdigit(ch))
    {
        if (ch == '-')
            f = -1;
        ch = nc();
    }
    while (isdigit(ch))
        x = (x << 3) + (x << 1) + ch - '0', ch = nc();
    return x * f;
}

struct edge
{
    int to, nxt, weight, orgw;
} edges[MAX_N * MAX_N << 1];

void addpath(int src, int dst, int weight)
{
    edges[current].to = dst, edges[current].nxt = head[src];
    edges[current].weight = weight, edges[current].orgw = weight;
    head[src] = current++;
}

void addtube(int src, int dst, int weight)
{
    addpath(src, dst, weight);
    addpath(dst, src, 0);
}

bool check(int curt)
{
    memset(vis, false, sizeof(vis));
    queue<int> q;
    q.push(curt), vis[curt] = true;
    while (!q.empty())
    {
        int u = q.front();
        q.pop();
        if (u == curt + n)
            return true;
        for (int i = head[u]; i != -1; i = edges[i].nxt)
            if (!vis[edges[i].to] && edges[i].weight > 0)
                q.push(edges[i].to), vis[edges[i].to] = true;
    }
    return false;
}

bool bfs()
{
    memset(dep, 0, sizeof(dep));
    memcpy(cur, head, sizeof(head));
    queue<int> q;
    q.push(start_pos), dep[start_pos] = 1;
    while (!q.empty())
    {
        int u = q.front();
        q.pop();
        for (int i = head[u]; i != -1; i = edges[i].nxt)
            if (edges[i].weight > 0 && dep[edges[i].to] == 0)
                dep[edges[i].to] = dep[u] + 1, q.push(edges[i].to);
    }
    return dep[end_pos] != 0;
}

int dfs(int u, int flow)
{
    if (u == end_pos || flow == 0)
        return flow;
    int acc = 0;
    for (int &i = cur[u]; i != -1; i = edges[i].nxt)
        if (edges[i].weight > 0 && dep[edges[i].to] == dep[u] + 1)
            if (int di = dfs(edges[i].to, min(flow, edges[i].weight)))
            {
                edges[i].weight -= di, edges[i ^ 1].weight += di;
                acc += di, flow -= di;
                if (flow == 0)
                    break;
            }
    return acc;
}

int main()
{
    T = read();
    while (T--)
    {
        // clear the data;
        memset(head, -1, sizeof(head)), current = 0;
        n = read(), start_pos = gS = (n << 1) | 1, end_pos = gT = gS + 1;
        for (int i = 1; i <= n; i++)
            ai[i] = read(), idx[i] = i;
        for (int i = 1; i <= n; i++)
            bi[i] = read(), pos[i] = current, addtube(i, i + n, bi[i]);
        for (int i = 1; i <= n; i++)
            ci[i] = read();
        for (int i = 1; i <= n; i++)
        {
            dp[i] = 1;
            for (int j = 1; j < i; j++)
                if (ai[i] > ai[j])
                    dp[i] = max(dp[i], dp[j] + 1);
        }
        int max_len = *max_element(dp + 1, dp + 1 + n);
        for (int i = 1; i <= n; i++)
        {
            if (dp[i] == 1)
                addtube(start_pos, i, INF);
            if (dp[i] == max_len)
                addtube(i + n, end_pos, INF);
        }
        for (int i = 1; i <= n; i++)
            for (int j = 1; j < i; j++)
                if (ai[i] > ai[j] && dp[i] == dp[j] + 1)
                    addtube(j + n, i, INF);
        int ans1 = 0;
        while (bfs())
            ans1 += dfs(start_pos, INF);
        printf("%d ", ans1), sort(idx + 1, idx + 1 + n, [](const int &rhs1, const int &rhs2) { return ci[rhs1] < ci[rhs2]; });
        vector<int> ansBox;
        for (int i = 1; i <= n; i++)
        {
            int u = idx[i];
            if (check(u))
                continue;
            ansBox.push_back(u);
            start_pos = gT, end_pos = u + n;
            while (bfs())
                dfs(start_pos, INF);
            start_pos = u, end_pos = gS;
            while (bfs())
                dfs(start_pos, INF);
            edges[pos[u]].weight = edges[pos[u] ^ 1].weight = 0;
            edges[pos[u]].orgw = edges[pos[u] ^ 1].orgw = 0;
        }
        printf("%lld\n", 1LL * ansBox.size());
        sort(ansBox.begin(), ansBox.end());
        for (int u : ansBox)
            printf("%d ", u);
        puts("");
    }
    return 0;
}