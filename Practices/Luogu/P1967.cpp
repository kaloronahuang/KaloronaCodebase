#include <iostream>
#include <vector>
#include <queue>
#include <cmath>
#include <cstdio>
#include <cstring>

using namespace std;

const int maxn = 100010;
const int INF = 2100000000;

struct UnionFindSet
{
    int mem[maxn];

    UnionFindSet()
    {
        for (int i = 0; i < maxn; i++)
            mem[i] = i;
    }

    int Find(int idx)
    {
        if (mem[idx] == idx)
            return idx;
        return mem[idx] = Find(mem[idx]);
    }

    void Unite(int a, int b)
    {
        if (Find(a) != Find(b))
            mem[Find(a)] = b;
    }
};

struct Edge
{
    int src, dst, weight;
    Edge() {}
    Edge(int s, int ds, int w) : src(s), dst(ds), weight(w) {}
    bool operator<(const Edge &e) const
    {
        return weight < e.weight;
    }
};

struct Graph
{
    int pointNum, edgeNum;
    UnionFindSet ufs;
    vector<Edge> map[maxn];
    vector<Edge> mst[maxn];
    priority_queue<Edge> epool;
    // Note: The origin point is 1;
    int dep[maxn];
    int P[maxn][21];
    int LimitTable[maxn][21];
    bool IsSearched[maxn];

    Graph()
    {
        memset(IsSearched, false, sizeof(IsSearched));
        memset(LimitTable, INF, sizeof(LimitTable));
    }

    void AddEdge(Edge e)
    {
        epool.push(e);
        int siz = map[e.src].size();
        bool flag = false;
        for (int i = 0; i < siz; i++)
            if (map[e.src][i].dst == e.dst)
            {
                map[e.src][i].weight = e.weight;
                flag = true;
                break;
            }
        siz = map[e.dst].size();
        for (int i = 0; i < siz; i++)
            if (map[e.dst][i].dst == e.src)
            {
                map[e.dst][i].weight = e.weight;
                flag = true;
                break;
            }
        if (!flag)
            map[e.src].push_back(e), map[e.dst].push_back(Edge(e.dst, e.src, e.weight));
    }

    void GenerateMST()
    {
        int num = 0;
        while (!epool.empty())
        {
            Edge curt = epool.top();
            epool.pop();
            if (ufs.Find(curt.src) == ufs.Find(curt.dst))
                continue;
            mst[curt.src].push_back(curt);
            mst[curt.dst].push_back(Edge(curt.dst, curt.src, curt.weight));
            ufs.Unite(curt.src, curt.dst);
            num++;
        }
    }

    void DFS(int curt, int father, int depth)
    {
        IsSearched[curt] = true;
        dep[curt] = depth;
        P[curt][0] = father;
        for (int i = 1; (1 << i) <= depth; i++)
        {
            P[curt][i] = P[P[curt][i - 1]][i - 1];
            LimitTable[curt][i] = min(LimitTable[curt][i - 1], LimitTable[P[curt][i - 1]][i - 1]);
        }
        int siz = mst[curt].size();
        for (int i = 0; i < siz; i++)
            if (mst[curt][i].dst != father)
            {
                LimitTable[mst[curt][i].dst][0] = mst[curt][i].weight;
                DFS(mst[curt][i].dst, curt, depth + 1);
            }
    }

    void inquire(int a, int b)
    {
        if (ufs.Find(a) != ufs.Find(b))
        {
            cout << -1 << endl;
            return;
        }
        if (dep[a] > dep[b])
            swap(a, b);
        int ans = INF;
        for (int i = 20; i >= 0; i--)
            if (dep[P[b][i]] >= dep[a])
            {
                ans = min(ans, LimitTable[b][i]);
                b = P[b][i];
            }
        if (a == b)
        {
            cout << ans << endl;
            return;
        }
        for (int i = 20; i >= 0; i--)
            if (P[a][i] != P[b][i])
            {
                ans = min(ans, min(LimitTable[a][i], LimitTable[b][i]));
                a = P[a][i];
                b = P[b][i];
            }
        cout << min(ans, min(LimitTable[a][0], LimitTable[b][0])) << endl;
    }
};

void print(Graph *g)
{
    for (int i = 1; i < g->pointNum; i++)
        for (int j = 0; j < g->mst[i].size(); j++)
            cout << i << " " << g->mst[i][j].dst << " " << g->mst[i][j].weight << endl;
}

int main()
{
    Graph *g = new Graph();
    cin >> g->pointNum >> g->edgeNum;
    for (int i = 0; i < g->edgeNum; i++)
    {
        int src, dst, weight;
        cin >> src >> dst >> weight;
        g->AddEdge(Edge(src, dst, weight));
    }
    g->GenerateMST();
    g->DFS(1, 0, 1);
    int q;
    cin >> q;
    int a, b;
    for (int i = 0; i < q; i++)
    {
        cin >> a >> b;
        if (!(g->IsSearched[a] || g->IsSearched[b]))
            g->DFS(a, 0, 1);
        g->inquire(a, b);
    }
    return 0;
}