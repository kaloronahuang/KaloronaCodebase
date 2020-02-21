// BZ3251.cpp
#include <bits/stdc++.h>

using namespace std;

const int MAX_N = 1e5 + 200;

int n, q, fa[MAX_N], val[MAX_N], head[MAX_N], current, dep[MAX_N];
vector<int> tmp;

struct edge
{
    int to, nxt;
} edges[MAX_N << 1];

void addpath(int src, int dst)
{
    edges[current].to = dst, edges[current].nxt = head[src];
    head[src] = current++;
}

bool query(int x, int y)
{
    int acc = 0;
    tmp.clear();
    while (x != y)
    {
        if (dep[x] < dep[y])
            swap(x, y);
        acc++, tmp.push_back(val[x]), x = fa[x];
        if (acc > 48)
            return true;
    }
    tmp.push_back(val[x]), sort(tmp.begin(), tmp.end());
    for (int i = 1, siz = tmp.size(); i < siz - 1; i++)
        if (0LL + tmp[i - 1] + tmp[i] > tmp[i + 1])
            return true;
    return false;
}

void dfs(int u)
{
    dep[u] = dep[fa[u]] + 1;
    for (int i = head[u]; i != -1; i = edges[i].nxt)
        dfs(edges[i].to);
}

int main()
{
    memset(head, -1, sizeof(head));
    scanf("%d%d", &n, &q);
    for (int i = 1; i <= n; i++)
        scanf("%d", &val[i]);
    for (int i = 1, a, b; i <= n - 1; i++)
        scanf("%d%d", &a, &b), fa[b] = a, addpath(a, b);
    dfs(1);
    while (q--)
    {
        int t, a, b;
        scanf("%d%d%d", &t, &a, &b);
        if (t == 1)
            val[a] = b;
        else
            puts(query(a, b) ? "Y" : "N");
    }
    return 0;
}