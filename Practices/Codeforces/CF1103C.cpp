// CF1103C.cpp
#include <bits/stdc++.h>

using namespace std;

const int MAX_N = 2.5e5 + 200, MAX_M = 5e5 + 200;

int n, m, k, head[MAX_N], current, dep[MAX_N], up[MAX_N];
bool flag;
vector<int> lf;

struct edge
{
    int to, nxt;
} edges[MAX_M << 1];

void addpath(int src, int dst)
{
    edges[current].to = dst, edges[current].nxt = head[src];
    head[src] = current++;
}

void dfs(int u, int fa)
{
    up[u] = fa, dep[u] = dep[fa] + 1;
    if (dep[u] >= (n + k - 1) / k && (!flag))
    {
        flag = true, puts("PATH");
        printf("%d\n", dep[u]);
        for (int v = u; v; v = up[v])
            printf("%d ", v);
        return (void)(puts(""));
    }
    bool leaf = true;
    for (int i = head[u]; i != -1; i = edges[i].nxt)
        if (edges[i].to != fa && dep[edges[i].to] == 0)
            dfs(edges[i].to, u), leaf = false;
    if (leaf)
        lf.push_back(u);
}

int main()
{
    memset(head, -1, sizeof(head));
    scanf("%d%d%d", &n, &m, &k);
    for (int i = 1, u, v; i <= m; i++)
        scanf("%d%d", &u, &v), addpath(u, v), addpath(v, u);
    dfs(1, 0);
    if (flag)
        return 0;
    puts("CYCLES");
    for (int loop_idx = 1; loop_idx <= k; loop_idx++)
    {
        int pt = lf[loop_idx - 1];
        flag = false;
        vector<int> pos;
        for (int i = head[pt]; i != -1; i = edges[i].nxt)
        {
            if (pos.size() != 2)
                pos.push_back(edges[i].to);
            if (edges[i].to == up[pt] || (dep[pt] - dep[edges[i].to] + 1) % 3 == 0)
                continue;
            printf("%d\n", dep[pt] - dep[edges[i].to] + 1);
            for (int p = pt; p != up[edges[i].to]; p = up[p])
                printf("%d ", p);
            puts(""), flag = true;
            break;
        }
        if (flag)
            continue;
        sort(pos.begin(), pos.end(), [](int a, int b) { return dep[a] < dep[b]; });
        printf("%d\n", dep[pos[1]] - dep[pos[0]] + 1);
        int p = pos[1], neck = pos[0];
        while (p != up[neck])
            printf("%d ", p), p = up[p];
        puts("");
    }
    return 0;
}