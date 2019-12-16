// BZ1095.cpp
#include <bits/stdc++.h>
#define pr pair<int, int>

using namespace std;

const int MAX_N = 100100, INF = 0x3f3f3f3f;

int head[MAX_N], current, n, q, upward[MAX_N], siz[MAX_N], fat[20][MAX_N], org_dep[MAX_N];
int groot, lft[MAX_N], rig[MAX_N], ptot, org[MAX_N], anti[MAX_N], gans;
bool tag[MAX_N], stat[MAX_N];
char str[20];

struct heap
{
    priority_queue<int> pq1, pq2;

    void check()
    {
        while (!pq2.empty() && pq1.top() == pq2.top())
            pq1.pop(), pq2.pop();
    }

    int top()
    {
        check();
        return pq1.top();
    }

    void insert(int val) { pq1.push(val); }

    void remove(int val) { pq2.push(val); }

    int size() { return pq1.size() - pq2.size(); }

    int sum()
    {
        int tmp = top(), ret;
        pq1.pop(), ret = tmp + top(), insert(tmp);
        return ret;
    }

} s1[MAX_N], s2[MAX_N], s3;

void insert(heap &s)
{
    if (s.size() >= 2)
        s3.insert(s.sum());
}

void erase(heap &s)
{
    if (s.size() >= 2)
        s3.remove(s.sum());
}

struct edge
{
    int to, nxt;
} edges[MAX_N << 1];

void addpath(int src, int dst)
{
    edges[current].to = dst, edges[current].nxt = head[src];
    head[src] = current++;
}

void dfs_initialize(int u, int fa)
{
    siz[u] = 1, anti[ptot] = u, fat[0][u] = fa, org_dep[u] = org_dep[fa] + 1;
    for (int i = head[u]; i != -1; i = edges[i].nxt)
        if (edges[i].to != fa)
            dfs_initialize(edges[i].to, u), siz[u] += siz[edges[i].to];
}

int getLCA(int x, int y)
{
    if (org_dep[x] < org_dep[y])
        swap(x, y);
    for (int i = 19; i >= 0; i--)
        if (org_dep[fat[i][x]] >= org_dep[y])
            x = fat[i][x];
    if (x == y)
        return x;
    for (int i = 19; i >= 0; i--)
        if (fat[i][x] != fat[i][y])
            x = fat[i][x], y = fat[i][y];
    return fat[0][x];
}

int getDist(int x, int y) { return org_dep[x] + org_dep[y] - (org_dep[getLCA(x, y)] << 1); }

int root, val;

void dfs_find(int u, int fa, int capacity)
{
    siz[u] = 1;
    int m_max = 0;
    for (int i = head[u]; i != -1; i = edges[i].nxt)
        if (edges[i].to != fa && !tag[edges[i].to])
        {
            dfs_find(edges[i].to, u, capacity);
            siz[u] += siz[edges[i].to];
            m_max = max(m_max, siz[edges[i].to]);
        }
    m_max = max(m_max, capacity - siz[u]);
    if (m_max < val)
        val = m_max, root = u;
}

int find_root(int p, int capacity)
{
    root = 0, val = INF;
    dfs_find(p, 0, capacity);
    return root;
}

void solve(int u, int fa, int capacity)
{
    tag[u] = true, upward[u] = fa;
    for (int i = head[u]; i != -1; i = edges[i].nxt)
        if (tag[edges[i].to] == false)
        {
            int root = find_root(edges[i].to, siz[edges[i].to]);
            solve(root, u, siz[root]);
        }
}

void join(int u)
{
    erase(s2[u]), s2[u].insert(0), insert(s2[u]);
    int x = u;
    for (; upward[u]; u = upward[u])
    {
        erase(s2[upward[u]]);
        if (s1[u].size())
            s2[upward[u]].remove(s1[u].top());
        s1[u].insert(getDist(x, upward[u]));
        s2[upward[u]].insert(s1[u].top());
        insert(s2[upward[u]]);
    }
}

void remove(int u)
{
    erase(s2[u]), s2[u].remove(0), insert(s2[u]);
    int x = u;
    for (; upward[u]; u = upward[u])
    {
        erase(s2[upward[u]]);
        s2[upward[u]].remove(s1[u].top());
        s1[u].remove(getDist(x, upward[u]));
        if (s1[u].size())
            s2[upward[u]].insert(s1[u].top());
        insert(s2[upward[u]]);
    }
}

int main()
{
    memset(head, -1, sizeof(head));
    scanf("%d", &n);
    for (int i = 1, u, v; i <= n - 1; i++)
        scanf("%d%d", &u, &v), addpath(u, v), addpath(v, u);
    groot = find_root(1, n), dfs_initialize(groot, 0);
    for (int i = 1; i < 20; i++)
        for (int j = 1; j <= n; j++)
            fat[i][j] = fat[i - 1][fat[i - 1][j]];
    solve(groot, 0, n), scanf("%d", &q);
    for (int i = 1; i <= n; i++)
        join(i);
    int tog = n;
    while (q--)
    {
        scanf("%s", str + 1);
        if (str[1] == 'G')
            if (tog >= 2)
                printf("%d\n", s3.top());
            else
                printf("%d\n", 0);
        else
        {
            int x;
            scanf("%d", &x);
            if (!stat[x])
                tog--, stat[x] = true, remove(x);
            else
                tog++, stat[x] = false, join(x);
        }
    }
    return 0;
}