// CF600E.cpp
#include <bits/stdc++.h>
#define ll long long

using namespace std;

const int MAX_N = 1e5 + 200;

int head[MAX_N], current, col[MAX_N], n, siz[MAX_N], son[MAX_N], lft[MAX_N], rig[MAX_N];
int anti[MAX_N], bucket[MAX_N], ptot;
ll most[MAX_N], answer[MAX_N];

struct edge
{
    int to, nxt;
} edges[MAX_N << 1];

void addpath(int src, int dst)
{
    edges[current].to = dst, edges[current].nxt = head[src];
    head[src] = current++;
}

void predfs(int u, int fa)
{
    lft[u] = ++ptot, anti[ptot] = u, siz[u] = 1;
    for (int i = head[u]; i != -1; i = edges[i].nxt)
        if (edges[i].to != fa)
        {
            predfs(edges[i].to, u), siz[u] += siz[edges[i].to];
            son[u] = (siz[son[u]] < siz[edges[i].to]) ? edges[i].to : son[u];
        }
    rig[u] = ptot;
}

void dfs(int u, int fa, bool save)
{
    for (int i = head[u]; i != -1; i = edges[i].nxt)
        if (edges[i].to != fa && edges[i].to != son[u])
            dfs(edges[i].to, u, false);
    ll acc = 0;
    if (son[u] != 0)
        dfs(son[u], u, true), most[u] = most[son[u]], acc = answer[son[u]];

    if (++bucket[col[u]] > most[u])
        most[u] = bucket[col[u]], acc = col[u];
    else if (bucket[col[u]] == most[u])
        acc += col[u];

    for (int i = head[u]; i != -1; i = edges[i].nxt)
        if (edges[i].to != fa && edges[i].to != son[u])
        {
            for (int id = lft[edges[i].to]; id <= rig[edges[i].to]; id++)
                if (++bucket[col[anti[id]]] > most[u])
                    most[u] = bucket[col[anti[id]]], acc = col[anti[id]];
                else if (bucket[col[anti[id]]] == most[u])
                    acc += col[anti[id]];
        }
    if (save == false)
        for (int id = lft[u]; id <= rig[u]; id++)
            --bucket[col[anti[id]]];
    answer[u] = acc;
}

int main()
{
    memset(head, -1, sizeof(head));
    scanf("%d", &n);
    for (int i = 1; i <= n; i++)
        scanf("%d", &col[i]);
    for (int i = 1, u, v; i <= n - 1; i++)
        scanf("%d%d", &u, &v), addpath(u, v), addpath(v, u);
    predfs(1, 0), dfs(1, 0, true);
    for (int i = 1; i <= n; i++)
        printf("%lld ", answer[i]);
    return 0;
}