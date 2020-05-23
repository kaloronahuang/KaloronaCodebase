// LOJ3101.cpp
#include <bits/stdc++.h>

using namespace std;

const int MAX_N = 4e5 + 200, BLOCK = 8194;

typedef pair<int, int> pii;

int T, n, m, ptot, rear[MAX_N], tag[MAX_N], ans[MAX_N];
bool vis[MAX_N], del[MAX_N];
map<int, int> mp[MAX_N];
bitset<BLOCK + 4> F[MAX_N];
vector<int> G[MAX_N];

void addpath(int src, int dst, int t1, int t2, int d1, int d2)
{
    if (mp[src].count(t1) == 0)
        mp[src][t1] = ptot++, ptot++;
    if (mp[dst].count(t2) == 0)
        mp[dst][t2] = ptot++, ptot++;
    G[mp[src][t1] ^ d1].push_back(mp[dst][t2] ^ d2);
}

void dfs(int u)
{
    if (vis[u])
        return;
    vis[u] = true, F[u] = 0;
    if (tag[u] != -1)
        F[u][tag[u]] = 1;
    for (int v : G[u])
        dfs(v), F[u] |= F[v];
}

int main()
{
    scanf("%d%d%d", &T, &n, &m);
    for (int i = 1, opt, t, x, y; i <= m; i++)
    {
        scanf("%d%d%d%d", &opt, &t, &x, &y);
        if (opt == 0)
            addpath(x, y, t, t + 1, 0, 0), addpath(y, x, t + 1, t, 1, 1);
        else
            addpath(x, y, t, t, 1, 0), addpath(y, x, t, t, 1, 0);
    }
    for (int u = 1; u <= n; u++)
    {
        int last_time = 0;
        rear[u] = -1;
        for (auto x : mp[u])
        {
            if (last_time)
                addpath(u, u, last_time, x.first, 0, 0), addpath(u, u, x.first, last_time, 1, 1);
            last_time = x.first;
        }
        if (!mp[u].empty())
            rear[u] = mp[u][last_time];
    }
    for (int bid = 1; bid <= (n + BLOCK - 1) / BLOCK; bid++)
    {
        int lft = (bid - 1) * BLOCK + 1, rig = min(n, bid * BLOCK);
        memset(tag, -1, sizeof(tag)), memset(vis, false, sizeof(vis));
        for (int i = lft; i <= rig; i++)
            if (rear[i] != -1)
                tag[rear[i]] = i - lft + 1;
        int acc = rig - lft + 1;
        bitset<BLOCK + 4> full_set;
        full_set.set();
        for (int i = 1; i <= n; i++)
            if (rear[i] != -1)
                dfs(rear[i] ^ 1);
        for (int i = lft; i <= rig; i++)
            if (rear[i] != -1 && F[rear[i] ^ 1][i - lft + 1])
                full_set[i - lft + 1] = 0, del[i] = true, acc--;
        for (int i = 1; i <= n; i++)
            if (rear[i] != -1)
                ans[i] += acc - (full_set & F[rear[i] ^ 1]).count();
            else
                ans[i] += acc;
    }
    for (int i = 1; i <= n; i++)
        if (del[i])
            printf("0 ");
        else
            printf("%d ", ans[i] - 1);
    return 0;
}