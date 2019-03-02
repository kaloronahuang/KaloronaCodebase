// B.cpp
#include <bits/stdc++.h>
using namespace std;
const int MAX_N = 220;
int n, m, wi[MAX_N], tmpx, tmpy, dist[MAX_N][MAX_N], tot;
stack<int> stk;
void dfs(int u)
{
    for (int i = 1; i <= n; i++)
        if (dist[u][i])
        {
            dist[u][i]--, dist[i][u]--;
            dfs(i);
        }
    stk.push(u);
}
int main()
{
    scanf("%d%d", &n, &m);
    for (int i = 1; i <= n; i++)
        scanf("%d", &wi[i]);
    for (int i = 1; i <= m; i++)
        scanf("%d%d", &tmpx, &tmpy), dist[tmpx][tmpy]++, dist[tmpy][tmpx]++;
    dfs(1);
    printf("%d\n", stk.size() - 1);
    while (!stk.empty())
        printf("%d ", stk.top()), stk.pop();
    return 0;
}