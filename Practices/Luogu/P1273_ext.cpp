// P1273.cpp
#include <iostream>
#include <cstring>

using namespace std;

const int maxn = 3010;
int point[maxn];
int to[maxn];
int next[maxn];
int weight[maxn];
int money[maxn];
int F[maxn][maxn];
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

int DFS(int curt, int fa)
{
    if (curt > N - M)
    {
        F[curt][1] = money[curt];
        return 1;
    }
    int ret = 0;
    for (int i = point[curt]; i != -1; i = next[i])
    {
        int jto = to[i];
        if (jto == fa)
            continue;
        int ele = DFS(jto, curt);
        ret += ele;
        for (int i_ = ret; i_ > 0; i_--)
            for (int j = 1; j <= ele; j++)
                if (i_ - j >= 0)
                    F[curt][i_] = max(F[curt][i_], F[curt][i_ - j] + F[jto][j] - weight[i]);
    }
    return ret;
}

int main()
{
    cin >> N >> M;
    fill(point, point + N + 10, -1);
    fill(next, next + N + 10, -1);
    fill(F[0], F[0] + maxn * maxn, -10000000);
    int num, A, C;
    for (int i = 1; i <= N - M; i++)
    {
        cin >> num;
        for (int j = 0; j < num; j++)
            cin >> A >> C, add_edge(i, A, C);
    }
    for (int i = N - M + 1; i <= N; i++)
        cin >> money[i];

    for (int i = 0; i <= N; i++)
        F[i][0] = 0;
    DFS(1, 0);
    for (int i = M; i >= 1; i--)
        if (F[1][i] >= 0)
        {
            cout << i;
            break;
        }
    return 0;
}