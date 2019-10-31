// C.cpp
#include <bits/stdc++.h>

using namespace std;

const int MAX_N = 2e5 + 200;

int head[MAX_N], current, n, k, q, vis[MAX_N], pre[MAX_N], lft[MAX_N], ncnt, matching[MAX_N];

struct edge
{
    int to, nxt;
} edges[MAX_N << 1];

void addpath(int src, int dst)
{
    edges[current].to = dst, edges[current].nxt = head[src];
    head[src] = current++;
}

bool hungery(int u, int org)
{
    for (int i = head[u]; i != -1; i = edges[i].nxt)
        if (vis[edges[i].to] != org)
        {
            vis[edges[i].to] = org;
            if (!matching[edges[i].to] || hungery(matching[edges[i].to], org))
            {
                matching[edges[i].to] = u, pre[u] = edges[i].to;
                return true;
            }
        }
    return false;
}

int main()
{
    memset(head, -1, sizeof(head));
    scanf("%d%d", &n, &k);
    for (int i = 1, u, v; i <= k; i++)
    {
        scanf("%d%d", &u, &v);
        addpath(u, i + n), addpath(i + n, u);
        addpath(v, i + n), addpath(i + n, v);
    }
    int lcur = 1;
    for (int i = 1; i <= n; i++)
    {
        // fine the leftmost point to pair a conti;
        while (!hungery(i, ++ncnt) && lcur <= i)
            matching[pre[lcur]] = false, lcur++;
        lft[i] = lcur;
    }
    scanf("%d", &q);
    while (q--)
    {
        int l, r;
        scanf("%d%d", &l, &r);
        if (lft[r] <= l)
            printf("Yes\n");
        else
            printf("No\n");
    }
    return 0;
}