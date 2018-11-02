// P1137.cpp
#include <iostream>
#include <cstring>
#include <queue>

using namespace std;

const int maxn = 100010;
int points[maxn];
int to[2 * maxn];
int next[2 * maxn];
int indeg[maxn];
int res[maxn];
int dp[maxn];
int tot = 0;
int current = 0;
int n, m;

void add_edge(int a, int b)
{
    to[current] = b;
    next[current] = points[a];
    points[a] = current++;
}

void toposort()
{
    queue<int> waiting;
    for (int i = 1; i <= n; i++)
        if (indeg[i] == 0)
            waiting.push(i), res[tot++] = i;
    while (!waiting.empty())
    {
        int curt = waiting.front();
        waiting.pop();
        for (int edge = points[curt]; edge != -1; edge = next[edge])
        {
            indeg[to[edge]]--;
            if (indeg[to[edge]] == 0)
                waiting.push(to[edge]), res[tot++] = to[edge];
        }
    }
}

void DP()
{
    for (int i = 1; i <= n; i++)
        dp[i] = 1;
    for (int i = 0; i < n; i++)
        for (int edge = points[res[i]]; edge != -1; edge = next[edge])
            dp[to[edge]] = max(dp[to[edge]], dp[res[i]] + 1);
}

int main()
{
    memset(points, -1, sizeof(points));
    memset(to, -1, sizeof(to));
    memset(indeg, 0, sizeof(indeg));
    cin >> n >> m;
    int a, b;
    for (int i = 0; i < m; i++)
    {
        cin >> a >> b, add_edge(a, b);
        indeg[b] += 1;
    }
    toposort();
    DP();
    for (int i = 1; i <= n; i++)
        cout << dp[i] << endl;
    return 0;
}