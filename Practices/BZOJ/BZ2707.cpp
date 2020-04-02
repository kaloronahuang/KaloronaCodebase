// BZ2707.cpp
#include <bits/stdc++.h>

using namespace std;

const int MAX_N = 1e4 + 200, MAX_M = 1001000;
const double eps = 1e-8;

int n, m, phead[MAX_N], rhead[MAX_N], current, start_pt, end_pt, aff[MAX_N], dfn[MAX_N], low[MAX_N], ptot, stk[MAX_N], tail;
int ncnt, outdeg[MAX_N], indeg[MAX_N], pos[MAX_N];
double mat[220][220], f[MAX_N];
bool vis[MAX_N], inst[MAX_N];
vector<int> sccs[MAX_N];

struct edge
{
    int to, nxt;
} edges[MAX_M * 3];

void addpath(int *header, int src, int dst)
{
    edges[current].to = dst, edges[current].nxt = header[src];
    header[src] = current++;
}

void gauss(int siz)
{
    for (int i = 1; i <= siz; i++)
    {
        int key = i;
        for (int j = i + 1; j <= siz; j++)
            if (fabs(mat[j][i]) > fabs(mat[key][i]))
                key = j;
        if (fabs(mat[key][i]) <= eps)
            continue;
        if (key != i)
            for (int j = 1; j <= siz + 1; j++)
                swap(mat[i][j], mat[key][j]);
        double tmp = mat[i][i];
        for (int j = i; j <= siz + 1; j++)
            mat[i][j] /= tmp;
        for (int j = 1; j <= siz; j++)
            if (i != j)
            {
                double rate = mat[j][i];
                for (int k = i; k <= siz + 1; k++)
                    mat[j][k] -= rate * mat[i][k];
            }
    }
}

void tarjan(int u)
{
    dfn[u] = low[u] = ++ptot, inst[u] = true, stk[++tail] = u;
    for (int i = phead[u]; i != -1; i = edges[i].nxt)
        if (dfn[edges[i].to] == 0)
            tarjan(edges[i].to), low[u] = min(low[u], low[edges[i].to]);
        else if (inst[edges[i].to])
            low[u] = min(low[u], dfn[edges[i].to]);
    if (dfn[u] == low[u])
    {
        ncnt++;
        do
        {
            aff[stk[tail]] = ncnt, sccs[ncnt].push_back(stk[tail]), inst[stk[tail]] = false, pos[stk[tail]] = sccs[ncnt].size();
        } while (stk[tail--] != u);
    }
}

void output(int siz)
{
    for (int i = 1; i <= siz; i++, puts(""))
        for (int j = 1; j <= siz + 1; j++)
            printf("%.3lf ", mat[i][j]);
}

void processSCC(int id)
{
    int siz = sccs[id].size();
    memset(mat, 0, sizeof(mat));
    for (int idx = 1; idx <= siz; idx++)
    {
        int u = sccs[id][idx - 1];
        for (int i = rhead[u]; i != -1; i = edges[i].nxt)
            if (aff[edges[i].to] == aff[u])
            {
                mat[pos[edges[i].to]][pos[u]] += 1.0 / double(outdeg[edges[i].to]);
                mat[pos[edges[i].to]][siz + 1] -= 1.0 / double(outdeg[edges[i].to]);
            }
    }
    for (int idx = 1; idx <= siz; idx++)
    {
        int u = sccs[id][idx - 1];
        mat[idx][siz + 1] -= f[u];
        if (u == end_pt)
            memset(mat[idx], 0, sizeof(mat[idx]));
        mat[idx][idx] -= 1.0;
    }
    gauss(siz);
    for (auto x : sccs[id])
        f[x] = mat[pos[x]][siz + 1];
}

void dfs(int u)
{
    vis[u] = true;
    if (u == end_pt)
        return;
    for (int i = phead[u]; i != -1; i = edges[i].nxt)
    {
        if (aff[edges[i].to] != aff[u])
            indeg[aff[u]]++;
        if (!vis[edges[i].to])
            dfs(edges[i].to);
    }
}

int main()
{
    memset(rhead, -1, sizeof(rhead)), memset(phead, -1, sizeof(phead));
    scanf("%d%d%d%d", &n, &m, &start_pt, &end_pt);
    for (int i = 1, u, v; i <= m; i++)
        scanf("%d%d", &u, &v), addpath(phead, u, v), addpath(rhead, v, u), outdeg[u]++;
    for (int i = 1; i <= n; i++)
        if (!dfn[i])
            tarjan(i);
    dfs(start_pt);
    for (int i = 1; i <= n; i++)
        if (vis[i] && aff[i] != aff[end_pt] && indeg[aff[i]] == 0)
            puts("INF"), exit(0);
    queue<int> q;
    q.push(aff[end_pt]);
    while (!q.empty())
    {
        int u = q.front();
        q.pop();
        processSCC(u);
        if (u == aff[start_pt])
            printf("%.3lf\n", fabs(f[start_pt])), exit(0);
        for (auto key : sccs[u])
            for (int i = rhead[key]; i != -1; i = edges[i].nxt)
                if (aff[edges[i].to] != aff[key])
                {
                    f[edges[i].to] += (f[key] + 1.0) / double(outdeg[edges[i].to]);
                    if (--indeg[aff[edges[i].to]] == 0)
                        q.push(aff[edges[i].to]);
                }
    }
    puts("INF");
    return 0;
}