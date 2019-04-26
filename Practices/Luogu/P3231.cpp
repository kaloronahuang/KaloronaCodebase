// P3231.cpp
#include <bits/stdc++.h>
using namespace std;

const int MAX_N = 5050, INF = 0x3f3f3f3f;
int head[MAX_N], current, matching[MAX_N], times, vis[MAX_N], tot;
int pos, T, point[MAX_N][4], di[4], answer, tmpx, tmpy, tmpz, ptot;
bool decision[MAX_N];
struct edge
{
    int to, nxt, weight;
} edges[MAX_N << 1];

void addpath(int src, int dst, int weight)
{
    edges[current].to = dst, edges[current].nxt = head[src];
    edges[current].weight = weight, head[src] = current++;
}

bool dfs(int u)
{
    for (int i = head[u]; i != -1; i = edges[i].nxt)
        if (!decision[edges[i].weight] && vis[edges[i].to] < times)
        {
            vis[edges[i].to] = times;
            if (matching[edges[i].to] == 0 || dfs(matching[edges[i].to]))
            {
                matching[edges[i].to] = u;
                return true;
            }
        }
    return false;
}

int solve(int acc)
{
    int ans = 0;
    for (int i = 1; i <= tot; i++)
        matching[i] = 0;
    for (int i = 1; i <= tot; i++)
    {
        times++;
        if (dfs(i))
            ans++;
        if (acc + ans >= answer)
            return acc + ans;
    }
    return acc + ans;
}

void DFS(int dep, int acc)
{
    if (dep > di[pos])
        return (void)(answer = min(answer, solve(acc)));
    decision[dep] = true, DFS(dep + 1, acc + 1);
    decision[dep] = false, DFS(dep + 1, acc);
}

int main()
{
    scanf("%d", &T);
    while (T--)
    {
        memset(head, -1, sizeof(head)), current = 0;

        answer = INF, tot = 0, pos = 1, ptot = 0;
        scanf("%d%d%d", &di[1], &di[2], &di[3]);
        if (di[2] < di[pos])
            pos = 2;
        if (di[3] < di[pos])
            pos = 3;
        for (int i = 1; i <= 3; i++)
            if (i != pos)
                tot = max(tot, di[i]);

        for (int i = 1; i <= di[1]; i++)
            for (int j = 1; j <= di[2]; j++)
                for (int k = 1; k <= di[3]; k++)
                {
                    scanf("%d", &tmpx);
                    if (tmpx != 0)
                        point[++ptot][1] = i, point[ptot][2] = j, point[ptot][3] = k;
                }

        for (int i = 1; i <= ptot; i++)
            if (pos == 1)
                addpath(point[i][2], point[i][3], point[i][1]);
            else if (pos == 2)
                addpath(point[i][1], point[i][3], point[i][2]);
            else
                addpath(point[i][1], point[i][2], point[i][3]);
        printf("%d\n", (DFS(1, 0), answer));
    }
    return 0;
}