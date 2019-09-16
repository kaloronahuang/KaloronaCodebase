// T98367.cpp
#include <bits/stdc++.h>
#define pr pair<int, int>
using namespace std;

const int MAX_N = 200010;

int n, head[MAX_N], current, dist[MAX_N];
bool vis[MAX_N];

struct edge
{
    int to, nxt, weight;
} edges[MAX_N * 12];

struct point
{
    int x, y, id;
} pts[MAX_N];

bool compareByX(point x, point y) { return x.x < y.x || (x.x == y.x && x.y < y.y); }
bool compareByY(point x, point y) { return x.y < y.y || (x.y == y.y && x.x < y.x); }

void addpath(int src, int dst, int weight)
{
    edges[current].to = dst, edges[current].nxt = head[src];
    edges[current].weight = weight, head[src] = current++;
}

void shortest_path()
{
    memset(dist, 0x3f, sizeof(dist));
    priority_queue<pr> pq;
    pq.push(make_pair(0, 1)), dist[1] = 0;
    while (!pq.empty())
    {
        int u = pq.top().second;
        pq.pop();
        if (vis[u])
            continue;
        vis[u] = true;
        for (int i = head[u]; i != -1; i = edges[i].nxt)
            if (dist[edges[i].to] > dist[u] + edges[i].weight)
                dist[edges[i].to] = dist[u] + edges[i].weight, pq.push(make_pair(-dist[edges[i].to], edges[i].to));
    }
}

int main()
{
    memset(head, -1, sizeof(head));
    scanf("%d", &n);
    for (int i = 1; i <= n; i++)
        scanf("%d%d", &pts[i].x, &pts[i].y), pts[i].id = i;
    sort(pts + 1, pts + 1 + n, compareByX);
    for (int i = 2; i <= n; i++)
    {
        addpath(pts[i - 1].id, pts[i].id, min(abs(pts[i].x - pts[i - 1].x), abs(pts[i].y - pts[i - 1].y)));
        addpath(pts[i].id, pts[i - 1].id, min(abs(pts[i].x - pts[i - 1].x), abs(pts[i].y - pts[i - 1].y)));
    }
    sort(pts + 1, pts + 1 + n, compareByY);
    for (int i = 2; i <= n; i++)
    {
        addpath(pts[i - 1].id, pts[i].id, min(abs(pts[i].x - pts[i - 1].x), abs(pts[i].y - pts[i - 1].y)));
        addpath(pts[i].id, pts[i - 1].id, min(abs(pts[i].x - pts[i - 1].x), abs(pts[i].y - pts[i - 1].y)));
    }
    shortest_path();
    printf("%d", dist[n]);
    return 0;
}