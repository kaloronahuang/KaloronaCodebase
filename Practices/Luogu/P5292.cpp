// P5292.cpp
#include <bits/stdc++.h>

using namespace std;

const int MAX_N = 5050, MAX_M = 1e6 + 200;

typedef pair<int, int> pii;

int n, m, q, col[MAX_N], head[MAX_N], current, ui[MAX_M], vi[MAX_M], mem[2][MAX_N];
bool tag[MAX_N], travel[MAX_N][MAX_N], already[MAX_N];
char str[MAX_N];
queue<pii> pool;

struct edge
{
    int to, nxt;
} edges[MAX_M << 1];

void addpath(int src, int dst)
{
    edges[current].to = dst, edges[current].nxt = head[src];
    head[src] = current++;
}

int find(int id, int x) { return mem[id][x] == x ? x : mem[id][x] = find(id, mem[id][x]); }

void dfs(int u, int color)
{
    col[u] = color;
    for (int i = head[u]; i != -1; i = edges[i].nxt)
        if (col[edges[i].to] == 0)
            dfs(edges[i].to, -color);
        else if (col[edges[i].to] == color)
            tag[abs(color)] = true;
}

int main()
{
    memset(head, -1, sizeof(head));
    scanf("%d%d%d%s", &n, &m, &q, str + 1);
    for (int i = 1; i <= n; i++)
        mem[0][i] = mem[1][i] = i, travel[i][i] = true, pool.push(make_pair(i, i));
    for (int i = 1; i <= m; i++)
    {
        scanf("%d%d", &ui[i], &vi[i]);
        if (str[ui[i]] == str[vi[i]])
            addpath(ui[i], vi[i]), addpath(vi[i], ui[i]);
    }
    for (int i = 1; i <= n; i++)
        if (col[i] == 0)
            dfs(i, i);
    memset(head, -1, sizeof(head)), current = 0;
    for (int i = 1; i <= m; i++)
    {
        int u = ui[i], v = vi[i];
        if (str[u] != str[v])
        {
            if (find(0, u) == find(0, v))
                continue;
            addpath(u, v), addpath(v, u);
            mem[0][find(0, u)] = find(0, v);
        }
        else
        {
            if (find(1, u) == find(1, v))
                continue;
            addpath(u, v), addpath(v, u);
            mem[1][find(1, u)] = find(1, v), pool.push(make_pair(u, v));
        }
    }
    for (int i = 1; i <= n; i++)
        if (tag[abs(col[i])] == true && already[abs(col[i])] == false)
            already[abs(col[i])] = true, addpath(i, i);
    // then we get to bfs;
    while (!pool.empty())
    {
        pii u = pool.front();
        pool.pop();
        for (int i = head[u.first]; i != -1; i = edges[i].nxt)
            for (int j = head[u.second]; j != -1; j = edges[j].nxt)
                if (str[edges[i].to] == str[edges[j].to] && travel[edges[i].to][edges[j].to] == false)
                    travel[edges[i].to][edges[j].to] = travel[edges[j].to][edges[i].to] = true, pool.push(make_pair(edges[i].to, edges[j].to));
    }
    while (q--)
    {
        int u, v;
        scanf("%d%d", &u, &v), puts(travel[u][v] ? "YES" : "NO");
    }
    return 0;
}