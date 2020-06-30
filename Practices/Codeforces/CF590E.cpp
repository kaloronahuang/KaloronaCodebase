// CF590E.cpp
#include <bits/stdc++.h>

using namespace std;

const int MAX_N = 1550, INF = 0x3f3f3f3f, MAX_S = 1e7 + 200;

int n, start_pos, end_pos, head[MAX_N], current, dep[MAX_N], cur[MAX_N], ptot = 1;
int ch[MAX_S][2], fail[MAX_S], tag[MAX_S], pos[MAX_N], fa[MAX_S];
bool mp[755][755];
char str[MAX_S];

struct edge
{
    int to, nxt, weight;
} edges[MAX_N * MAX_N];

void addpath(int src, int dst, int weight)
{
    edges[current].to = dst, edges[current].nxt = head[src];
    edges[current].weight = weight, head[src] = current++;
}

void addtube(int src, int dst, int weight)
{
    addpath(src, dst, weight);
    addpath(dst, src, 0);
}

bool bfs()
{
    memset(dep, 0, sizeof(dep));
    queue<int> q;
    q.push(start_pos), dep[start_pos] = 1;
    while (!q.empty())
    {
        int u = q.front();
        q.pop();
        for (int i = head[u]; i != -1; i = edges[i].nxt)
            if (edges[i].weight > 0 && dep[edges[i].to] == 0)
                dep[edges[i].to] = dep[u] + 1, q.push(edges[i].to);
    }
    return dep[end_pos] != 0;
}

int dfs(int u, int flow)
{
    if (u == end_pos || flow == 0)
        return flow;
    for (int &i = cur[u]; i != -1; i = edges[i].nxt)
        if (edges[i].weight > 0 && dep[edges[i].to] == dep[u] + 1)
            if (int di = dfs(edges[i].to, min(flow, edges[i].weight)))
            {
                edges[i].weight -= di, edges[i ^ 1].weight += di;
                return di;
            }
    return 0;
}

int dinic()
{
    int ret = 0;
    while (bfs())
    {
        memcpy(cur, head, sizeof(cur));
        while (int di = dfs(start_pos, INF))
            ret += di;
    }
    return ret;
}

void build()
{
    queue<int> q;
    for (int i = 0; i < 2; i++)
        if (ch[1][i])
            fail[ch[1][i]] = 1, q.push(ch[1][i]);
        else
            ch[1][i] = 1;
    while (!q.empty())
    {
        int u = q.front();
        q.pop();
        for (int c = 0; c < 2; c++)
            if (ch[u][c])
                fail[ch[u][c]] = ch[fail[u]][c], q.push(ch[u][c]);
            else
                ch[u][c] = ch[fail[u]][c];
    }
    // simplify the paths;
    vector<int> path;
    for (int i = 1; i <= n; i++)
        for (int org = pos[i]; org != 1; org = fa[org])
        {
            int u = fail[org];
            path.clear();
            while (!tag[u])
                path.push_back(u), u = fail[u];
            while (!path.empty())
                fail[path.back()] = u, path.pop_back();
            fail[org] = u;
            if (org != pos[i] && tag[org])
                u = org;
            if (u != 1)
                mp[i][tag[u]] = true;
        }
}

int main()
{
    memset(head, -1, sizeof(head));
    scanf("%d", &n), tag[1] = -1;
    for (int ptr = 1, len; ptr <= n; ptr++)
    {
        scanf("%s", str + 1), len = strlen(str + 1);
        int p = 1;
        for (int i = 1; i <= len; i++)
        {
            if (ch[p][str[i] - 'a'] == 0)
                fa[ch[p][str[i] - 'a'] = ++ptot] = p;
            p = ch[p][str[i] - 'a'];
        }
        tag[p] = ptr, pos[ptr] = p;
    }
    build();
    for (int k = 1; k <= n; k++)
        for (int i = 1; i <= n; i++)
            for (int j = 1; j <= n; j++)
                mp[i][j] |= mp[i][k] && mp[k][j];
    for (int i = 1; i <= n; i++)
        mp[i][i] = false;
    start_pos = 2 * n + 1, end_pos = start_pos + 1;
    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= n; j++)
            if (mp[i][j])
                addtube(i, j + n, 1);
    for (int i = 1; i <= n; i++)
        addtube(start_pos, i, 1), addtube(i + n, end_pos, 1);
    printf("%d\n", n - dinic());
    for (int i = 1; i <= n; i++)
        if (dep[i] != 0 && dep[i + n] == 0)
            printf("%d ", i);
    puts("");
    return 0;
}