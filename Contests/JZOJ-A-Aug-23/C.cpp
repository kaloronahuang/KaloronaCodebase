// C.cpp
#include <bits/stdc++.h>

using namespace std;

const int MAX_N = 5e5 + 200;

int n, head[MAX_N], current, deg[MAX_N], answers[MAX_N];
bool vis[MAX_N], tag[MAX_N];
struct line
{
    int l, r;
} lns[MAX_N];
vector<int> mp;
struct edge
{
    int to, nxt, id;
} edges[MAX_N << 1];

void addpath(int src, int dst, int id)
{
    edges[current].nxt = head[src], edges[current].to = dst;
    edges[current].id = id, head[src] = current++;
}

void dfs(int u)
{
    tag[u] = true;
    for (int i = head[u]; i != -1; i = edges[i].nxt)
        if (!vis[i])
        {
            vis[i] = vis[i ^ 1] = true;
            answers[edges[i].id] = (u < edges[i].to);
            dfs(edges[i].to);
        }
}

int main()
{
    memset(head, -1, sizeof(head));
    scanf("%d", &n);
    for (int i = 1; i <= n; i++)
        scanf("%d%d", &lns[i].l, &lns[i].r), lns[i].r++, mp.push_back(lns[i].l), mp.push_back(lns[i].r);

    sort(mp.begin(), mp.end());
    mp.erase(unique(mp.begin(), mp.end()), mp.end());
    for (int i = 1; i <= n; i++)
    {
        lns[i].l = lower_bound(mp.begin(), mp.end(), lns[i].l) - mp.begin() + 1;
        lns[i].r = lower_bound(mp.begin(), mp.end(), lns[i].r) - mp.begin() + 1;
        addpath(lns[i].l, lns[i].r, i), addpath(lns[i].r, lns[i].l, i);
        deg[lns[i].l]++, deg[lns[i].r]++;
    }
    int last_pt = 0;
    for (int i = 1, siz = mp.size(); i <= siz; i++)
        if (deg[i] & 1)
            if (last_pt == 0)
                last_pt = i;
            else
                addpath(i, last_pt, 0), addpath(last_pt, i, 0), deg[i]++, deg[last_pt]++, last_pt = 0;
    for (int i = 1, siz = mp.size(); i <= siz; i++)
        if (!tag[i])
            dfs(i);
    for (int i = 1; i <= n; i++)
        printf("%d ", answers[i]);
    return 0;
}

