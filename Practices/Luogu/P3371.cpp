// P3371.cpp
#include <iostream>
#include <queue>

using namespace std;

const int maxn = 60020;
const int maxm = 800020;
const int INF = 2147483647;
struct edge
{
    int to, weight, next;
} edges[maxm];
struct node
{
    int u, w;
    node() {}
    node(int u_, int w_) : u(u_), w(w_) {}
    bool operator<(const node &e) const
    {
        return w > e.w;
    }
};
int head[maxn];
int path[maxn];
bool vis[maxn];
int current = 0;
int N, M, S;

void addedge(int src, int dst, int w)
{
    edges[current].to = dst;
    edges[current].weight = w;
    edges[current].next = head[src];
    head[src] = current++;
}

void getPath()
{
    fill(path, path + maxn, INF);
    path[S] = 0;
    fill(vis, vis + maxn, false);
    priority_queue<node> edgePool;
    edgePool.push(node(S, 0));
    while (!edgePool.empty())
    {
        node curt = edgePool.top();
        edgePool.pop();
        if (vis[curt.u])
            continue;
        vis[curt.u] = true;
        for (int p = head[curt.u]; p != -1; p = edges[p].next)
        {
            int dst = edges[p].to;
            if (path[dst] > path[curt.u] + edges[p].weight)
                path[dst] = path[curt.u] + edges[p].weight, edgePool.push(node(dst, path[dst]));
        }
    }
}

int main()
{
    fill(head, head + maxn, -1);
    cin >> N >> M >> S;
    for (int i = 0; i < M; i++)
    {
        int f, g, w;
        cin >> f >> g >> w;
        addedge(f, g, w);
    }
    getPath();
    path[S] = 0;
    for (int i = 1; i <= N; i++)
        cout << path[i] << " ";
    return 0;
}
