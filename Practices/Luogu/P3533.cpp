// P3533.cpp
#include <bits/stdc++.h>
using namespace std;

const int MAX_N = 501000;

int n, k, fa[20][MAX_N], head[MAX_N], current, component[MAX_N], affroot[MAX_N], deg[MAX_N];
int dep[MAX_N], idx[MAX_N], loop_len[MAX_N];
bool vis[MAX_N], isLoop[MAX_N];
struct edge
{
    int to, nxt;
} edges[MAX_N << 1];

void addpath(int src, int dst)
{
    edges[current].to = dst, edges[current].nxt = head[src];
    head[src] = current++;
}

int find_component(int x) { return component[x] == x ? x : component[x] = find_component(component[x]); }

void unite(int x, int y) { component[find_component(x)] = find_component(y); }

void dfs(int u, int top)
{
    affroot[u] = top, dep[u] = dep[fa[0][u]] + 1;
    if (u == top)
        dep[u] = 1;
    for (int i = head[u]; i != -1; i = edges[i].nxt)
        if (edges[i].to != fa[0][u] && isLoop[edges[i].to] == false)
            dfs(edges[i].to, top);
}

void dfs_loop(int u, int fat)
{
    if (idx[u])
        return;
    idx[u] = idx[fat] + 1;
    dfs_loop(fa[0][u], u);
}

int main()
{
    memset(head, -1, sizeof(head));
    scanf("%d%d", &n, &k);
    for (int i = 1; i <= n; i++)
        component[i] = i;
    for (int i = 1; i <= n; i++)
    {
        scanf("%d", &fa[0][i]);
        if (fa[0][i] == i)
            deg[i]++, fa[0][i] = 0;
        else
        {

            unite(fa[0][i], i);
            addpath(fa[0][i], i), addpath(i, fa[0][i]);
            deg[fa[0][i]]++;
        }
    }
    // find the loop;
    queue<int> q;
    for (int i = 1; i <= n; i++)
        if (deg[i] == 0)
            q.push(i);
    while (!q.empty())
    {
        int u = q.front();
        q.pop(), vis[u] = true;
        for (int i = head[u]; i != -1; i = edges[i].nxt)
            if (vis[edges[i].to] == false && (--deg[edges[i].to]) == 0)
                q.push(edges[i].to);
    }
    for (int i = 1; i <= n; i++)
        if (deg[i] > 0)
            isLoop[i] = true;

    for (int i = 1; i <= n; i++)
        if (isLoop[i])
            dfs(i, i), loop_len[find_component(i)]++;

    for (int i = 1; i <= n; i++)
        if (isLoop[i])
        {
            dfs_loop(i, 0);
            break;
        }

    for (int i = 1; i < 20; i++)
        for (int j = 1; j <= n; j++)
            fa[i][j] = fa[i - 1][fa[i - 1][j]];
    while (k--)
    {
        int x, y;
        scanf("%d%d", &x, &y);
        if (find_component(x) == find_component(y))
        {
            if (affroot[x] == affroot[y])
            {
                // get the lca stuff;
                bool flag = false;
                if (dep[x] < dep[y])
                    swap(x, y), flag = true;
                int ans_x = 0, ans_y = 0;
                for (int i = 19; i >= 0; i--)
                    if (dep[fa[i][x]] >= dep[y])
                        x = fa[i][x], ans_x += (1 << i);
                if (flag)
                    swap(ans_x, ans_y), swap(x, y);
                if (x == y)
                {
                    printf("%d %d\n", ans_x, ans_y);
                    continue;
                }
                for (int i = 19; i >= 0; i--)
                    if (fa[i][x] != fa[i][y])
                        x = fa[i][x], y = fa[i][y], ans_x += (1 << i), ans_y += (1 << i);
                printf("%d %d\n", ans_x + 1, ans_y + 1);
            }
            else
            {
                int ans_x = dep[x] - 1, ans_y = dep[y] - 1;
                bool flag = false;
                x = affroot[x], y = affroot[y];
                if (idx[x] > idx[y])
                    swap(x, y), swap(ans_x, ans_y), flag = true;
                int ans1 = ans_x + (idx[y] - idx[x]), ans2 = ans_y + loop_len[find_component(x)] - (idx[y] - idx[x]);
                if (max(ans1, ans_y) > max(ans2, ans_x))
                    ans_y = ans2;
                else if (max(ans1, ans_y) == max(ans2, ans_x))
                    if (min(ans1, ans_y) > min(ans2, ans_x))
                        ans_y = ans2;
                    else if (min(ans1, ans_y) == min(ans2, ans_x))
                        if (ans1 >= ans_y)
                            ans_x = ans1;
                        else
                            ans_y = ans2;
                    else
                        ans_x = ans1;
                else
                    ans_x = ans1;
                if (flag)
                    swap(x, y), swap(ans_x, ans_y);
                printf("%d %d\n", ans_x, ans_y);
            }
        }
        else
            puts("-1 -1");
    }
    return 0;
}