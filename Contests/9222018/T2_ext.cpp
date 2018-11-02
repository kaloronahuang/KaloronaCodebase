// T2_ext.cpp
#include <iostream>
#include <queue>
#include <vector>
#include <cstring>

using namespace std;

const int maxn_point = 50010;
const int maxn_edge = 100010;
const int INF = 210000000;

int points[maxn_edge];
int edge[maxn_edge];
int degree[maxn_edge];
int next[maxn_edge];
int up_pointer = 0;
vector<int> hallysRoom;

int n, m, k, x, y;

void add_edge(int src, int dst, int dg)
{
    int cursor = up_pointer;
    next[cursor] = points[src];
    edge[cursor] = dst;
    points[src] = cursor;
    degree[cursor] = dg;
    up_pointer++;
}

int getDegree(int src, int dst)
{
    int nx = points[src];
    while (true)
        if (edge[nx] == dst)
            return degree[nx];
        else if (next[nx] == -1)
            return -1;
        else
            nx = next[nx];
}

void init()
{
    memset(points, -1, sizeof(points));
    memset(edge, -1, sizeof(edge));
    memset(next, -1, sizeof(next));
    cin >> n >> m >> k;
    hallysRoom.resize(k);
    for (int i = 0; i < k; i++)
        cin >> hallysRoom[i];
    for (int i = 0; i < m; i++)
    {
        int src, dst, dg;
        cin >> src >> dst >> dg;
        add_edge(src, dst, dg);
        add_edge(dst, src, dg);
    }
}

struct pair
{
    int index, degree;

    pair() {}

    pair(int idx, int dg)
    {
        index = idx;
        degree = dg;
    }

    bool operator<(pair dst)
    {
        return dst.degree > this->degree;
    }
};

int djisktra_halley()
{
    priority_queue<int> pq;
    vector<int> distance(n, INF);
    vector<bool> vis(n, false);
    
}

int main()
{
    init();
} // T2_ext.cpp