// P1144.cpp
#include <iostream>
#include <queue>

using namespace std;
const int maxn = 1000200;
const int maxm = 2000200;
const int mod = 100003;
struct edge
{
    int to, next;
} edges[maxm << 1];
int head[maxn];
bool vis[maxn];
int dist[maxn];
int ans[maxn];
int current = 0;
int n, m;

struct npair
{
    int u, w;
    bool operator<(const npair &h) const
    {
        return w > h.w;
    }
};

void add_edge(int src, int dst)
{
    edges[current].to = dst;
    edges[current].next = head[src];
    head[src] = current++;
}

void dji()
{
    priority_queue<npair> epool;
    epool.push(npair{1, 0});
    dist[1] = 0;
    ans[1] = 1;
    while (!epool.empty())
    {
        npair crt = epool.top();
        epool.pop();
        if (vis[crt.u])
            continue;
        vis[crt.u] = true;
        for (int i = head[crt.u]; i != -1; i = edges[i].next)
            if (dist[edges[i].to] > dist[crt.u] + 1)
                dist[edges[i].to] = dist[crt.u] + 1, epool.push(npair{edges[i].to, dist[edges[i].to]}),
                ans[edges[i].to] = ans[crt.u];
            else if (dist[edges[i].to] == dist[crt.u] + 1)
                ans[edges[i].to] += ans[crt.u], ans[edges[i].to] %= mod;
    }
}

int main()
{
    cin >> n >> m;
    fill(head, head + n + 10, -1);
    fill(dist, dist + n + 10, 1e9);
    for (int i = 0; i < m; i++)
    {
        int x, y;
        cin >> x >> y;
        add_edge(x, y), add_edge(y, x);
    }
    dji();
    for (int i = 1; i <= n; i++)
        cout << ans[i] << endl;
    return 0;
}