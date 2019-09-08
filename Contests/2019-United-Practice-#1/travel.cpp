// travel.cpp
#include <bits/stdc++.h>
#define pr pair<int, int>

using namespace std;

const int MAX_N = 550;

int head[MAX_N * MAX_N], current, n, m, opt[MAX_N * MAX_N], dist[MAX_N * MAX_N];
bool vis[MAX_N * MAX_N];

struct edge
{
    int to, nxt, weight;
} edges[2000010];

priority_queue<pr> pq;

void addpath(int src, int dst, int weight)
{
    edges[current].to = dst, edges[current].weight = weight;
    edges[current].nxt = head[src], head[src] = current++;
}

int main()
{
    freopen("travel.in", "r", stdin);
    freopen("travel.out", "w", stdout);
    memset(head, -1, sizeof(head));
    scanf("%d%d", &m, &n);
    while (getchar() != '\n')
        ;
    for (int i = 1; i <= m; i++)
    {
        bool pending = false;
        int tot = 0, tmp = 0;
        char ch;
        while (scanf("%c", &ch))
        {
            if (ch == '\n')
                break;
            else if (ch == ' ')
            {
                opt[++tot] = tmp, tmp = 0, pending = false;
                continue;
            }
            else
                tmp = tmp * 10 + int(ch - '0'), pending = true;
        }
        if (pending)
            opt[++tot] = tmp;
        for (int j = 2; j <= tot; j++)
            addpath(opt[j - 1] + (i - 1) * n, opt[j] + (i - 1) * n, 0);
    }
    for (int j = 0; j < m; j++)
        for (int k = j + 1; k < m; k++)
            addpath(1 + j * n, 1 + k * n, 0), addpath(1 + k * n, 1 + j * n, 0);
    for (int i = 2; i <= n; i++)
        for (int j = 0; j < m; j++)
            for (int k = j + 1; k < m; k++)
                addpath(i + j * n, i + k * n, 1), addpath(i + k * n, i + j * n, 1);
    while (!pq.empty())
        pq.pop();
    memset(dist, 0x3f, sizeof(dist)), dist[1] = 0;
    pq.push(make_pair(0, 1));
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
    int ans = 0x3f3f3f3f;
    for (int i = 0; i < m; i++)
        ans = min(ans, dist[i * n + n]);
    if (ans == 0x3f3f3f3f)
        puts("N0");
    else
        printf("%d", ans);
    return 0;
}