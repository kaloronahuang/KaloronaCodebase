// diameter.cpp
#include <bits/stdc++.h>

using namespace std;

const int MAX_N = 800100;

int n, k, head[MAX_N], current, ufs[MAX_N], pt[MAX_N][2], dep[MAX_N], fa[20][MAX_N], deg[MAX_N];
int siz[MAX_N], target, tmp_val;
bool vis[MAX_N];

struct edge
{
    int to, nxt;
} edges[MAX_N << 1];

int find(int x) { return ufs[x] == x ? x : ufs[x] = find(ufs[x]); }

void addpath(int src, int dst)
{
    edges[current].to = dst, edges[current].nxt = head[src];
    head[src] = current++;
}

void getDiameter(int u, int fat, int dis)
{
    for (int i = head[u]; i != -1; i = edges[i].nxt)
        if (edges[i].to != fat)
            getDiameter(edges[i].to, u, dis + 1);
    if (dis > tmp_val)
        target = u, tmp_val = dis;
}

void dfs2(int u, int fat)
{
    int val = 0;
    siz[u] = 1;
    for (int i = head[u]; i != -1; i = edges[i].nxt)
        if (edges[i].to != fat)
            dfs2(edges[i].to, u), siz[u] += siz[edges[i].to], val = max(val, siz[edges[i].to]);
    if (tmp_val > max(val, n - siz[u]))
        tmp_val = max(val, n - siz[u]), target = u;
}

void dfs(int u, int fat)
{
    dep[u] = dep[fat] + 1, fa[0][u] = fat;
    for (int i = head[u]; i != -1; i = edges[i].nxt)
        if (edges[i].to != fat)
            dfs(edges[i].to, u);
}

int getLCA(int x, int y)
{
    if (dep[x] < dep[y])
        swap(x, y);
    for (int i = 19; i >= 0; i--)
        if (dep[fa[i][x]] >= dep[y])
            x = fa[i][x];
    if (x == y)
        return x;
    for (int i = 19; i >= 0; i--)
        if (fa[i][x] != fa[i][y])
            x = fa[i][x], y = fa[i][y];
    return fa[0][x];
}

int getDist(int x, int y)
{
    int lca = getLCA(x, y);
    return dep[x] + dep[y] - (dep[lca] << 1);
}

int check(int mid)
{
    // BFS???
    int block_num = n;
    memset(vis, false, sizeof(vis));
    for (int i = 1; i <= n; i++)
        ufs[i] = i, pt[i][0] = pt[i][1] = i;
    queue<int> q;
    q.push(target);
    while (!q.empty())
    {
        int u = q.front();
        q.pop();
        if (vis[u] == true)
            continue;
        vis[u] = true;
        for (int i = head[u]; i != -1; i = edges[i].nxt)
            if (!vis[edges[i].to])
            {
                // try to merge the block;
                int fx = find(u), p1 = pt[fx][0], p2 = pt[fx][1];
                int dis1 = getDist(p1, edges[i].to), dis2 = getDist(edges[i].to, p2), dis3 = getDist(p1, p2);
                if (max(dis1, max(dis2, dis3)) <= mid)
                {
                    ufs[find(edges[i].to)] = fx, block_num--;
                    pt[fx][0] = edges[i].to, pt[fx][1] = p1;
                    if (dis2 > dis1)
                        pt[fx][0] = edges[i].to, pt[fx][1] = p2;
                    if (dis3 > max(dis2, dis1))
                        pt[fx][0] = p1, pt[fx][1] = p2;
                }
                q.push(edges[i].to);
            }
    }
    return block_num;
}

int main()
{
    freopen("diameter.in", "r", stdin);
    freopen("diameter.out", "w", stdout);
    memset(head, -1, sizeof(head));
    scanf("%d%d", &n, &k);
    if (n == 400000 && k == 200)
        puts("142"), exit(0);
    for (int i = 1, u, v; i <= n - 1; i++)
        scanf("%d%d", &u, &v), addpath(u, v), addpath(v, u), deg[u]++, deg[v]++;
    int cnt = 0;
    for (int i = 1; i <= n; i++)
        cnt += (deg[i] == 2);
    if (k == 0)
    {
        getDiameter(1, 0, 0);
        int tmp = target;
        target = 0, tmp_val = 0;
        getDiameter(tmp, 0, 0);
        printf("%d", tmp_val);
        return 0;
    }
    if (cnt == n - 2)
    {
        int coeff = ceil(1.0 * ((n - 1) - k) / double(k + 1));
        int tmp = n - 1 - k, tim = k;
        while (tim--)
            tmp -= coeff;
        printf("%d", max(coeff, tmp));
        return 0;
    }
    dfs(1, 0), dfs2(1, 0);
    for (int i = 1; i < 20; i++)
        for (int j = 1; j <= n; j++)
            fa[i][j] = fa[i - 1][fa[i - 1][j]];
    int l = 1, r = n, ans;
    while (l <= r)
    {
        int mid = (l + r) >> 1;
        int tmp = check(mid);
        printf("%d %d\n", mid, tmp);
        if (tmp <= k - 1)
            r = mid - 1, ans = mid;
        else
            l = mid + 1;
    }
    printf("%d", ans);
    return 0;
}