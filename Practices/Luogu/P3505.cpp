// P3505.cpp
#include <bits/stdc++.h>

using namespace std;

const int MAX_N = 4e4 + 200, MAX_E = 1e6 + 200;

int n, m, head[MAX_N], current, col[MAX_N];

struct edge
{
    int to, nxt;
} edges[MAX_E << 1];

void addpath(int src, int dst)
{
    edges[current].to = dst, edges[current].nxt = head[src];
    head[src] = current++;
}

int main()
{
    memset(head, -1, sizeof(head));
    scanf("%d%d", &n, &m);
    for (int i = 1, u, v; i <= m; i++)
        scanf("%d%d", &u, &v), addpath(u, v), addpath(v, u);
    int connection[4] = {0, 0, 0, 0};
    for (int i = head[1]; i != -1; i = edges[i].nxt)
        col[edges[i].to] = 1, connection[1]++;
    for (int i = head[2]; i != -1; i = edges[i].nxt)
        col[edges[i].to] = 2, connection[2]++;
    connection[3] = n - connection[1] - connection[2] - 2;
    int org_connection[4] = {0, connection[1], connection[2], connection[3]};
    int ans = 0;
    for (int u = 3; u <= n; u++)
        if (col[u] == 1)
        {
            connection[1]--, ans += connection[1];
            for (int i = head[u]; i != -1; i = edges[i].nxt)
                if (col[edges[i].to] == 1 && edges[i].to > u)
                    ans--;
        }
        else if (col[u] == 2)
        {
            connection[2]--, ans += connection[2];
            for (int i = head[u]; i != -1; i = edges[i].nxt)
                if (col[edges[i].to] == 2 && edges[i].to > u)
                    ans--;
        }
        else
        {
            connection[3]--, ans += connection[3];
            int dir = 0, acc = 0;
            for (int i = head[u]; i != -1; i = edges[i].nxt)
            {
                if (col[edges[i].to] != 0)
                    dir = col[edges[i].to], acc++;
                else if (edges[i].to > u)
                    ans--;
            }
            if (dir == 1)
                ans += org_connection[1] - acc;
            else if (dir == 2)
                ans += org_connection[2] - acc;
            else
                ans += max(org_connection[2], org_connection[1]);
        }
    printf("%d\n", ans);
    return 0;
}