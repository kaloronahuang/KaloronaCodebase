// T2_ext_ext.cpp
#include <iostream>
#include <algorithm>
#include <vector>
#include <queue>
using namespace std;
const int INF = 2147483647;
// Data structure;
struct edge
{
    int dst, degree;

    bool operator<(const edge &e) const
    {
        return degree > e.degree;
    }

    edge(){};
    edge(int dst, int dg)
    {
        this->dst = dst;
        this->degree = dg;
    }
};

struct point
{
    vector<edge> edges;
};
// Data block;
vector<point> point_pool;
vector<bool> hallysRoom;
int n, m, k, x, y;

void add_edge(int src, int dst, int dg)
{
    edge e;
    e.dst = dst;
    e.degree = dg;
    point_pool[src].edges.push_back(e);
}

void init()
{
    cin >> n >> m >> k;
    hallysRoom.resize(n + 1, false);
    point_pool.resize(n + 1);
    for (int i = 0; i < k; i++)
    {
        int room;
        cin >> room;
        hallysRoom[room] = true;
    }
    for (int i = 0; i < m; i++)
    {
        int src, dst, dg;
        cin >> src >> dst >> dg;
        add_edge(src, dst, dg);
        add_edge(dst, src, dg);
    }
    cin >> x >> y;
}

int djistkra_halley(int dst, bool access)
{
    priority_queue<edge> pq;
    vector<bool> vis(n + 1, false);
    vector<int> dis(n + 1, INF);
    for (int i = 0; i < point_pool[1].edges.size(); i++)
    {
        dis[point_pool[1].edges[i].dst] = point_pool[1].edges[i].degree;
        pq.push(point_pool[1].edges[i]);
    }
    while (!pq.empty())
    {
        edge e = pq.top();
        pq.pop();
        if (vis[e.dst])
            continue;
        vis[e.dst] = true;
        int to = e.dst;
        for (int i = 0; i < point_pool[to].edges.size(); i++)
        {
            int nex = point_pool[to].edges[i].dst;
            int computed = dis[to] + point_pool[to].edges[i].degree;
            if (dis[nex] >= computed && !(access && hallysRoom[e.dst]))
            {
                dis[nex] = computed;
                pq.push(point_pool[to].edges[i]);
            }
        }
    }
    return dis[dst];
}

int main()
{
    init();
    cout << min(max(djistkra_halley(x, true), djistkra_halley(y, false)), max(djistkra_halley(x, false), djistkra_halley(y, true)));
    return 0;
}
