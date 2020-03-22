// UOJ32.cpp
#include <bits/stdc++.h>

using namespace std;

const int MAX_N = 300, MAX_M = 1e4 + 200;

typedef long long ll;
typedef pair<ll, ll> pii;

const ll INF = 9000000000000000000LL;

int n, m, head[MAX_N], current;
ll dist[MAX_N][MAX_N][MAX_N];
bool mp[MAX_N][MAX_N];
vector<pii> segs[MAX_N], bucket;

struct edge
{
    int to, nxt, weight, color;
} edges[MAX_M << 2];

void addpath(int src, int dst, int weight, int col)
{
    edges[current].to = dst, edges[current].weight = weight;
    edges[current].color = col, edges[current].nxt = head[src];
    head[src] = current++;
}

ll flat(ll a, ll b)
{
    if (b < 0)
        a = -a, b = -b;
    return a > 0 ? a / b : -((-a + b - 1) / b);
}

ll flatOver(ll a, ll b) { return -flat(-a, b); }

void bellmanFord()
{
    for (int step = 0; step <= n; step++)
        for (int u = 1; u <= n; u++)
            for (int k = 0; k <= (n << 1); k++)
                dist[step][u][k] = INF;
    dist[0][1][n] = 0;
    for (int step = 0; step < n; step++)
        for (int u = 1; u <= n; u++)
            for (int k = 0; k <= (n << 1); k++)
                if (dist[step][u][k] != INF)
                {
                    for (int i = head[u]; i != -1; i = edges[i].nxt)
                        dist[step + 1][edges[i].to][k + edges[i].color] = min(dist[step + 1][edges[i].to][k + edges[i].color], dist[step][u][k] + edges[i].weight);
                    dist[step + 1][u][k] = min(dist[step + 1][u][k], dist[step][u][k]);
                }
}

int main()
{
    memset(head, -1, sizeof(head));
    scanf("%d%d", &n, &m);
    for (int i = 1, u, v, w, c; i <= m; i++)
        scanf("%d%d%d%d", &u, &v, &w, &c), addpath(u, v, w, c), mp[u][v] = true;
    bellmanFord();
    for (int i = 1; i <= n; i++)
        mp[i][i] = true;
    for (int k = 1; k <= n; k++)
        for (int i = 1; i <= n; i++)
            for (int j = 1; j <= n; j++)
                mp[i][j] |= mp[i][k] && mp[k][j];
    for (int u = 1; u <= n; u++)
        for (int k = 0; k <= (n << 1); k++)
            if (dist[n][u][k] != INF)
            {
                ll lft = -INF, rig = INF;
                for (int j = 0; j <= (n << 1); j++)
                    if (dist[n - 1][u][j] != INF)
                    {
                        if (j > k)
                            rig = min(rig, flatOver(dist[n - 1][u][j] - dist[n][u][k], j - k));
                        else if (j < k)
                            lft = max(lft, flat(dist[n - 1][u][j] - dist[n][u][k], j - k));
                        else if (dist[n - 1][u][j] <= dist[n][u][k])
                            lft = INF, rig = -INF;
                    }
                if (lft <= rig)
                    segs[u].push_back(make_pair(lft, rig));
            }
    for (int u = 1; u <= n; u++)
    {
        ll lft = INF, rig = -INF, curt = -INF;
        bool flag = false;
        bucket.clear();
        for (int k = 1; k <= n; k++)
            if (mp[1][k] && mp[k][u])
                for (auto &x : segs[k])
                    bucket.push_back(x);
        sort(bucket.begin(), bucket.end());
        for (int i = 0, siz = bucket.size(); i < siz; i++)
        {
            if (i == 0)
            {
                if (bucket[i].first > -INF)
                {
                    lft = -INF, rig = bucket[i].first, flag = true;
                    break;
                }
            }
            else if (bucket[i].first >= curt)
            {
                lft = curt, rig = bucket[i].first, flag = true;
                break;
            }
            curt = max(curt, bucket[i].second);
        }
        if (!flag && curt < INF)
            lft = curt, rig = INF;
        if (lft == -INF || rig == INF || bucket.empty())
            puts("-1");
        else if (lft <= rig)
            printf("%lld\n", rig - lft + 1);
        else
            puts("0");
    }
    return 0;
}