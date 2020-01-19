// C.cpp
#include <bits/stdc++.h>

using namespace std;

const int MAX_N = 2e5 + 200;

int head[MAX_N], current, n, m, mem[MAX_N], fa[MAX_N], dist[200][200], stat;

struct edge
{
    int to, nxt;
} edges[MAX_N << 1];

vector<int> G[MAX_N];

void fileIO()
{
    freopen("tree.in", "r", stdin);
    freopen("tree.out", "w", stdout);
}

void addpath(int src, int dst)
{
    edges[current].to = dst, edges[current].nxt = head[src];
    head[src] = current++;
}

int find(int x) { return x == mem[x] ? x : mem[x] = find(mem[x]); }

void dfs(int u)
{
    for (int i = head[u]; i != -1; i = edges[i].nxt)
        if (edges[i].to != fa[u])
            fa[edges[i].to] = u, dfs(edges[i].to);
}

bool bf(int u, int last, int turn)
{
    int cnt = 0;
    bool flag = false, flag2 = true;
    for (int dst = 1; dst <= n; dst++)
        if (dist[u][dst] > last && (stat & (1 << (dst - 1))))
        {
            bool res = bf(dst, dist[u][dst], turn ^ 1);
            flag |= res, flag2 &= res;
            cnt++;
        }
    if (cnt == 0)
        return turn;
    if (turn == 0)
        // counting stuff;
        return flag;
    else
        return flag2;
}

int main()
{
    fileIO();
    memset(head, -1, sizeof(head)), memset(dist, 0x3f, sizeof(dist));
    scanf("%d", &n);
    for (int i = 1, u, v; i <= n - 1; i++)
        scanf("%d%d", &u, &v), addpath(u, v), addpath(v, u), dist[u][v] = dist[v][u] = 1;
    // choose the block;
    dfs(1);
    for (int i = 1; i <= n; i++)
        dist[i][i] = 0;
    for (int k = 1; k <= n; k++)
        for (int i = 1; i <= n; i++)
            for (int j = 1; j <= n; j++)
                dist[i][j] = min(dist[i][j], dist[i][k] + dist[k][j]);
    int ans = 0;
    for (stat = 1; stat < (1 << n); stat++)
    {
        if (!(stat & 1))
            continue;
        for (int i = 1; i <= n; i++)
            mem[i] = i;
        for (int i = 2; i <= n; i++)
            if (stat & (1 << (i - 1)))
                mem[find(i)] = find(fa[i]);
        bool flag = false;
        for (int i = 2; i <= n; i++)
            if ((stat & (1 << (i - 1))) && find(i) != find(1))
            {
                flag = true;
                break;
            }
        if (flag)
            continue;
        if (bf(1, 0, 0))
            ans++;
    }
    printf("%d\n", ans);
    return 0;
}