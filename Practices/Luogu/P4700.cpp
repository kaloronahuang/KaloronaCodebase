// P4700.cpp
#include <bits/stdc++.h>

using namespace std;

const int MAX_N = 6e5 + 200, MAX_E = 9e5 * 4 + 200, INF = 0x3f3f3f3f;

int head[MAX_N], current, n, m, A, B, dfn[MAX_N], low[MAX_N], ptot, stk[MAX_N], tail, ncnt;
int aff[MAX_N], mx[MAX_N], mi[MAX_N];
bool inst[MAX_N], vis[MAX_N];
vector<int> G[MAX_N];

struct edge
{
    int to, nxt;
} edges[MAX_E];

struct point
{
    int x, y, stat, id;
    bool operator<(const point &nd) const { return y > nd.y; }
} pts[MAX_N];

vector<point> lft, rig;

void addpath(int src, int dst)
{
    edges[current].to = dst, edges[current].nxt = head[src];
    head[src] = current++;
}

void tarjan(int u)
{
    dfn[u] = low[u] = ++ptot, inst[u] = true, stk[++tail] = u;
    if (pts[u].stat == 1)
        rig.push_back(pts[u]);
    for (int i = head[u]; i != -1; i = edges[i].nxt)
        if (dfn[edges[i].to] == 0)
            tarjan(edges[i].to), low[u] = min(low[u], low[edges[i].to]);
        else if (inst[edges[i].to])
            low[u] = min(low[u], dfn[edges[i].to]);
    if (dfn[u] == low[u])
    {
        ncnt++;
        do
        {
            inst[stk[tail]] = false, aff[stk[tail]] = ncnt;
        } while (stk[tail--] != u);
    }
}

void dfs(int u)
{
    if (vis[u])
        return;
    vis[u] = true;
    for (int i = 0, siz = G[u].size(); i < siz; i++)
    {
        dfs(G[u][i]);
        mi[u] = min(mi[u], mi[G[u][i]]);
        mx[u] = max(mx[u], mx[G[u][i]]);
    }
}

bool compare(point a, point b) { return a.y > b.y; }

int main()
{
    memset(head, -1, sizeof(head));
    scanf("%d%d%d%d", &n, &m, &A, &B);
    for (int i = 1; i <= n; i++)
    {
        scanf("%d%d", &pts[i].x, &pts[i].y);
        pts[i].stat = (pts[i].x == 0) ? -1 : ((pts[i].x == A) ? 1 : 0);
        pts[i].id = i;
    }
    for (int i = 1, u, v, k; i <= m; i++)
    {
        scanf("%d%d%d", &u, &v, &k);
        addpath(u, v);
        if (k != 1)
            addpath(v, u);
    }
    for (int i = 1; i <= n; i++)
    {
        mi[i] = INF, mx[i] = 0;
        if (pts[i].stat == -1)
        {
            // lft point;
            // go TARJAN!
            lft.push_back(pts[i]);
            if (dfn[i] == 0)
                tarjan(i);
        }
    }
    for (int u = 1; u <= n; u++)
        for (int i = head[u]; i != -1; i = edges[i].nxt)
            if (aff[edges[i].to] != aff[u])
                G[aff[u]].push_back(aff[edges[i].to]);
    sort(lft.begin(), lft.end(), compare), sort(rig.begin(), rig.end(), compare);
    for (int i = 0, siz = rig.size(); i < siz; i++)
    {
        int cpnt = aff[rig[i].id], res = lower_bound(rig.begin(), rig.end(), rig[i], compare) - rig.begin() + 1;
        mi[cpnt] = min(mi[cpnt], res);
        mx[cpnt] = max(mx[cpnt], res);
    }
    for (int i = 0, siz = lft.size(); i < siz; i++)
    {
        int cpnt = aff[lft[i].id];
        dfs(cpnt);
        printf("%d\n", max(mx[cpnt] - mi[cpnt] + 1, 0));
    }
    return 0;
}