// trip.cpp
#include <bits/stdc++.h>
#define pr pair<int, int>

using namespace std;

const int MAX_N = 5e4 + 200, MAX_E = 2e5 + 200;

int head[MAX_N], current, dist[MAX_N], n, m, pi, percentages[MAX_N];
int ui[MAX_E], vi[MAX_E], wi[MAX_E], aff[MAX_N], stp, edp;
bool vis[MAX_N];

struct edge
{
    int from, to, nxt;
    double weight;
} edges[MAX_E << 1];
vector<edge> indeg[MAX_N];

void addpath(int src, int dst, double weight)
{
    edges[current].from = src;
    edges[current].to = dst, edges[current].nxt = head[src];
    edges[current].weight = weight, head[src] = current++;
}

void addtube(int src, int dst, double weight)
{
    addpath(src, dst, weight), addpath(dst, src, weight);
}

void shortest_path(int src)
{
    priority_queue<pr> pq;
    pq.push(make_pair(0, src)), dist[src] = 0x3f3f3f3f;
    while (!pq.empty())
    {
        int u = pq.top().second;
        pq.pop();
        if (vis[u])
            continue;
        vis[u] = true;
        for (int i = head[u]; i != -1; i = edges[i].nxt)
            if (dist[edges[i].to] < min(dist[u], int(edges[i].weight)))
            {
                dist[edges[i].to] = min(dist[u], int(edges[i].weight)), pq.push(make_pair(dist[edges[i].to], edges[i].to));
                indeg[edges[i].to].clear(), indeg[edges[i].to].push_back(edges[i]);
            }
            else if (dist[edges[i].to] == min(dist[u], int(edges[i].weight)))
                indeg[edges[i].to].push_back(edges[i]);
    }
}

void biggest_path(int src)
{
    memset(dist, 0x3f, sizeof(dist));
    memset(vis, false, sizeof(vis));
    priority_queue<pr> pq;
    pq.push(make_pair(0, src)), dist[src] = 0;
    while (!pq.empty())
    {
        int u = pq.top().second;
        pq.pop();
        if (vis[u])
            continue;
        vis[u] = true;
        for (int i = head[u]; i != -1; i = edges[i].nxt)
            if (dist[edges[i].to] > max(dist[u], (int)ceil(edges[i].weight)))
                dist[edges[i].to] = max(dist[u], (int)ceil(edges[i].weight)), pq.push(make_pair(-dist[edges[i].to], edges[i].to));
    }
}

int main()
{
    memset(head, -1, sizeof(head));
    scanf("%d%d", &pi, &m);
    for (int i = 1; i <= m; i++)
        scanf("%d%d%d", &ui[i], &vi[i], &wi[i]);
    for (int i = 1, ti, tmp; i <= pi; i++)
    {
        scanf("%d", &ti), n += ti;
        while (ti--)
            scanf("%d", &tmp), aff[tmp] = i;
    }
    for (int i = 1; i <= pi; i++)
        scanf("%d", &percentages[i]);
    for (int i = 1; i <= m; i++)
        if (aff[ui[i]] == aff[vi[i]])
            addtube(ui[i], vi[i], double(wi[i] * percentages[aff[ui[i]]]) / 100.0);
        else
            addtube(ui[i], vi[i], double(wi[i] * (percentages[aff[ui[i]]] + percentages[aff[vi[i]]])) / 200.0);
    scanf("%d%d", &stp, &edp);
    shortest_path(stp);
    int Lans = dist[edp], Rans;
    memset(head, -1, sizeof(head)), current = 0;
    for (int i = 1; i <= n; i++)
        for (int j = 0, siz = indeg[i].size(); j < siz; j++)
            addpath(indeg[i][j].from, indeg[i][j].to, indeg[i][j].weight);
    biggest_path(stp);
    printf("%d %d", Lans, Rans = dist[edp]);
    return 0;
}