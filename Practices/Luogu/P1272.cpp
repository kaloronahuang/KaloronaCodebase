#include <iostream>

using namespace std;
const int maxn = 400;
const int INF = 1e9;
int F[maxn][maxn];
int deg[maxn];

int N, P;
// graph part;
struct edge
{
    int to, next;
    edge() {}
    edge(int t, int n) : to(t), next(n) {}
} edges[maxn];
int head[maxn];
int current = 0;

void add_edge(int u, int v)
{
    edges[current] = edge(v, head[u]);
    head[u] = current++;
}

void DFS(int u, int fa)
{
    F[u][1] = deg[u];
    for (int i = head[u]; i != -1; i = edges[i].next)
    {
        int dst = edges[i].to;
        if (dst == fa)
            continue;
        DFS(dst, u);
        for (int cap = P; cap >= 1; cap--)
            for (int j = 1; j < cap; j++)
                F[u][cap] = min(F[u][cap], F[u][cap - j] + F[dst][j] - 2);
    }
}

int main()
{
    cin >> N >> P;
    fill(head, head + maxn, -1);
    fill(F[0], F[0] + maxn * maxn, INF / 2);
    fill(deg, deg + maxn, 0);
    for (int i = 0; i < N - 1; i++)
    {
        int a, b;
        cin >> a >> b;
        add_edge(b, a), add_edge(a, b);
        deg[a]++, deg[b]++;
    }
    DFS(1, 0);
    long long ans = INF;
    for (int i = 1; i <= N; i++)
        ans = min(ans, (long long)F[i][P]);
    cout << ans;
    return 0;
}