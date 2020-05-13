// CF1349C.cpp
#include <bits/stdc++.h>

using namespace std;

const int MAX_N = 1010, dx[4] = {0, 0, -1, 1}, dy[4] = {1, -1, 0, 0};

typedef pair<int, int> pii;

int n, m, q, mem[MAX_N * MAX_N], siz[MAX_N * MAX_N], head[MAX_N * MAX_N], current, dist[MAX_N * MAX_N];
char str[MAX_N][MAX_N];
bool vis[MAX_N * MAX_N];

struct edge
{
    int to, nxt, weight;
} edges[(MAX_N * MAX_N) << 3];

int getId(int x, int y) { return (x - 1) * m + y; }

int find(int x) { return mem[x] == x ? x : mem[x] = find(mem[x]); }

void addpath(int src, int dst, int weight)
{
    edges[current].to = dst, edges[current].nxt = head[src];
    edges[current].weight = weight, head[src] = current++;
}

int main()
{
    memset(head, -1, sizeof(head));
    scanf("%d%d%d", &n, &m, &q);
    for (int i = 1; i <= n; i++)
        scanf("%s", str[i] + 1);
    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= m; j++)
            mem[getId(i, j)] = getId(i, j);
    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= m; j++)
        {
            if (str[i][j] == str[i - 1][j] && find(getId(i, j)) != find(getId(i - 1, j)))
                mem[find(getId(i, j))] = find(getId(i - 1, j));
            if (str[i][j] == str[i][j - 1] && find(getId(i, j)) != find(getId(i, j - 1)))
                mem[find(getId(i, j))] = find(getId(i, j - 1));
        }
    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= m; j++)
            siz[find(getId(i, j))]++;
    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= m; j++)
            if (find(getId(i, j)) == getId(i, j) && siz[find(getId(i, j))] > 1)
                addpath(0, getId(i, j), 0);
    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= m; j++)
            for (int d = 0; d < 4; d++)
                if (str[i + dx[d]][j + dy[d]] != 0 && find(getId(i, j)) != find(getId(i + dx[d], j + dy[d])))
                    addpath(find(getId(i, j)), find(getId(i + dx[d], j + dy[d])), 1);
    memset(dist, 0x3f, sizeof(dist));
    priority_queue<pii> pq;
    pq.push(make_pair(0, 0)), dist[0] = 0;
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
    int cnt = 0;
    while (q--)
    {
        cnt++;
        int x, y;
        long long t;
        scanf("%d%d%lld", &x, &y, &t);
        int threshold = dist[find(getId(x, y))];
        if (t <= threshold || threshold == 0x3f3f3f3f)
            printf("%c\n", str[x][y]);
        else
            printf("%c\n", str[x][y] ^ int((t - threshold) & 1));
    }
    return 0;
}