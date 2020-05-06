// ARC095D.cpp
#include <bits/stdc++.h>

using namespace std;

const int MAX_N = 1e5 + 200;

int n, head[MAX_N], current, deg[MAX_N], cdeg[MAX_N], odeg[MAX_N], ans[MAX_N], seq[2][MAX_N];
bool tag[MAX_N];

struct edge
{
    int to, nxt;
} edges[MAX_N << 1];

void addpath(int src, int dst)
{
    edges[current].to = dst, edges[current].nxt = head[src];
    head[src] = current++;
}

void solve(int curt, int idx)
{
    int u = curt, fa = 0, ptr = 0;
    seq[idx][++ptr] = 1;
    while (u != fa)
    {
        int cptr = ++ptr;
        for (int i = 1; i <= odeg[u]; i++)
            seq[idx][ptr] = ptr + 1, ptr++;
        seq[idx][ptr] = cptr, cptr = u;
        for (int i = head[u]; i != -1; i = edges[i].nxt)
            if (edges[i].to != fa && !tag[edges[i].to])
            {
                u = edges[i].to;
                break;
            }
        fa = cptr;
    }
    seq[idx][++ptr] = n;
}

int main()
{
    memset(head, -1, sizeof(head));
    scanf("%d", &n);
    for (int i = 1, u, v; i <= n - 1; i++)
        scanf("%d%d", &u, &v), addpath(u, v), addpath(v, u), deg[u]++, deg[v]++;
    for (int i = 1; i <= n; i++)
        if (deg[i] == 1)
            tag[i] = true;
    int max_deg = 0;
    for (int u = 1; u <= n; u++)
        if (tag[u] == false)
        {
            for (int i = head[u]; i != -1; i = edges[i].nxt)
                if (tag[edges[i].to] == false)
                    cdeg[u]++;
                else
                    odeg[u]++;
            max_deg = max(max_deg, cdeg[u]);
            if (cdeg[u] >= 3)
                puts("-1"), exit(0);
        }
    if (max_deg == 0)
    {
        ans[1] = 1, ans[n] = n;
        if (n >= 3)
            ans[n - 1] = 2;
        for (int i = 2, j = 3; i <= n - 2; i++, j++)
            ans[i] = j;
        for (int i = 1; i <= n; i++)
            printf("%d ", ans[i]);
        return 0;
    }
    for (int i = 1; i <= n; i++)
        if (cdeg[i] == 1)
            odeg[i]--;
    for (int i = 1, opt = 0; i <= n; i++)
        if (cdeg[i] == 1)
            solve(i, opt++);
    int verdict = true;
    for (int i = 1; i <= n; i++)
        if (seq[0][i] != seq[1][i])
        {
            verdict = seq[0][i] > seq[1][i];
            break;
        }
    for (int i = 1; i <= n; i++)
        printf("%d ", seq[verdict][i]);
    return 0;
}