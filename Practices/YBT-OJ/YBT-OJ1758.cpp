// YBT-OJ1758.cpp
#include <bits/stdc++.h>

using namespace std;

const int MAX_N = 1000100;

int head[MAX_N], current, n, m, dist[MAX_N], down[MAX_N], son[MAX_N];
int siz[MAX_N], ans[MAX_N], upweight[MAX_N];
vector<int> vec[MAX_N], target;

struct edge
{
    int to, nxt, weight;
} edges[MAX_N << 1];

void addpath(int src, int dst, int weight)
{
    edges[current].to = dst, edges[current].nxt = head[src];
    edges[current].weight = weight, head[src] = current++;
}

int search(int jud, int u)
{
    int l = 0, r = vec[u].size() - 1, pans = 0;
    while (l <= r)
    {
        int mid = (l + r) >> 1;
        if (vec[u][mid] <= (jud >> 1))
            l = mid + 1, pans = mid;
        else
            r = mid - 1;
    }

    if (pans + 1 < vec[u].size() && max(jud - vec[u][pans], vec[u][pans]) > max(vec[u][pans + 1], jud - vec[u][pans + 1]))
        return max(vec[u][pans + 1], jud - vec[u][pans + 1]);

    return max(vec[u][pans], jud - vec[u][pans]);
}

void merge(vector<int> &a, vector<int> &b)
{
    target.clear();
    int lptr = 0, rptr = 0, r1 = a.size() - 1, r2 = b.size() - 1;
    while (lptr <= r1 && rptr <= r2)
        if (a[lptr] < b[rptr])
            target.push_back(a[lptr++]);
        else
            target.push_back(b[rptr++]);
    while (lptr <= r1)
        target.push_back(a[lptr++]);
    while (rptr <= r2)
        target.push_back(b[rptr++]);
    a = target;
}

void dfs(int u, int fa)
{
    int mx = -1, smx = -1;
    for (int i = head[u]; i != -1; i = edges[i].nxt)
        if (edges[i].to != fa)
        {
            dist[edges[i].to] = dist[u] + edges[i].weight, upweight[edges[i].to] = edges[i].weight;
            dfs(edges[i].to, u), down[u] = max(down[u], down[edges[i].to] + edges[i].weight);
            if (mx == -1 || down[edges[i].to] > down[mx])
                swap(mx, smx), mx = edges[i].to;
            else if (smx == -1 || down[edges[i].to] > down[smx])
                smx = edges[i].to;
        }
    for (int i = head[u]; i != -1; i = edges[i].nxt)
        if (edges[i].to != fa && down[edges[i].to] == down[u] - edges[i].weight)
            merge(vec[u], vec[edges[i].to]);
    if (mx == -1)
    {
        vec[u].push_back(0), ans[u] = 0;
        return;
    }
    else
    {
        vec[u].push_back(down[u]);
        if (smx == -1)
            ans[u] = search(down[u], u);
        else
            ans[u] = search(down[u] + down[smx] + upweight[smx], u);
    }
}

int main()
{
    /*
    int size = 256 << 20; // 256MB
    char *p = (char *)malloc(size) + size;
    __asm__("movl %0, %%esp\n" ::"r"(p));
    */
    memset(head, -1, sizeof(head));
    scanf("%d", &n);
    for (int i = 1, u, v, w; i <= n - 1; i++)
        scanf("%d%d%d", &u, &v, &w), addpath(u, v, w), addpath(v, u, w);
    dfs(1, 0);
    for (int i = 1; i <= n; i++)
        printf("%d\n", ans[i]);
    exit(0);
    return 0;
}