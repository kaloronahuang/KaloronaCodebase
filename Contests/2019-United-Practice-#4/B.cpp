// B.cpp
#include <bits/stdc++.h>

using namespace std;

const int MAX_N = 3e5 + 200;

int T, n, m, head[MAX_N], current, dist[MAX_N], li[MAX_N], ri[MAX_N];
int deg[MAX_N], tmp_deg[MAX_N], topo_order[MAX_N], idx[MAX_N], ans[MAX_N];
bool vis[MAX_N];
vector<int> rnk[MAX_N];

inline int read()
{
    char ch = getchar();
    int x = 0, f = 1;
    while (ch < '0' || ch > '9')
        f *= (ch == '-') ? -1 : 1, ch = getchar();
    while ('0' <= ch && ch <= '9')
        x = x * 10 + ch - '0', ch = getchar();
    return x * f;
}

struct edge
{
    int to, nxt;
} edges[MAX_N * 10];

struct compareBox
{
    bool operator()(int a, int b) { return ri[a] > ri[b]; }
};

void addpath(int src, int dst)
{
    edges[current].to = dst, edges[current].nxt = head[src];
    head[src] = current++, deg[dst]++;
}

bool isLoopExist()
{
    queue<int> q;
    for (int i = 1; i <= n; i++)
        if (deg[i] == 0)
            q.push(i);
    int tot = 0;
    while (!q.empty())
    {
        int u = q.front();
        q.pop();
        topo_order[++tot] = u;
        for (int i = head[u]; i != -1; i = edges[i].nxt)
            if (--(deg[edges[i].to]) == 0)
                q.push(edges[i].to);
    }
    return (tot == n);
}

void toposort()
{
    for (int i = 1; i <= n; i++)
        rnk[i].clear();
    for (int i = 1; i <= n; i++)
        if (deg[i] == 0)
            rnk[li[i]].push_back(i);
    for (int i = 1; i <= n; i++)
        ans[i] = 0;
    priority_queue<int, vector<int>, compareBox> q;
    for (int now = 1; now <= n; now++)
    {
        int len = rnk[now].size();
        for (int i = 0; i < len; i++)
            q.push(rnk[now][i]);
        if (q.empty())
        {
            puts("NO");
            return;
        }
        int u = q.top();
        q.pop();
        if (ri[u] < now)
        {
            puts("NO");
            return;
        }
        ans[now] = u;
        for (int i = head[u]; i != -1; i = edges[i].nxt)
            if (--deg[edges[i].to] == 0)
                if (li[edges[i].to] <= now)
                    q.push(edges[i].to);
                else
                    rnk[li[edges[i].to]].push_back(edges[i].to);
    }
    puts("YES");
    for (int i = 1; i <= n; i++)
        printf("%d ", ans[i]);
}

int main()
{
    freopen("rank.in", "r", stdin);
    freopen("rank.out", "w", stdout);
    T = read();
    while (T--)
    {
        n = read(), current = 0;
        memset(head, -1, sizeof(head)), memset(deg, 0, sizeof(deg));
        for (int i = 1; i <= n; i++)
            li[i] = read(), ri[i] = read();
        m = read();
        for (int i = 1, u, v; i <= m; i++)
            u = read(), v = read(), addpath(u, v);
        memcpy(tmp_deg, deg, sizeof(deg));
        if (!isLoopExist())
        {
            puts("NO");
            continue;
        }
        swap(deg, tmp_deg);
        for (int id = n; id >= 1; id--)
            for (int u = topo_order[id], i = head[u]; i != -1; i = edges[i].nxt)
                ri[u] = min(ri[u], ri[edges[i].to] - 1);
        for (int i = 1; i <= n; i++)
            if (li[i] > ri[i])
            {
                puts("NO");
                continue;
            }
        toposort();
    }
    return 0;
}