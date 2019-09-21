// P3452.cpp
#include <bits/stdc++.h>

using namespace std;

const int MAX_N = 1e5 + 200, MAX_E = 4e6 + 200;

int head[MAX_N], current, n, m;

struct edge
{
    int to, nxt;
} edges[MAX_E];

bool vis[MAX_N], ext[MAX_N];

vector<int> pool;

void addpath(int src, int dst)
{
    edges[current].to = dst, edges[current].nxt = head[src];
    head[src] = current++;
}

int bfs(int x)
{
    int tot = 0;
    queue<int> q;
    q.push(x), ext[x] = true;
    while (!q.empty())
    {
        int u = q.front();
        q.pop(), tot++;
        vis[u] = true;
        for (int i = head[u]; i != -1; i = edges[i].nxt)
            ext[edges[i].to] = true;
        vector<int> tmp = pool;
        pool.clear();
        for (int i = 0, siz = tmp.size(); i < siz; i++)
            if (ext[tmp[i]])
                pool.push_back(tmp[i]);
            else
                q.push(tmp[i]);
        for (int i = head[u]; i != -1; i = edges[i].nxt)
            ext[edges[i].to] = false;
    }
    return tot;
}

int main()
{
    memset(head, -1, sizeof(head));
    scanf("%d%d", &n, &m);
    for (int i = 1, u, v; i <= m; i++)
        scanf("%d%d", &u, &v), addpath(u, v), addpath(v, u);
    for (int i = 1; i <= n; i++)
        pool.push_back(i);
    vector<int> ans;
    for (int i = 1; i <= n; i++)
        if (vis[i] == false)
            ans.push_back(bfs(i));
    sort(ans.begin(), ans.end());
    printf("%d\n", ans.size());
    for (int i = 0, siz = ans.size(); i < siz; i++)
        printf("%d ", ans[i]);
    return 0;
}