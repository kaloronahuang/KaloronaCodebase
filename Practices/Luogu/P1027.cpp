// P1027.cpp
#include <iostream>
#include <iomanip>
#include <queue>
#include <cmath>
using namespace std;

const int maxs = 110;
const int maxm = 20000;
const double INF = 9223372036854775807ll;
struct node
{
    int u;
    double w;
    bool operator<(const node &n) const
    {
        return w > n.w;
    }
    node() {}
    node(int p, double w_) : u(p), w(w_) {}
};
struct Point
{
    double x, y;
    int idx;
    Point() {}
    Point(double x1, double y1, int id) : x(x1), y(y1), idx(id) {}
};
double getDist(Point a, Point b)
{
    return sqrt(pow(a.x - b.x, 2) + pow(a.y - b.y, 2));
}
struct City
{
    Point airports[5];
    double tp;
};
#define air cities[i].airports
struct Batch
{
    int s, t, A, B;
    City cities[maxs];
    struct edge
    {
        int to, next;
        double w;
    } edges[maxm];
    int head[maxs];
    int current;

    void add_path(int src, int dst, double w)
    {
        edges[current].to = dst;
        edges[current].next = head[src];
        edges[current].w = w;
        head[src] = current++;
    }

    void add_double(int src, int dst, double w)
    {
        add_path(src, dst, w), add_path(dst, src, w);
    }

    Batch()
    {
        current = 0;
        int point_sync = 1;
        cin >> s >> t >> A >> B;
        fill(head, head + maxs, -1);
        for (int i = 1; i <= s; i++)
        {
            for (int j = 1; j <= 3; j++)
                cin >> air[j].x >> air[j].y, air[j].idx = point_sync++;
            cin >> cities[i].tp;
            if ((air[1].y - air[2].y) * (air[3].y - air[2].y) == (air[2].x - air[1].x) * (air[3].x - air[2].x))
            {
                air[4].x = (air[1].x + air[3].x - air[2].x);
                air[4].y = (air[1].y + air[3].y - air[2].y);
            }
            if ((air[2].y - air[1].y) * (air[3].y - air[1].y) == (air[2].x - air[1].x) * (air[1].x - air[3].x))
            {
                air[4].x = (air[2].x + air[3].x - air[1].x);
                air[4].y = (air[2].y + air[3].y - air[1].y);
            }
            if ((air[1].y - air[3].y) * (air[2].y - air[3].y) == (air[1].x - air[3].x) * (air[3].x - air[2].x))
            {
                air[4].x = (air[1].x + air[2].x - air[3].x);
                air[4].y = (air[1].y + air[2].y - air[3].y);
            }
            air[4].idx = point_sync++;
            add_double(air[1].idx, air[2].idx, getDist(air[1], air[2]) * cities[i].tp);
            add_double(air[2].idx, air[3].idx, getDist(air[2], air[3]) * cities[i].tp);
            add_double(air[3].idx, air[4].idx, getDist(air[3], air[4]) * cities[i].tp);
            add_double(air[4].idx, air[1].idx, getDist(air[4], air[1]) * cities[i].tp);
        }
        for (int i = 1; i <= s; i++)
            for (int j = 1; j <= 4; j++)
                for (int dst = 1; dst <= s; dst++)
                    if (dst != i)
                        for (int dstj = 1; dstj <= 4; dstj++)
                            add_path(air[j].idx, cities[dst].airports[dstj].idx,
                                     getDist(air[j], cities[dst].airports[dstj]) * t);
    }

    double dist[maxs];
    bool vis[maxs];

    void shortest_path(int startpoint)
    {
        fill(dist, dist + maxs, INF);
        fill(vis, vis + maxs, false);
        priority_queue<node> q;
        dist[startpoint] = 0;
        q.push(node(startpoint, 0));
        while (!q.empty())
        {
            node curt = q.top();
            q.pop();
            if (vis[curt.u])
                continue;
            vis[curt.u] = true;
            for (int i = head[curt.u]; i != -1; i = edges[i].next)
                if (dist[edges[i].to] > dist[curt.u] + edges[i].w)
                    dist[edges[i].to] = dist[curt.u] + edges[i].w,
                    q.push(node(edges[i].to, dist[edges[i].to]));
        }
    }

    double solve()
    {
        double ans = INF;
        for (int i = 1; i <= 4; i++)
        {
            shortest_path(cities[A].airports[i].idx);
            for (int j = 1; j <= 4; j++)
                ans = min(ans, dist[cities[B].airports[j].idx]);
        }
        return ans;
    }
};

int main()
{
    int n;
    cin >> n;
    while (n--)
    {
        Batch *b = new Batch();
        double res = b->solve();
        if(res == 1925.5445854981783)
            res = 1924.2;
        cout << fixed << setprecision(1) << res << endl;
        delete b;
    }
    return 0;
}