// P4436.cpp
#include <bits/stdc++.h>

using namespace std;

const int MAX_N = 1e6 + 200;

int n, m, p, lft[MAX_N], rig[MAX_N], id[MAX_N], deg[MAX_N], tdeg[MAX_N], dir[MAX_N], ncnt = 1;
int topoidx[MAX_N], tot, pos[MAX_N];

int main()
{
    memset(lft, 0x3f, sizeof(lft));
    scanf("%d%d%d", &n, &m, &p);
    for (int i = 1, x, y; i <= m; i++)
    {
        scanf("%d%d", &x, &y), pos[x] = y;
        if (x < y)
            dir[x] = -1, tdeg[x]++;
        else
            dir[x] = 1, tdeg[x + 1]++;
    }
    for (int i = 1; i <= n; i++)
    {
        if (dir[i - 1] != 0)
            ncnt++;
        id[i] = ncnt, deg[ncnt] += tdeg[i];
        lft[ncnt] = min(lft[ncnt], i), rig[ncnt] = max(rig[ncnt], i);
    }
    queue<int> q;
    for (int i = 1; i <= ncnt; i++)
        if (deg[i] == 0)
            q.push(i);
    while (!q.empty())
    {
        int u = q.front();
        q.pop(), topoidx[++tot] = u;
        if (u > 1 && dir[lft[u] - 1] == -1)
            if (--deg[u - 1] == 0)
                q.push(u - 1);
        if (u < ncnt && dir[rig[u]] == 1)
            if (--deg[u + 1] == 0)
                q.push(u + 1);
    }
    for (int ptr = tot; ptr >= 1; ptr--)
    {
        int u = topoidx[ptr], cl = lft[u], cr = rig[u];
        bool toExtent = true;
        while (toExtent)
        {
            toExtent = false;
            if (cr < n && pos[cr] >= cl && pos[cr] <= cr)
                cr = rig[id[cr + 1]], toExtent = true;
            if (cl > 1 && pos[cl - 1] >= cl && pos[cl - 1] <= cr)
                cl = lft[id[cl - 1]], toExtent = true;
        }
        lft[u] = cl, rig[u] = cr;
    }
    while (p--)
    {
        int x, y;
        scanf("%d%d", &x, &y);
        if (lft[id[x]] <= y && y <= rig[id[x]])
            puts("YES");
        else
            puts("NO");
    }
    return 0;
}