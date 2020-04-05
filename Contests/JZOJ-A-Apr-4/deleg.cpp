// deleg.cpp
#include <bits/stdc++.h>

using namespace std;

const int MAX_N = 1e5 + 200;

int n, head[MAX_N], current;

struct edge
{
    int to, nxt;
} edges[MAX_N << 1];

void fileIO()
{
    freopen("deleg.in", "r", stdin);
    freopen("deleg.out", "w", stdout);
}

void addpath(int src, int dst)
{
    edges[current].to = dst, edges[current].nxt = head[src];
    head[src] = current++;
}

int dfs(int u, int fa, int len)
{
    multiset<int> ms;
    for (int i = head[u], res; i != -1; i = edges[i].nxt)
        if (edges[i].to != fa)
        {
            res = dfs(edges[i].to, u, len);
            if (res == -1)
                return -1;
            ms.insert(res + 1);
        }
    int lft = 0, rig = 0;
    while (!ms.empty())
    {
        int u = *ms.begin();
        ms.erase(ms.begin());
        if (u >= len)
            lft = u;
        else
        {
            multiset<int>::iterator it = ms.lower_bound(len - u);
            if (it == ms.end())
            {
                if (lft > 0)
                    return -1;
                lft = u;
            }
            else
            {
                if (*it >= len)
                    rig = u;
                ms.erase(it);
            }
        }
    }
    if (u != 1)
        return lft ? lft : rig;
    else
        return lft;
}

bool check(int len)
{
    int res = dfs(1, 0, len);
    return res == 0 || res >= len;
}

int main()
{
    // fileIO();
    memset(head, -1, sizeof(head));
    scanf("%d", &n);
    for (int i = 1, u, v; i <= n - 1; i++)
        scanf("%d%d", &u, &v), addpath(u, v), addpath(v, u);
    int l = 1, r = n, res = 0;
    while (l <= r)
    {
        int mid = (l + r) >> 1;
        if (check(mid))
            l = mid + 1, res = mid;
        else
            r = mid - 1;
    }
    printf("%d\n", res);
    return 0;
}