// P1273.cpp
#include <iostream>
#include <cstring>
#include <queue>

using namespace std;

const int maxn = 2900;
int point[maxn];
int to[maxn];
int next[maxn];
int weight[maxn];
int money[maxn];
int F[maxn];
int C[maxn];
int Fat[maxn];
bool rmv[maxn];
bool rec[maxn];

int current = 0;
int N, M;

void add_edge(int u, int v, int w)
{
    next[current] = point[u];
    to[current] = v;
    point[u] = current;
    weight[current] = w;
    current++;
}

void preDFS(int curt, int fa)
{
    bool flag = true;
    Fat[curt] = fa;
    for (int e = point[curt]; e != -1; e = next[e])
    {
        if (to[e] == fa)
            continue;
        flag = false;
        preDFS(to[e], curt);
        F[curt] += F[to[e]];
        C[curt] += (C[to[e]] - weight[e]);
    }
    if (flag)
        C[curt] = money[curt], F[curt] = 1;
}

struct SNde
{
    int nodeID, peopleLost, cost;
    SNde(int id, int pl, int cst) : nodeID(id), peopleLost(pl), cost(cst) {}
    bool operator<(const SNde &obj) const
    {
        if (peopleLost == 0)
        {
            if (obj.peopleLost == 0)
                if (rmv[nodeID] && rmv[obj.nodeID])
                    return peopleLost > obj.peopleLost;
                else if (rmv[nodeID])
                    return true;
                else if (rmv[obj.nodeID])
                    return false;
            if (rmv[nodeID])
                return true;
            int go = true;
            for (int i = point[nodeID]; i != -1; i = next[i])
                if (!rmv[to[i]] && to[i] != Fat[nodeID])
                {
                    go = false;
                    break;
                }
            if ((rmv[nodeID] = go))
                return true;
            return false;
        }
        return cost < obj.cost;
    }
};

int getDist(int f, int d)
{
    for (int i = point[f]; i != -1; i = next[i])
        if (to[i] == d)
            return weight[i];
    return 0;
}

void DP()
{
    priority_queue<SNde> nodes;
    for (int i = N - M + 1; i <= N; i++)
        nodes.push(SNde(i, 1, -money[i]));
    while (C[1] < 0)
    {
        SNde tp = nodes.top();
        nodes.pop();
        F[1] -= tp.peopleLost;
        C[1] += tp.cost + getDist(Fat[tp.nodeID], tp.nodeID);
        if (!rec[Fat[tp.nodeID]])
            nodes.push(SNde(Fat[tp.nodeID], 0, 0)), rec[Fat[tp.nodeID]] = true;
    }
    cout << F[1];
}

int main()
{
    memset(point, -1, sizeof(point));
    memset(to, -1, sizeof(to));
    memset(next, -1, sizeof(next));
    memset(F, 0, sizeof(F));
    memset(C, 0, sizeof(C));
    memset(rmv, false, sizeof(rmv));
    memset(rec, false, sizeof(rec));
    cin >> N >> M;
    int num, A, C;
    for (int i = 1; i <= N - M; i++)
    {
        cin >> num;
        for (int j = 0; j < num; j++)
            cin >> A >> C, add_edge(i, A, C), add_edge(A, i, C);
    }
    for (int i = N - M + 1; i <= N; i++)
        cin >> money[i];
    preDFS(1, 0);
    DP();
    return 0;
}