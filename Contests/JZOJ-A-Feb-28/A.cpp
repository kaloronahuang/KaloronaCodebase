// A.cpp
#include <bits/stdc++.h>
using namespace std;
const int MAX_N = 110, MAX_E = 1e5 + 200;
int head[MAX_E], current = 1, dist[MAX_E], previous[MAX_E], s, t, n, m, pi[MAX_N], psum, waiting[MAX_N][MAX_N];
int bel[MAX_E], rec[MAX_E];
bool vis[MAX_E], flag[MAX_N][10 * MAX_N];
struct edge
{
    int to, nxt, flow, cost;
} edges[MAX_E << 1];
void addpath(int src, int dst, int fl, int cst)
{
    ++current;
    edges[current].to = dst, edges[current].flow = fl, edges[current].cost = cst;
    edges[current].nxt = head[src], head[src] = current;
}
void add(int src, int dst, int fl, int cst) { addpath(src, dst, fl, cst), addpath(dst, src, 0, -cst); }
bool spfa()
{
    memset(vis, 0, sizeof(vis)), memset(dist, 0x3f, sizeof(dist));
    deque<int> q;
    dist[s] = 0, vis[s] = true;
    q.push_back(s);
    while (!q.empty())
    {
        int curt = q.front();
        q.pop_front();
        for (int i = head[curt]; i != -1; i = edges[i].nxt)
        {
            if (!edges[i].flow)
                continue;
            if (dist[edges[i].to] > dist[curt] + edges[i].cost)
            {
                dist[edges[i].to] = dist[curt] + edges[i].cost;
                previous[edges[i].to] = i;
                if (!vis[edges[i].to])
                {
                    vis[edges[i].to] = true, q.push_back(edges[i].to);
                    if (dist[q.front()] > dist[q.back()])
                    {
                        int tmp1 = q.front(), tmp2 = q.back();
                        q.pop_front(), q.pop_back();
                        q.push_front(tmp2), q.push_back(tmp1);
                    }
                }
            }
        }
        vis[curt] = false;
    }
    return dist[t] < dist[t + 1];
}
int main()
{
	//freopen("bird2.in", "r", stdin);
    memset(head, -1, sizeof(head));
    scanf("%d%d", &n, &m);
    for (int i = 1; i <= n; i++)
        scanf("%d", &pi[i]), psum += pi[i];
    s = n + m * psum + 1, t = s + 1;
    for (int i = 1; i <= n; i++)
    {
        add(s, i, pi[i], 0);
        for (int j = 1; j <= m; j++)
            scanf("%d", &waiting[i][j]);
    }
    for (int i = 1; i <= m; i++)
    {
        add(n + i, t, 1, 0);
        for (int j = 1; j <= n; j++)
            add(j, n + i, 1, waiting[j][i]), bel[current ^ 1] = i, rec[current ^ 1] = 0;
    }
    long long ans = 0;
    while (spfa())
    {
        int minv = 0x7fffffff;
        for (int i = t; i != s; i = edges[previous[i] ^ 1].to)
            minv = min(minv, edges[previous[i]].flow);
        ans += dist[t] * minv;
        for (int pt = t; pt != s; pt = edges[previous[pt] ^ 1].to)
        {
            edges[previous[pt]].flow -= minv, edges[previous[pt] ^ 1].flow += minv;
            if (bel[previous[pt]])
            {
                int j = bel[previous[pt]], k = rec[previous[pt]] + 1;
                if (k >= psum || flag[j][k])
                    continue;
                flag[j][k] = true;
                int now = n + m * k + j;
                add(now, t, 1, 0);
                for (int i = 1; i <= n; i++)
                {
                    add(i, now, 1, waiting[i][j] * (k + 1));
                    bel[current ^ 1] = j, rec[current ^ 1] = k;
                }
            }
        }
    }
    printf("%lld", ans);
    return 0;
}
