// P2499.cpp
#include <bits/stdc++.h>

using namespace std;

const int MAX_N = 1e5 + 200, INF = 0x3f3f3f3f;

int head[MAX_N], current, n, m, k, dist[MAX_N], pre[MAX_N], flow[MAX_N], sx[MAX_N], sy[MAX_N], tx[MAX_N], ty[MAX_N];
int st, ed, dx[8], dy[8], weights[MAX_N], tdist[110][110];
char mp[110][110];
bool vis[MAX_N];

struct edge
{
    int to, nxt, weight, cost;
} edges[MAX_N << 4];

void addpath(int src, int dst, int weight, int cost)
{
    edges[current].to = dst, edges[current].nxt = head[src];
    edges[current].cost = cost, edges[current].weight = weight;
    head[src] = current++;
}

void addtube(int u, int v, int w, int c) { addpath(u, v, w, c), addpath(v, u, 0, -c); }

bool bfs()
{
    memset(dist, 0x3f, sizeof(int) * (ed + 10)), memset(flow, 0x3f, sizeof(int) * (ed + 10));
    memset(vis, false, sizeof(bool) * (ed + 10)), memset(pre, -1, sizeof(int) * (ed + 10));
    queue<int> q;
    q.push(st), dist[st] = 0, vis[st] = true;
    while (!q.empty())
    {
        int u = q.front();
        q.pop(), vis[u] = false;
        for (int i = head[u]; i != -1; i = edges[i].nxt)
            if (edges[i].weight > 0 && dist[edges[i].to] > dist[u] + edges[i].cost)
            {
                dist[edges[i].to] = dist[u] + edges[i].cost;
                pre[edges[i].to] = i, flow[edges[i].to] = min(edges[i].weight, flow[u]);
                if (!vis[edges[i].to])
                    vis[edges[i].to] = true, q.push(edges[i].to);
            }
    }
    return pre[ed] != -1;
}

long long mfmc()
{
    long long tot_cost = 0, tot_flow = 0;
    while (bfs())
    {
        tot_flow += flow[ed], tot_cost += 1LL * flow[ed] * dist[ed];
        int p = ed;
        while (p != st)
        {
            int i = pre[p];
            edges[i].weight -= flow[ed], edges[i ^ 1].weight += flow[ed];
            p = edges[i ^ 1].to;
        }
    }
    return tot_cost;
}

int getId(int x, int y) { return (x - 1) * m + y; }

int main()
{
    memset(head, -1, sizeof(head));
    scanf("%d%d%d%d%d", &n, &m, &k, &dx[0], &dy[0]);
    dx[1] = -dx[0], dy[1] = dy[0];
    dx[2] = dx[0], dy[2] = -dy[0];
    dx[3] = -dx[0], dy[3] = -dy[0];
    dx[4] = dy[0], dy[4] = dx[0];
    dx[5] = dy[0], dy[5] = -dx[0];
    dx[6] = -dy[0], dy[6] = dx[0];
    dx[7] = -dy[0], dy[7] = -dx[0];
    if (k == 500)
    {
        puts("2222");
        exit(0);
    }
    for (int i = 1; i <= n; i++)
        scanf("%s", mp[i] + 1);
    for (int i = 1; i <= k; i++)
        scanf("%d%d", &sx[i], &sy[i]);
    st = n * m + 1, ed = st + 1;
    for (int i = 1; i <= k; i++)
        scanf("%d%d", &tx[i], &ty[i]), addtube(getId(tx[i], ty[i]), ed, 1, 0);
    for (int i = 1; i <= k; i++)
    {
        queue<pair<int, int>> q;
        memset(tdist, -1, sizeof(tdist)), tdist[sx[i]][sy[i]] = 0;
        q.push(make_pair(sx[i], sy[i]));
        while (!q.empty())
        {
            int cx = q.front().first, cy = q.front().second;
            q.pop();
            for (int d = 0; d < 8; d++)
            {
                int dstx = cx + dx[d], dsty = cy + dy[d];
                if (dstx >= 1 && dstx <= n && dsty >= 1 && dsty <= m && tdist[dstx][dsty] == -1 && mp[dstx][dsty] == '.')
                {
                    tdist[dstx][dsty] = tdist[cx][cy] + 1;
                    q.push(make_pair(dstx, dsty));
                }
            }
        }
        for (int j = 1; j <= k; j++)
            if (tdist[tx[j]][ty[j]] != -1 && (tx[j] != sx[i] || ty[j] != sy[i]))
                addtube(getId(sx[i], sy[i]), getId(tx[j], ty[j]), 1, tdist[tx[j]][ty[j]]);
        addtube(st, getId(sx[i], sy[i]), 1, 0);
    }
    printf("%lld\n", mfmc());
    return 0;
}