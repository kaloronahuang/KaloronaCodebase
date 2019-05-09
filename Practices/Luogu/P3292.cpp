// P3292.cpp
#include <bits/stdc++.h>
#define ll long long
using namespace std;

const int MAX_N = 20100;

int head[MAX_N], current, dep[MAX_N], fa[20][MAX_N], n, q;
ll lbs[20][MAX_N][70], ans[70], val[MAX_N];

struct edge
{
    int to, nxt;
} edges[MAX_N << 1];

inline ll read()
{
    char ch = getchar();
    ll x = 0, f = 1;
    while (ch > '9' || ch < '0')
    {
        if (ch == '-')
            f = -1;
        ch = getchar();
    }
    while (ch >= '0' && ch <= '9')
        x = x * 10 + ch - '0', ch = getchar();
    return x * f;
}

void addpath(int src, int dst)
{
    edges[current].to = dst, edges[current].nxt = head[src];
    head[src] = current++;
}

void insert(ll *arr, ll element)
{
    for (int i = 62; i >= 0; i--)
        if ((element >> i) & 1)
        {
            if (arr[i] == 0)
                return (void)(arr[i] = element);
            element ^= arr[i];
        }
}

void merge(ll *src, ll *dst)
{
    for (int i = 62; i >= 0; i--)
        if (src[i])
            insert(dst, src[i]);
}

void dfs(int u)
{
    dep[u] = dep[fa[0][u]] + 1;
    for (int i = head[u]; i != -1; i = edges[i].nxt)
        if (edges[i].to != fa[0][u])
            fa[0][edges[i].to] = u, dfs(edges[i].to);
}

void process_lca()
{
    for (int i = 1; i < 20; i++)
        for (int j = 1; j <= n; j++)
        {
            fa[i][j] = fa[i - 1][fa[i - 1][j]];
            memcpy(lbs[i][j], lbs[i - 1][j], sizeof(lbs[i][j]));
            merge(lbs[i - 1][fa[i - 1][j]], lbs[i][j]);
        }
}

void getLCA(int x, int y)
{
    if (dep[x] < dep[y])
        swap(x, y);
    for (int i = 19; i >= 0; i--)
        if (dep[fa[i][x]] >= dep[y])
            merge(lbs[i][x], ans), x = fa[i][x];
    if (x == y)
    {
        merge(lbs[0][x], ans);
        return;
    }
    for (int i = 19; i >= 0; i--)
        if (fa[i][x] != fa[i][y])
        {
            merge(lbs[i][x], ans), merge(lbs[i][y], ans);
            x = fa[i][x], y = fa[i][y];
        }
    merge(lbs[0][x], ans), merge(lbs[0][y], ans), merge(lbs[0][fa[0][x]], ans);
}

int main()
{
    memset(head, -1, sizeof(head));
    n = read(), q = read();
    for (ll i = 1; i <= n; i++)
        insert(lbs[0][i], read());
    for (int i = 1, tmpx, tmpy; i <= n - 1; i++)
        tmpx = read(), tmpy = read(), addpath(tmpx, tmpy), addpath(tmpy, tmpx);
    dfs(1), process_lca();
    while (q--)
    {
        memset(ans, 0, sizeof(ans));
        ll x, y, answer = 0;
        x = read(), y = read(), getLCA(x, y);
        for (int i = 62; i >= 0; i--)
            if ((answer ^ ans[i]) > answer)
                answer ^= ans[i];
        printf("%lld\n", answer);
    }
    return 0;
}