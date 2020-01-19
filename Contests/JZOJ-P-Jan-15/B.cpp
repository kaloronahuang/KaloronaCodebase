// B.cpp
#include <bits/stdc++.h>

using namespace std;

const int MAX_N = 1e6 + 200, INF = 0x3f3f3f3f;

int head[MAX_N], current, n, m, k, dep[MAX_N], dist[MAX_N], extra_start, useless_cnt;
char mp[MAX_N];
bool useless[MAX_N];

struct edge
{
    int to, nxt;
} edges[MAX_N << 4];

void fileIO()
{
    freopen("robots.in", "r", stdin);
    freopen("robots.out", "w", stdout);
}

int id(int x, int y) { return (x - 1) * m + y; }

pair<int, int> getCord(int idx) { return make_pair(((idx - 1) / m) + 1, (idx - 1) % m + 1); }

void addpath(int src, int dst)
{
    if (useless[src] || useless[dst])
        return;
    edges[current].to = dst, edges[current].nxt = head[src];
    head[src] = current++;
}

void bfs()
{
    queue<int> q;
    q.push(extra_start), dist[extra_start] = 0;
    while (!q.empty())
    {
        int u = q.front();
        q.pop();
        for (int i = head[u]; i != -1; i = edges[i].nxt)
            if (dist[edges[i].to] == -1)
                dist[edges[i].to] = dist[u] + 1, q.push(edges[i].to);
    }
}

void output_graph()
{
    for (int u = 1; u <= extra_start; u++)
        for (int i = head[u]; i != -1; i = edges[i].nxt)
            cerr << u << " " << edges[i].to << endl;
}

int main()
{
    // fileIO();
    memset(head, -1, sizeof(head)), memset(dist, -1, sizeof(dist));
    scanf("%d%d%d", &n, &m, &k);
    for (int i = 1; i <= n; i++)
        scanf("%s", mp + (i - 1) * m + 1);
    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= m; j++)
        {
            char ch = mp[id(i, j)];
            if (ch == 'U')
                addpath(id(i - 1, j), id(i, j));
            else if (ch == 'L')
                addpath(id(i, j - 1), id(i, j));
            else if (ch == 'R')
                addpath(id(i, j + 1), id(i, j));
            else
                addpath(id(i + 1, j), id(i, j));
        }
    // extra;
    extra_start = n * m + 1;
    for (int i = 1; i <= n; i++)
        addpath(extra_start, id(i, m));
    bfs();
    // then we can get the useless point set;
    for (int i = 1; i <= n * m; i++)
        useless[i] = (dist[i] == -1), useless_cnt += (useless[i] == true);
    // then we got a tree;
    memset(head, -1, sizeof(head)), current = 0;
    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= m; j++)
        {
            char ch = mp[id(i, j)];
            if (ch == 'U')
                addpath(id(i, j), id(i - 1, j)), addpath(id(i - 1, j), id(i, j));
            else if (ch == 'L')
                addpath(id(i, j), id(i, j - 1)), addpath(id(i, j - 1), id(i, j));
            else if (ch == 'R')
                addpath(id(i, j), id(i, j + 1)), addpath(id(i, j + 1), id(i, j));
            else
                addpath(id(i, j), id(i + 1, j)), addpath(id(i + 1, j), id(i, j));
        }
    // the root;
    for (int i = 1; i <= n; i++)
        addpath(id(i, m), extra_start);

    return 0;
}