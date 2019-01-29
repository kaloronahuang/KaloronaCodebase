// P3381.cpp
#include <bits/stdc++.h>
using namespace std;
const int MAX_N = 5010, MAX_M = 50020;
int n, m, s, t, head[MAX_N], dist[MAX_N], flow[MAX_N], vis[MAX_N];
int tmpx, tmpy, tmpz, tmpw, current, last[MAX_N];
struct edge
{
    int to, nxt, weight, cost;
} edges[MAX_M << 1];
void addpath(int u, int v, int w, int c)
{
    edges[current].to = v, edges[current].nxt = head[u];
    edges[current].weight = w, edges[current].cost = c;
    head[u] = current++;
}
void add(int u, int v, int w, int c) { addpath(u, v, w, c), addpath(v, u, 0, -c); }
bool spfa()
{
}
int main()
{
    memset(head, -1, sizeof(head));
    scanf("%d%d%d%d", &n, &m, &s, &t);
    for (int i = 1; i <= m; i++)
        scanf("%d%d%d%d", &tmpx, &tmpy, &tmpz, &tmpw), add(tmpx, tmpy, tmpz, tmpw);

    return 0;
}