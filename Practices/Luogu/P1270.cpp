// P1270.cpp
#include <iostream>
#include <vector>

using namespace std;

const int maxn = 200;
const int INF = (0x7fffffff) / 3;
struct edge
{
    int to, weight;
    edge() {}
    edge(int t, int w) : to(t), weight(w) {}
};
vector<edge> G[200];
int paintings[200];
int n = 1;
int tim;
int F[maxn][maxn];

void print()
{
    for (int i = 1; i <= n; i++)
    {
        int siz2 = G[i].size();
        for (int j = 0; j < siz2; j++)
            cout << i << " " << G[i][j].to << " " << G[i][j].weight << endl;
    }
}

void read(int u)
{
    int w, num;
    cin >> w >> num;
    if (num == 0)
    {
        G[u].push_back(edge(++n, w));
        int v = n;
        read(v);
        read(v);
        return;
    }
    G[u].push_back(edge(++n, w));
    paintings[n] = num;
}

void dfs(int u)
{
    F[u][0] = 0;
    if (G[u].empty())
    {
        // there are no subtrees;
        for (int i = 0; i <= paintings[u]; i++)
            F[u][i] = i * 5;
        return;
    }
    if (G[u].size() == 1)
    {
        dfs(G[u][0].to);
        F[u][0] = 0;
        for (int i = 1; i < maxn; i++)
            F[u][i] = 2 * G[u][0].weight + F[G[u][0].to][i];
        return;
    }
    dfs(G[u][0].to), dfs(G[u][1].to);
    for (int i = 0; i < maxn; i++)
        for (int j = 0; j < maxn; j++)
        {
            int wi = (i == 0) ? 0 : G[u][0].weight;
            int wj = (j == 0) ? 0 : G[u][1].weight;
            F[u][i + j] = min(F[u][i + j], 2 * wi + 2 * wj + F[G[u][0].to][i] + F[G[u][1].to][j]);
        }
    return;
}

int main()
{
    cin >> tim;
    fill(F[0], F[0] + maxn * maxn, INF);
    read(1);
    dfs(1);
    int ans = 0;
    for (int i = 0; i < maxn; i++)
        if (F[1][i] < tim)
            ans = i;
    cout << ans;
    return 0;
}