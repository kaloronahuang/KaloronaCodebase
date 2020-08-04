// HDU-4085.cpp
#include <bits/stdc++.h>

using namespace std;

typedef pair<int, int> pii;

const int MAX_N = 55, MAX_K = 10, MAX_E = 2020, INF = 0x3f3f3f3f;

int T, n, m, k, head[MAX_N], current, bi[MAX_N], f[MAX_N][1 << MAX_K], dp[1 << MAX_K];
queue<pii> q;
bool vis[MAX_N][1 << MAX_K];

struct edge
{
    int to, nxt, weight;
} edges[MAX_E];

void addpath(int src, int dst, int weight)
{
    edges[current].to = dst, edges[current].nxt = head[src];
    edges[current].weight = weight, head[src] = current++;
}

void spfa()
{
    while (!q.empty())
    {
        int uid = q.front().first, stat = q.front().second;
        q.pop(), vis[uid][stat] = false;
        for (int i = head[uid]; i != -1; i = edges[i].nxt)
            if (f[edges[i].to][stat] > f[uid][stat] + edges[i].weight)
            {
                f[edges[i].to][stat] = f[uid][stat] + edges[i].weight;
                if (!vis[edges[i].to][stat])
                    vis[edges[i].to][stat] = true, q.push(make_pair(edges[i].to, stat));
            }
    }
}

bool check(int stat)
{
    int acc = 0;
    for (int i = 0; i < k; i++)
        acc += ((stat >> i) & 1);
    for (int i = k; i < 2 * k; i++)
        acc -= ((stat >> i) & 1);
    return acc == 0;
}

int main()
{
    scanf("%d", &T);
    while (T--)
    {
        memset(head, -1, sizeof(head)), current = 0;
        scanf("%d%d%d", &n, &m, &k);
        for (int i = 1, u, v, w; i <= m; i++)
            scanf("%d%d%d", &u, &v, &w), addpath(u, v, w), addpath(v, u, w);
        memset(bi, 0, sizeof(bi)), memset(f, 0x3f, sizeof(f));
        for (int i = 1; i <= k; i++)
            bi[i] = 1 << (i - 1), f[i][bi[i]] = 0;
        for (int i = 1; i <= k; i++)
            bi[n - k + i] = 1 << (k + i - 1), f[n - k + i][bi[n - k + i]] = 0;
        for (int stat = 1; stat < (1 << (2 * k)); stat++)
        {
            for (int i = 1; i <= n; i++)
            {
                for (int sub = stat & (stat - 1); sub; sub = (sub - 1) & stat)
                    f[i][stat] = min(f[i][stat], f[i][stat ^ sub] + f[i][sub]);
                if (f[i][stat] != INF)
                    q.push(make_pair(i, stat)), vis[i][stat] = true;
            }
            spfa();
        }
        memset(dp, 0x3f, sizeof(dp));
        for (int stat = 0; stat < (1 << (2 * k)); stat++)
            for (int i = 1; i <= n; i++)
                dp[stat] = min(dp[stat], f[i][stat]);
        for (int stat = 0; stat < (1 << (2 * k)); stat++)
            for (int sub = (stat - 1) & stat; sub; sub = (sub - 1) & stat)
                if (check(sub))
                    dp[stat] = min(dp[stat], dp[sub] + dp[stat ^ sub]);
        if (dp[(1 << (2 * k)) - 1] != INF)
            printf("%lld\n", dp[(1 << (2 * k)) - 1]);
        else
            puts("No solution");
    }
    return 0;
}