// CF59E.cpp
#include <bits/stdc++.h>
#define pr pair<int, int>

using namespace std;

const int MAX_N = 3010, MAX_M = 20202;

int head[MAX_N], current, n, m, k;
int upward[MAX_N][MAX_N], dist[MAX_N][MAX_N], tmp[MAX_N];
vector<int> vecs[MAX_N][MAX_N];

struct edge
{
    int to, nxt;
} edges[MAX_M << 1];

void addpath(int src, int dst)
{
    edges[current].to = dst, edges[current].nxt = head[src];
    head[src] = current++;
}

bool check(int a, int b, int c)
{
    for (int i = 0, siz = vecs[a][b].size(); i < siz; i++)
        if (vecs[a][b][i] == c)
            return false;
    return true;
}

void writeAns(int pre)
{
    printf("%d\n1 ", dist[pre][n]);
    int pt = n, tot = 0;
    int fat = n;
    /*
    while (pt != 1)
    {
        tmp[++tot] = pt;
        int tp = pre, pre = upward[pre][pt], pt = tp;
    }
    */
    while (fat != 1)
    {
        tmp[++tot] = fat;
        int tp = pre;
        pre = upward[pre][fat];
        fat = tp;
    }
    for (int i = tot; i >= 1; i--)
        printf("%d ", tmp[i]);
}

void bfs()
{
    queue<pr> q;
    q.push(make_pair(0, 1));
    while (!q.empty())
    {
        int pre = q.front().first, u = q.front().second;
        q.pop();
        if (u == n)
            writeAns(pre), exit(0);
        for (int i = head[u]; i != -1; i = edges[i].nxt)
            if (!dist[u][edges[i].to] && check(pre, u, edges[i].to))
                upward[u][edges[i].to] = pre, dist[u][edges[i].to] = dist[pre][u] + 1, q.push(make_pair(u, edges[i].to));
    }
}

int main()
{
    memset(head, -1, sizeof(head));
    scanf("%d%d%d", &n, &m, &k);
    for (int i = 1, u, v; i <= m; i++)
        scanf("%d%d", &u, &v), addpath(u, v), addpath(v, u);
    for (int i = 1, x, y, z; i <= k; i++)
        scanf("%d%d%d", &x, &y, &z), vecs[x][y].push_back(z);
    bfs();
    puts("-1");
    return 0;
}