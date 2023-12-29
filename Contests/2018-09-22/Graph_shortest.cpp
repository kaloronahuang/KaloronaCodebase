// T2:LRJ's edition;
#include <iostream>
#include <vector>
#include <queue>
#include <cstring>

using namespace std;

#define INF 21000000

struct edge
{
    int src, dst, distance;

    edge() {}

    edge(int src, int dst, int distance)
    {
        this->src = src;
        this->dst = dst;
        this->distance = distance;
    }
};

struct node
{
    int u, degree;

    node() {}
    node(int u, int degree)
    {
        this->u = u;
        this->degree = degree;
    }

    bool operator<(const node &n) const
    {
        return degree > n.degree;
    }
};

vector< vector<edge> > points;
vector<edge> edges;
vector<bool> access;
int n, m, k, x, y;

void init()
{
    cin >> n >> m >> k;
    points.resize(n + 1);
    edges.resize(m);
    access.resize(n + 1, false);
    for (int i = 0; i < k; i++)
    {
        int pos;
        cin >> pos;
        access[pos] = true;
    }
    for (int i = 0; i < m; i++)
    {
        int src, dst, dis;
        cin >> src >> dst >> dis;
        edge a = edge(src, dst, dis);
        edge b = edge(dst, src, dis);
        points[src].push_back(a);
        points[dst].push_back(b);
        edges.push_back(a);
        edges.push_back(b);
    }
    cin >> x >> y;
}

int d1[100010], d2[100010], d3[100010];

void shortest(int st, int *dis, bool isAccess)
{
    priority_queue<node> pq;
    vector<bool> vis(n + 1, false);
    pq.push(node(st, 0));
    dis[st] = 0;
    while (!pq.empty())
    {
        node currentPoint = pq.top();
        pq.pop();
        if (vis[currentPoint.u])
            continue;
        vis[currentPoint.u] = true;
        for (int i = 0; i < points[currentPoint.u].size(); i++)
        {
            edge to = points[currentPoint.u][i];
            if (vis[to.dst] || (isAccess && access[to.dst]))
                continue;
            int computed = dis[currentPoint.u] + to.distance;
            if (computed < dis[to.dst])
            {
                dis[to.dst] = computed;
                pq.push(node(to.dst, dis[to.dst]));
            }
        }
    }
}

int solve()
{
    memset(d1, INF, sizeof(d1));
    memset(d2, INF, sizeof(d2));
    memset(d3, INF, sizeof(d3));
    shortest(1, d1, false);
    shortest(1, d2, true);
    shortest(x, d3, false);
    int ans = min(max(d1[x], d2[y]), max(d1[y], d2[x]));
    ans = min(ans, d1[x] + d3[y]);
    return ans;
}

int main()
{
    init();
    cout << solve();
    return 0;
}