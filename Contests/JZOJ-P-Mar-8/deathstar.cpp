// deathstar.cpp
#include <bits/stdc++.h>

using namespace std;

const int MAX_N = 2020;

int n, k, gans, head[MAX_N], current, rhead[MAX_N];
bool mat[MAX_N][MAX_N], vis[MAX_N];
char str[int(1e6) + 5];

struct edge
{
    int to, nxt;
} edges[MAX_N * MAX_N << 1];

void addpath(int *h, int src, int dst)
{
    edges[current].to = dst, edges[current].nxt = h[src];
    h[src] = current++;
}

void fileIO()
{
    freopen("deathstar.in", "r", stdin);
    freopen("deathstar.out", "w", stdout);
}

int getHex(char c)
{
    if (isdigit(c))
        return c - '0';
    else
        return 10 + c - 'A';
}

bool read()
{
    static int sptr = 1, iptr = 3;
    bool ret = (getHex(str[sptr]) >> iptr) & 1;
    iptr--;
    if (iptr < 0)
        sptr++, iptr = 3;
    return ret;
}

void dfs(int u, int limit, int dist)
{
    if (dist == k - 1)
    {
        for (int i = head[u]; i != -1; i = edges[i].nxt)
            if (edges[i].to > limit)
                gans += (vis[edges[i].to] == true);
        return;
    }
    for (int i = head[u]; i != -1; i = edges[i].nxt)
        if (edges[i].to > limit)
            dfs(edges[i].to, limit, dist + 1);
}

int main()
{
    // fileIO();
    memset(head, -1, sizeof(head)), memset(rhead, -1, sizeof(rhead));
    scanf("%d%d%s", &n, &k, str + 1);
    for (int i = 1; i <= n; i++)
        for (int j = i + 1; j <= n; j++)
            if (read())
                mat[i][j] = true, addpath(head, i, j), addpath(rhead, j, i);
            else
                mat[j][i] = true, addpath(head, j, i), addpath(rhead, i, j);
    for (int u = 1; u <= n; u++)
    {
        for (int i = rhead[u]; i != -1; i = edges[i].nxt)
            vis[edges[i].to] = true;
        dfs(u, u, 1);
        for (int i = rhead[u]; i != -1; i = edges[i].nxt)
            vis[edges[i].to] = false;
    }
    printf("%d\n", gans);
    return 0;
}