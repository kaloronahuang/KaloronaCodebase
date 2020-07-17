// FOJ6733.cpp
#include <bits/stdc++.h>

using namespace std;

typedef pair<int, int> pii;

const int MAX_N = 6e5 + 200, MAX_E = 9e5 + 200;

int n, m, head[MAX_N], current, mem[MAX_N], di[MAX_N], deg[MAX_N];
char ans[MAX_E], candid[MAX_E];
bool vis[MAX_N];
vector<pii> G[MAX_N];
pii org[MAX_E];

struct edge
{
    int to, nxt, weight;
} edges[MAX_E << 1];

void fileIO(string str)
{
    freopen((str + ".in").c_str(), "r", stdin);
    freopen((str + ".out").c_str(), "w", stdout);
}

void addpath(int src, int dst, int weight)
{
    edges[current].to = dst, edges[current].nxt = head[src];
    edges[current].weight = weight, head[src] = current++;
}

int find(int x) { return mem[x] == x ? x : mem[x] = find(mem[x]); }

bool dfs(int u)
{
    vis[u] = true;
    int res = di[u];
    for (pii x : G[u])
        if (!vis[x.first] && dfs(x.first))
            res ^= 1, ans[x.second] = '1';
    return res;
}

deque<int> cstk;

void calc(int u, int fa, int lowestPos)
{
    deque<int> ustk;
    bool rFlag = false;
    if (u != 1 && ans[lowestPos] == '0')
    {
        rFlag = true;
        ustk = cstk;
        for (int x : cstk)
            ans[x] ^= 1;
        cstk.clear(), lowestPos = m + 1;
    }
    for (pii x : G[u])
    {
        int v = x.first;
    }
    if (rFlag)
    {
        cstk = ustk;
        for (int x : cstk)
            ans[x] ^= 1;
    }
}

int main()
{
    // fileIO("graph");
    memset(head, -1, sizeof(head));
    scanf("%d%d", &n, &m);
    for (int i = 1, u, v; i <= m; i++)
    {
        scanf("%d%d", &u, &v), addpath(u, v, i), addpath(v, u, i);
        org[i] = make_pair(u, v);
    }
    if (m <= 20)
    {
        int ans = 0;
        for (int stat = 0; stat < (1 << m); stat++)
        {
            for (int i = 1; i <= n; i++)
                deg[i] = 0;
            for (int i = 1; i <= m; i++)
                if (stat & (1 << (m - i)))
                    deg[org[i].first] ^= 1, deg[org[i].second] ^= 1;
            int acc = 0;
            for (int i = 1; i <= n; i++)
                acc += deg[i];
            if (acc == n - (n & 1))
                ans = max(ans, stat);
        }
        for (int i = m - 1; i >= 0; i--)
            putchar('0' + ((ans >> i) & 1));
        puts("");
        return 0;
    }
    for (int i = 1; i <= n; i++)
        mem[i] = i, di[i] = 1;
    for (int i = m; i >= 1; i--)
    {
        if (find(org[i].first) != find(org[i].second))
        {
            int u = org[i].first, v = org[i].second;
            mem[find(u)] = find(v), ans[i] = '0';
            G[u].push_back(make_pair(v, i)), G[v].push_back(make_pair(u, i));
        }
        else
            di[org[i].first] ^= 1, di[org[i].second] ^= 1, ans[i] = '1';
    }
    if (!dfs(1))
        printf("%s\n", ans + 1), exit(0);
    // odd situation;
    calc(1, 0, m + 1);
    return 0;
}