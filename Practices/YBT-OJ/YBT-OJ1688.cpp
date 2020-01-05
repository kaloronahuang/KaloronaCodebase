// YBT-OJ1688.cpp
#include <bits/stdc++.h>

using namespace std;

const int MAX_N = 1e5 + 200;
typedef pair<int, int> pii;

int head[MAX_N], current, n, m, ui[MAX_N << 1], vi[MAX_N << 1], ci[MAX_N << 1];
int posDist[MAX_N], revDist[MAX_N], T;

int read()
{
    int x = 0, f = 1;
    char ch = getchar();
    while (!isdigit(ch))
    {
        if (ch == -1)
            f = -1;
        ch = getchar();
    }
    while (isdigit(ch))
        x = (x << 3) + (x << 1) + ch - '0', ch = getchar();
    return x * f;
}

struct edge
{
    int to, nxt;
} edges[MAX_N << 2];

vector<pii> G[MAX_N];

void addpath(int src, int dst)
{
    edges[current].to = dst, edges[current].nxt = head[src];
    head[src] = current++;
}

void bfs(int src, int *dist)
{
    queue<int> q;
    q.push(src), dist[src] = 0;
    while (!q.empty())
    {
        int u = q.front();
        q.pop();
        for (int i = head[u]; i != -1; i = edges[i].nxt)
            if (dist[edges[i].to] > dist[u] + 1)
                dist[edges[i].to] = dist[u] + 1, q.push(edges[i].to);
    }
}

int main()
{
    T = read();
    while (T--)
    {
        memset(head, -1, sizeof(head)), current = 0;
        for (int i = 1; i <= n; i++)
            G[i].clear();
        n = read(), m = read();
        for (int i = 1; i <= m; i++)
            ui[i] = read(), vi[i] = read(), ci[i] = read(), addpath(ui[i], vi[i]), addpath(vi[i], ui[i]);
        memset(posDist, 0x3f, sizeof(posDist)), bfs(1, posDist);
        memset(revDist, 0x3f, sizeof(revDist)), bfs(n, revDist);
        printf("%d\n", posDist[n]);
        for (int i = 1; i <= m; i++)
            for (int t = 0; t <= 1; t++)
            {
                if (posDist[ui[i]] + revDist[vi[i]] + 1 == posDist[n])
                    G[ui[i]].push_back(make_pair(ci[i], vi[i]));
                swap(ui[i], vi[i]);
            }
        for (int i = 1; i <= n; i++)
            sort(G[i].begin(), G[i].end());
        vector<int> ptSet, candidate;
        ptSet.push_back(1);
        for (int idx = 1; idx <= posDist[n]; idx++)
        {
            int minid = 0x3f3f3f3f;
            sort(ptSet.begin(), ptSet.end()), ptSet.erase(unique(ptSet.begin(), ptSet.end()), ptSet.end());
            for (int ptid = 0, siz = ptSet.size(); ptid < siz; ptid++)
            {
                int u = ptSet[ptid];
                for (int pos = 0, siz_ = G[u].size(); pos < siz_; pos++)
                    if (G[u][pos].first < minid)
                        candidate.clear(), minid = G[u][pos].first, candidate.push_back(G[u][pos].second);
                    else if (G[u][pos].first == minid)
                        candidate.push_back(G[u][pos].second);
                    else
                        break;
            }
            printf("%d ", minid), ptSet.clear(), swap(ptSet, candidate);
        }
        puts("");
    }
    return 0;
}