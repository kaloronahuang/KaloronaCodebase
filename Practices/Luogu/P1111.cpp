// P1111.cpp
#include <iostream>
#include <queue>

using namespace std;

const int maxn = 1200;
const int INF = 0x7fffffff;
struct edge
{
    int src, to, next, weight;
    bool operator<(const edge &e) const
    {
        return weight > e.weight;
    }
} edges[201000];
int head[maxn];
int current = 0;
int n, m;

struct UFS
{
    int mem[maxn];

    UFS()
    {
        for (int i = 0; i < maxn; i++)
            mem[i] = i;
    }

    int Find(int x)
    {
        if (x == mem[x])
            return x;
        return mem[x] = Find(mem[x]);
    }

    void Unite(int a, int b)
    {
        if (Find(a) != Find(b))
            mem[Find(a)] = Find(b);
    }
} ufs;

int addedge(int src, int dst, int weight)
{
    edges[current].src = src;
    edges[current].to = dst;
    edges[current].weight = weight;
    edges[current].next = head[src];
    head[src] = current++;
    return current - 1;
}

priority_queue<edge> edgesPool;
int ans = 0;

void solve()
{
    while (!edgesPool.empty())
    {
        edge curt = edgesPool.top();
        edgesPool.pop();
        if (ufs.Find(curt.to) == ufs.Find(curt.src))
            continue;
        ans = max(ans, curt.weight);
        ufs.Unite(curt.src, curt.to);
    }
}

int main()
{
    fill(head, head + maxn, -1);
    cin >> n >> m;
    for (int i = 0; i < m; i++)
    {
        int x, y, t;
        cin >> x >> y >> t;
        edgesPool.push(edges[addedge(x, y, t)]);
        edgesPool.push(edges[addedge(y, x, t)]);
    }
    solve();
    for(int i = 1;i<=n;i++)
        for(int j = i+1;j<=n;j++)
            if(ufs.Find(i)!=ufs.Find(j))
            {
                cout<<-1;
                return 0;
            }
    cout << ans;
    return 0;
}