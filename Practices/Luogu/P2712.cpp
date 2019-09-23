// P2712.cpp
#include <bits/stdc++.h>

using namespace std;

const int MAX_N = 510;

int head[MAX_N], current, n, deg[MAX_N];
bool used[MAX_N];

struct edge
{
    int to, nxt;
} edges[MAX_N * MAX_N];

void addpath(int src, int dst)
{
    edges[current].to = dst, edges[current].nxt = head[src];
    head[src] = current++;
}

int main()
{
    memset(head, -1, sizeof(head));
    scanf("%d", &n);
    for (int i = 1, pos, m, tmp; i <= n; i++)
    {
        scanf("%d%d", &pos, &m), used[pos] = true;
        while (m--)
            scanf("%d", &tmp), addpath(pos, tmp), deg[tmp]++;
    }
    queue<int> q;
    for (int i = 0; i <= 500; i++)
        if (deg[i] == 0 && used[i])
            q.push(i);
    int cnt = 0;
    while (!q.empty())
    {
        int u = q.front();
        q.pop();
        if (used[u])
            cnt++;
        for (int i = head[u]; i != -1; i = edges[i].nxt)
            if ((--deg[edges[i].to]) == 0)
                q.push(edges[i].to);
    }
    if (cnt == n)
        puts("YES");
    else
        printf("%d", n - cnt);
    return 0;
}