// CF1074B.cpp
#include <bits/stdc++.h>

using namespace std;

const int MAX_N = 1010;

int T, n, head[MAX_N], current, k1, k2, p1[MAX_N], p2[MAX_N], dist[MAX_N];
bool tag1[MAX_N], tag2[MAX_N];

struct edge
{
    int to, nxt;
} edges[MAX_N << 1];

void addpath(int src, int dst)
{
    edges[current].to = dst, edges[current].nxt = head[src];
    head[src] = current++;
}

int query(bool typ, int x)
{
    printf("%c %d\n", typ ? 'B' : 'A', x), fflush(stdout);
    scanf("%d", &x);
    return x;
}

int dfs(int u, int fa)
{
    if (tag1[u])
        return u;
    int ret = 0;
    for (int i = head[u]; i != -1; i = edges[i].nxt)
        if (edges[i].to != fa)
        {
            dist[edges[i].to] = dist[u] + 1;
            int tmp = dfs(edges[i].to, u);
            if (dist[tmp] < dist[ret])
                ret = tmp;
        }
    return ret;
}

int main()
{
    scanf("%d", &T);
    while (T--)
    {
        memset(head, -1, sizeof(head)), current = 0, memset(dist, 0, sizeof(dist));
        memset(tag1, false, sizeof(tag1)), memset(tag2, false, sizeof(tag2)), dist[0] = 0x3f3f3f3f;
        scanf("%d", &n);
        for (int i = 1, u, v; i < n; i++)
            scanf("%d%d", &u, &v), addpath(u, v), addpath(v, u);
        scanf("%d", &k1);
        for (int i = 1; i <= k1; i++)
            scanf("%d", &p1[i]), tag1[p1[i]] = true;
        scanf("%d", &k2);
        for (int i = 1; i <= k2; i++)
            scanf("%d", &p2[i]), tag2[p2[i]] = true;
        int center = query(true, p2[1]), pt = dfs(center, 0);
        if (tag2[query(false, pt)])
            printf("C %d\n", pt), fflush(stdout);
        else
            puts("C -1"), fflush(stdout);
    }
    return 0;
}