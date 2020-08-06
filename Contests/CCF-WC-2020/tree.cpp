// tree.cpp
#include <bits/stdc++.h>

using namespace std;

const int MAX_N = 1e6 + 200;

int n, q, head[MAX_N], current, st[20][MAX_N], stot, dep[MAX_N], dist[MAX_N];
int log2_[MAX_N], pos[MAX_N], up[MAX_N], wi[MAX_N];
bool tag[MAX_N], Stag[MAX_N];
set<int> pset;

struct edge
{
    int to, nxt;
} edges[MAX_N << 1];

void addpath(int src, int dst)
{
    edges[current].to = dst, edges[current].nxt = head[src];
    head[src] = current++;
}

void dfs(int u, int fa)
{
    dep[u] = dep[fa] + 1, st[0][++stot] = u, pos[u] = stot, up[u] = fa;
    for (int i = head[u]; i != -1; i = edges[i].nxt)
        if (edges[i].to != fa)
            dfs(edges[i].to, u), st[0][++stot] = u;
}

int gmin(int x, int y) { return dep[x] < dep[y] ? x : y; }

int getLCA(int x, int y)
{
    if (pos[x] > pos[y])
        swap(x, y);
    int d = log2_[pos[y] - pos[x] + 1];
    return gmin(st[d][pos[x]], st[d][pos[y] - (1 << d) + 1]);
}

namespace Subtask1
{

    void makeDist(int u, int fa)
    {
        dist[u] += (tag[u] == true), Stag[u] = false, wi[u] = (tag[u] == true);
        for (int i = head[u]; i != -1; i = edges[i].nxt)
            if (edges[i].to != fa)
                dist[edges[i].to] = dist[u], makeDist(edges[i].to, u), wi[u] += wi[edges[i].to];
    }

    int handler()
    {
        while (q--)
        {
            int opt, x;
            scanf("%d%d", &opt, &x), tag[x] ^= 1;
            dist[1] = 0, makeDist(1, 0);
            if (opt == 1)
                pset.insert(x);
            else
                pset.erase(x);
            vector<int> vec;
            for (set<int>::iterator it = pset.begin(); it != pset.end(); it++)
                vec.push_back(*it);
            sort(vec.begin(), vec.end(), [](const int &rhs1, const int &rhs2) { return wi[rhs1] > wi[rhs2]; });
            int acc = 0, gacc = 0, ans = 0x3f3f3f3f;
            for (vector<int>::iterator it = vec.begin(); it != vec.end(); it++)
            {
                int u = *it;
                it++;
                if (it == vec.end())
                    acc = 0;
                else
                    acc = wi[*it];
                it--;
                while (u != 0)
                    if (Stag[u] == false)
                    {
                        Stag[u] = true;
                        if (tag[u] == true)
                            gacc++;
                        u = up[u];
                    }
                    else
                        break;
                ans = min(ans, max(gacc, acc));
                if (gacc > acc)
                    break;
            }
            if (vec.empty())
                puts("0");
            else
                printf("%d\n", ans);
        }
        return 0;
    }

} // namespace Subtask1

int main()
{
    freopen("tree.in", "r", stdin);
    freopen("tree.out", "w", stdout);
    memset(head, -1, sizeof(head));
    scanf("%d", &n);
    for (int i = 1, u, v; i <= n - 1; i++)
        scanf("%d%d", &u, &v), addpath(u, v), addpath(v, u);
    scanf("%d", &q), dfs(1, 0);
    for (int i = 1; i < 20; i++)
        for (int j = 1; j <= stot; j++)
            st[i][j] = gmin(st[i - 1][j], st[i - 1][j + (1 << (i - 1))]);
    if (1LL * n * q <= 4e8)
        return Subtask1::handler();
    return 0;
}