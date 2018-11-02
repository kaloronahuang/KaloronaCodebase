// P3366.cpp
#include <iostream>
#include <vector>
#include <queue>

using namespace std;

const int maxn = 5010;
int n, m;

struct edge
{
    int src, to, weight;

    edge() {}

    edge(int src, int to, int weight)
    {
        this->src = src;
        this->to = to;
        this->weight = weight;
    }

    bool operator<(const edge &e) const
    {
        return weight > e.weight;
    }
};

struct ufset
{
    int mem[maxn];

    ufset()
    {
        for (int i = 0; i < maxn; i++)
            mem[i] = i;
    }

    int find_ele(int idx)
    {
        if (mem[idx] == idx)
            return idx;
        return mem[idx] = find_ele(mem[idx]);
    }

    void unionfy(int a, int b)
    {
        if (find_ele(a) != find_ele(b))
            mem[find_ele(a)] = b;
    }
};
#define map_type vector< vector<edge> >
map_type map;
priority_queue<edge> edge_repo;
ufset us;

void add_edge(int src, int to, int weight)
{
    map[src].push_back(edge(src, to, weight));
    map[to].push_back(edge(to, src, weight));
    edge_repo.push(edge(src, to, weight));
}

bool judge()
{
    int root = us.find_ele(1);
    for (int i = 2; i < n + 1; i++)
        if (root != us.find_ele(i))
            return false;
        else
            root = us.find_ele(i);
    return true;
}

void init()
{
    cin >> n >> m;
    map.resize(n + 1);
    int src, dst, weight;
    for (int i = 0; i < m; i++)
    {
        cin >> src >> dst >> weight;
        add_edge(src, dst, weight);
        us.unionfy(src, dst);
    }
}

int ans = 0;

void mst()
{
    // prepare for set vertices;
    ufset us_;
    while (!edge_repo.empty())
    {
        edge curt_e = edge_repo.top();
        edge_repo.pop();
        if (us_.find_ele(curt_e.src) != us_.find_ele(curt_e.to))
            ans += curt_e.weight, us_.unionfy(curt_e.src, curt_e.to);
    }
    cout << ans;
}

int main()
{
    init();
    if (!judge())
        cout << "orz";
    else
        mst();
    return 0;
}