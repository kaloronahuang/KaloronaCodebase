// CF741D.cpp
// dsu on tree;
#include <bits/stdc++.h>

using namespace std;

const int MAX_N = 5e5 + 200;

int head[MAX_N], current, n, fa[MAX_N], siz[MAX_N], lft[MAX_N], rig[MAX_N], ptot;
int son[MAX_N], dep[MAX_N], anti[MAX_N], book[1 << 23], answer[MAX_N], dist[MAX_N];
char opt[10];

struct edge
{
    int to, nxt, weight;
} edges[MAX_N << 1];

void addpath(int src, int dst, int weight)
{
    edges[current].to = dst, edges[current].nxt = head[src];
    edges[current].weight = weight, head[src] = current++;
}

void predfs(int u)
{
    lft[u] = ++ptot, siz[u] = 1, dep[u] = dep[fa[u]] + 1, anti[ptot] = u;
    for (int i = head[u]; i != -1; i = edges[i].nxt)
    {
        dist[edges[i].to] = dist[u] ^ edges[i].weight, predfs(edges[i].to), siz[u] += siz[edges[i].to];
        if (siz[son[u]] < siz[edges[i].to])
            son[u] = edges[i].to;
    }
    rig[u] = ptot;
}

void dfs(int u, bool save)
{
    for (int i = head[u]; i != -1; i = edges[i].nxt)
        if (edges[i].to != son[u])
            dfs(edges[i].to, false), answer[u] = max(answer[u], answer[edges[i].to]);
    if (son[u] != 0)
        dfs(son[u], true), answer[u] = max(answer[u], answer[son[u]]);
    if (book[dist[u]] != 0)
        answer[u] = max(answer[u], book[dist[u]] - dep[u]);
    // iterate the mid char;
    for (int ch = 0; ch <= 21; ch++)
        if (book[dist[u] ^ (1 << ch)])
            answer[u] = max(answer[u], book[dist[u] ^ (1 << ch)] - dep[u]);
    book[dist[u]] = max(book[dist[u]], dep[u]);
    for (int i = head[u]; i != -1; i = edges[i].nxt)
        if (edges[i].to != son[u])
        {
            for (int id = lft[edges[i].to]; id <= rig[edges[i].to]; id++)
            {
                int curt = anti[id];
                if (book[dist[curt]])
                    answer[u] = max(answer[u], dep[curt] + book[dist[curt]] - (dep[u] << 1));
                // iterate the mid char;
                for (int ch = 0; ch <= 21; ch++)
                    if (book[dist[curt] ^ (1 << ch)])
                        answer[u] = max(answer[u], book[dist[curt] ^ (1 << ch)] + dep[curt] - (dep[u] << 1));
            }
            for (int id = lft[edges[i].to]; id <= rig[edges[i].to]; id++)
                book[dist[anti[id]]] = max(book[dist[anti[id]]], dep[anti[id]]);
        }
    if (save == false)
        for (int id = lft[u]; id <= rig[u]; id++)
            book[dist[anti[id]]] = 0;
}

int main()
{
    memset(head, -1, sizeof(head));
    scanf("%d", &n);
    for (int i = 2; i <= n; i++)
        scanf("%d%s", &fa[i], opt + 1), addpath(fa[i], i, 1 << (opt[1] - 'a'));
    predfs(1), dfs(1, true);
    for (int i = 1; i <= n; i++)
        printf("%d ", answer[i]);
    return 0;
}