// CF1098A.cpp
#include <bits/stdc++.h>

using namespace std;

const int MAX_N = 1e5 + 200;

int head[MAX_N], current, n, fa[MAX_N], si[MAX_N], max_sum[MAX_N], siz[MAX_N], val[MAX_N];
int gans;

struct edge
{
    int to, nxt;
} edges[MAX_N << 1];

void addpath(int src, int dst)
{
    edges[current].to = dst, edges[current].nxt = head[src];
    head[src] = current++;
}

void dfs(int u)
{
    int sum = 0x3f3f3f3f;
    for (int i = head[u]; i != -1; i = edges[i].nxt)
        sum = min(sum, si[edges[i].to]);
    if (si[u] == -1)
        val[u] = sum - si[fa[u]];
    if (head[u] == -1 && si[u] == -1)
        val[u] = 0;
    for (int i = head[u]; i != -1; i = edges[i].nxt)
    {
        if (si[u] == -1)
            val[edges[i].to] += si[edges[i].to] - val[u] - si[fa[u]];
        dfs(edges[i].to);
    }
}

int main()
{
    memset(head, -1, sizeof(head));
    scanf("%d", &n);
    for (int i = 2; i <= n; i++)
        scanf("%d", &fa[i]), addpath(fa[i], i);
    for (int i = 1; i <= n; i++)
        scanf("%d", &si[i]);
    val[1] = si[1], dfs(1);
    long long sum = 0;
    for (int i = 1; i <= n && sum != -1; i++)
        if (val[i] < 0)
            sum = -1;
        else
            sum += val[i];
    printf("%lld\n", sum);
    return 0;
}