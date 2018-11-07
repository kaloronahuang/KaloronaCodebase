// D.cpp
#include <iostream>
#include <queue>
#include <vector>
#include <algorithm>
using namespace std;

const int maxn = 100020;
#define ll long long
struct edge
{
    ll to, weight;
};
vector<edge> G[maxn];
ll fa[maxn];
bool vis[maxn], anst[maxn];
ll indeg[maxn];
ll n;

void toposort()
{
    queue<int> pts;
    for (int i = 1; i <= n; i++)
        if (indeg[i] == 0)
            pts.push(i);
    while (!pts.empty())
    {
        int pt = pts.front();
        pts.pop();
        vis[pt] = true;
        int siz = G[pt].size();
        for (int i = 0; i < siz; i++)
        {
            indeg[G[pt][i].to]--;
            if (indeg[G[pt][i].to] == 0)
                pts.push(G[pt][i].to);
        }
    }
}

ll ans = 0;

void dfs(int u, int pre, ll dst)
{
    int siz = G[u].size();
    vis[u] = true;
    for (int i = 0; i < siz; i++)
    {
        edge e = G[u][i];
        if (e.to == dst)
        {
            ans = max(ans, pre + e.weight);
            return;
        }
        if (!vis[e.to])
            dfs(e.to, pre + e.weight, dst);
    }
}

int main()
{
    cin >> n;
    for (int i = 1; i <= n; i++)
    {
        ll dst, w;
        cin >> dst >> w;
        G[i].push_back(edge{dst, w});
        indeg[dst]++;
    }
    toposort();
    for (int i = 1; i <= n; i++)
        if (!vis[i])
            dfs(i, 0, i);
    cout << ans;
    return 0;
}
