// LOJ6078.cpp
#include <bits/stdc++.h>

using namespace std;

const int MAX_N = 2020;
const double eps = 1e-8;

typedef pair<double, int> pdi;

int n, m, s, t, head[MAX_N], current, stot, rem[MAX_N];
double E[MAX_N], wseq[MAX_N], eseq[MAX_N];
bool connected[MAX_N], vis[MAX_N];

struct edge
{
    int to, nxt;
    double weight;
} edges[MAX_N];

void addpath(int src, int dst, double weight)
{
    edges[current].to = dst, edges[current].nxt = head[src];
    edges[current].weight = weight, head[src] = current++;
}

double calcBestPair()
{
    priority_queue<pdi, vector<pdi>, greater<pdi>> pq;
    for (int i = 1; i <= stot; i++)
        pq.push(make_pair(wseq[i] + eseq[1], i)), rem[i] = stot;
    double pre_p = 1, res = 0;
    while (!pq.empty() && pre_p > 0)
    {
        pdi curt = pq.top();
        pq.pop();
        double prob = pre_p * double(rem[curt.second] - curt.second) / double(rem[curt.second] - curt.second + 1.0);
        rem[curt.second]--, res += curt.first * (pre_p - prob), pre_p = prob;
        if (rem[curt.second] > 0)
            pq.push(make_pair(wseq[curt.second] + eseq[stot - rem[curt.second] + 1], curt.second));
    }
    return res;
}

void dfs(int u)
{
    vis[u] = true;
    if (u == t)
        return (void)(connected[u] = true);
    for (int i = head[u]; i != -1; i = edges[i].nxt)
    {
        if (!vis[edges[i].to])
            dfs(edges[i].to);
        connected[u] |= connected[edges[i].to];
    }
    if (!connected[u])
        return (void)(E[u] = 1e10);
    bool self_loop = false;
    stot = 0;
    for (int i = head[u]; i != -1; i = edges[i].nxt)
        wseq[++stot] = edges[i].weight, self_loop |= edges[i].to == u;
    sort(wseq + 1, wseq + 1 + stot);
    if (!self_loop)
    {
        stot = 0;
        for (int i = head[u]; i != -1; i = edges[i].nxt)
            eseq[++stot] = E[edges[i].to];
        sort(eseq + 1, eseq + 1 + stot), E[u] = calcBestPair();
    }
    else
    {
        double l = 0, r = 1e6;
        while (l + eps < r)
        {
            double mid = E[u] = (l + r) / 2.0;
            stot = 0;
            for (int i = head[u]; i != -1; i = edges[i].nxt)
                eseq[++stot] = E[edges[i].to];
            sort(eseq + 1, eseq + 1 + stot);
            if (calcBestPair() > mid)
                l = mid;
            else
                r = mid;
        }
        E[u] = l;
    }
}

int main()
{
    memset(head, -1, sizeof(head));
    scanf("%d%d%d%d", &n, &m, &s, &t);
    double w;
    for (int i = 1, u, v; i <= m; i++)
        scanf("%d%d%lf", &u, &v, &w), addpath(u, v, w);
    dfs(s);
    if (connected[s])
        printf("%.10lf\n", E[s]);
    else
        puts("-1");
    return 0;
}