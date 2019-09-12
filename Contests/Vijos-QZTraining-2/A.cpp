// A.cpp
#include <bits/stdc++.h>

using namespace std;

const int MAX_N = 75, MAX_P = 4910, INF = 0x3f3f3f3f;

int n, m, mem[MAX_P], head[MAX_P], current, tot, dep[MAX_P];
char opt[MAX_N][MAX_N];
bool mp[MAX_P][MAX_P], vis[MAX_P];

struct edge
{
    int to, nxt;
} edges[MAX_P << 3];

void addpath(int src, int dst)
{
    edges[current].to = dst, edges[current].nxt = head[src];
    head[src] = current++;
}

int getId(int x, int y) { return (x - 1) * m + y; }

int find(int x) { return x == mem[x] ? x : mem[x] = find(mem[x]); }

int main()
{
    memset(head, -1, sizeof(head));
    scanf("%d%d", &n, &m);
    for (int i = 1; i <= n; i++)
        scanf("%s", opt[i] + 1);
    for (int i = 1; i <= n * m; i++)
        mem[i] = i;
    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= m; j++)
        {
            if (i > 1 && opt[i][j] == opt[i - 1][j])
                mem[find(getId(i - 1, j))] = mem[find(getId(i, j))];
            if (j > 1 && opt[i][j] == opt[i][j - 1])
                mem[find(getId(i, j - 1))] = mem[find(getId(i, j))];
        }
    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= m; j++)
        {
            if (vis[find(getId(i, j))] == false)
                vis[find(getId(i, j))] = true, tot++;
            if (i > 1 && opt[i][j] != opt[i - 1][j] && !mp[find(getId(i, j))][find(getId(i - 1, j))])
                addpath(find(getId(i, j)), find(getId(i - 1, j))), addpath(find(getId(i - 1, j)), find(getId(i, j)));
            if (j > 1 && opt[i][j] != opt[i][j - 1] && !mp[find(getId(i, j))][find(getId(i, j - 1))])
                addpath(find(getId(i, j)), find(getId(i, j - 1))), addpath(find(getId(i, j - 1)), find(getId(i, j)));
        }
    int gans = INF;
    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= m; j++)
        {
            if (find(getId(i, j)) != getId(i, j))
                continue;
            memset(dep, 0x3f, sizeof(dep));
            int id = getId(i, j), ans = 0;
            queue<int> q;
            q.push(id), dep[id] = 0;
            while (!q.empty())
            {
                int u = q.front();
                q.pop();
                for (int i = head[u]; i != -1; i = edges[i].nxt)
                    if (dep[edges[i].to] == INF)
                        q.push(edges[i].to), dep[edges[i].to] = dep[u] + 1, ans = max(ans, dep[edges[i].to]);
            }
            if (((ans & 1) && opt[i][j] == 'W') || ((ans & 1) == 0 && opt[i][j] == 'B'))
                ans++;
            gans = min(gans, ans);
        }
    printf("%d", gans);
    return 0;
}