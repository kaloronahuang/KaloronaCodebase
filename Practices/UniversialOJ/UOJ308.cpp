// UOJ308.cpp
#include <bits/stdc++.h>

using namespace std;

const int MAX_N = 1e5 + 200;

int T, n, m, k, head[MAX_N], current, col[MAX_N];

struct edge
{
    int to, nxt;
} edges[MAX_N << 2];

void addpath(int src, int dst)
{
    edges[current].to = dst, edges[current].nxt = head[src];
    head[src] = current++;
}

int fpow(int bas, int tim)
{
    int ret = 1;
    while (tim)
    {
        if (tim & 1)
            ret = 1LL * ret * bas % 6;
        bas = 1LL * bas * bas % 6;
        tim >>= 1;
    }
    return ret;
}

bool dfs(int u, int c)
{
    col[u] = c;
    for (int i = head[u]; i != -1; i = edges[i].nxt)
        if (col[edges[i].to] == -1 && !dfs(edges[i].to, c ^ 1))
            return false;
        else if (col[edges[i].to] != -1 && col[edges[i].to] == c)
            return false;
    return true;
}

int main()
{
    scanf("%d", &T);
    while (T--)
    {
        scanf("%d%d%d", &n, &m, &k);
        memset(head, -1, sizeof(int) * (n + 10));
        memset(col, -1, sizeof(int) * (n + 10));
        current = 0;
        if (m == 0)
        {
            printf("%d\n", fpow(k, n));
            continue;
        }
        for (int i = 1, u, v; i <= m; i++)
            scanf("%d%d", &u, &v), addpath(u, v), addpath(v, u);
        int acc = 2;
        bool flag = true;
        for (int i = 1; i <= n; i++)
            if (col[i] == -1)
                flag &= dfs(i, 0), acc = 2LL * acc % 6;
        if (!flag)
        {
            puts("0");
            continue;
        }
        printf("%lld\n", 1LL * k * acc % 6 * (k - 1) % 6);
    }
    return 0;
}