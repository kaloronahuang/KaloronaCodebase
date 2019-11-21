// P5666.cpp
#include <bits/stdc++.h>
#define ll long long

using namespace std;

const int MAX_N = 3e5 + 200;

int head[MAX_N], current, n, T, pson[MAX_N], sson[MAX_N], siz[MAX_N], down[25][MAX_N];
int modsiz[MAX_N], cson[MAX_N], fat[MAX_N], orgfa[MAX_N];
ll ans;

int read()
{
    int x = 0, f = 1;
    char ch = getchar();
    while (!isdigit(ch))
    {
        if (ch == '-')
            f = -1;
        ch = getchar();
    }
    while (isdigit(ch))
        x = (x << 3) + (x << 1) + ch - '0', ch = getchar();
    return x * f;
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

void predfs(int u, int fa)
{
    siz[u] = 1, orgfa[u] = fa;
    for (int i = head[u]; i != -1; i = edges[i].nxt)
        if (edges[i].to != fa)
        {
            predfs(edges[i].to, u), siz[u] += siz[edges[i].to];
            if (siz[edges[i].to] > siz[pson[u]])
                swap(pson[u], sson[u]), pson[u] = edges[i].to;
            else if (siz[edges[i].to] > siz[sson[u]])
                sson[u] = edges[i].to;
        }
    down[0][u] = pson[u];
}

ll validate(int p, int tot_siz) { return p * (max(modsiz[cson[p]], tot_siz - modsiz[p]) <= (tot_siz >> 1)); }

void dfs(int u, int fa)
{
    for (int i = head[u]; i != -1; i = edges[i].nxt)
        if (edges[i].to != fa)
        {
            fat[u] = fat[edges[i].to] = 0;
            modsiz[u] = n - siz[edges[i].to];
            if (pson[u] == edges[i].to)
                cson[u] = sson[u];
            else
                cson[u] = pson[u];
            if (modsiz[fa] > modsiz[cson[u]])
                cson[u] = fa;
            down[0][u] = cson[u];
            for (int lv = 1; lv <= 24; lv++)
                down[lv][u] = down[lv - 1][down[lv - 1][u]];
            int pt = u;
            for (int lv = 24; lv >= 0; lv--)
                if (modsiz[u] - modsiz[down[lv][pt]] <= (modsiz[u] >> 1))
                    pt = down[lv][pt];
            ans += validate(cson[pt], modsiz[u]) + validate(pt, modsiz[u]) + validate(fat[pt], modsiz[u]);
            pt = edges[i].to;
            for (int lv = 24; lv >= 0; lv--)
                if (modsiz[edges[i].to] - modsiz[down[lv][pt]] <= (modsiz[edges[i].to] >> 1))
                    pt = down[lv][pt];
            ans += validate(cson[pt], modsiz[edges[i].to]) + validate(pt, modsiz[edges[i].to]) + validate(fat[pt], modsiz[edges[i].to]);
            fat[u] = edges[i].to, dfs(edges[i].to, u);
        }
    cson[u] = down[0][u] = pson[u], fat[u] = orgfa[u];
    for (int i = 1; i <= 24; i++)
        down[i][u] = down[i - 1][down[i - 1][u]];
    modsiz[u] = siz[u];
}

int main()
{
    T = read();
    while (T--)
    {
        memset(head, -1, sizeof(head)), current = 0, memset(sson, 0, sizeof(sson));
        memset(pson, 0, sizeof(pson)), memset(cson, 0, sizeof(cson));
        n = read();
        for (int i = 1, u, v; i <= n - 1; i++)
            u = read(), v = read(), addpath(u, v), addpath(v, u);
        predfs(1, 0);
        for (int i = 1; i <= 24; i++)
            for (int j = 1; j <= n; j++)
                down[i][j] = down[i - 1][down[i - 1][j]];
        memcpy(modsiz, siz, sizeof(modsiz)), memcpy(cson, pson, sizeof(cson));
        memcpy(fat, orgfa, sizeof(fat)), ans = 0, dfs(1, 0);
        printf("%lld\n", ans);
    }
    return 0;
}