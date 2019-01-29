// POJ3041.cpp
#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
const int MAX_N = 510;
int n, k, head[MAX_N], current, tmpx, tmpy, dfn[MAX_N], match[MAX_N], ans;
struct edge
{
    int to, nxt;
} edges[21000];
void addpath(int src, int dst)
{
    edges[current].to = dst, edges[current].nxt = head[src];
    head[src] = current++;
}
bool dfs(int u, int tm)
{
    for (int i = head[u]; i != -1; i = edges[i].nxt)
    {
        int to = edges[i].to;
        if (dfn[to] != tm)
        {
            dfn[to] = tm;
            if ((!match[to]) || dfs(match[to], tm))
            {
                match[to] = u;
                return true;
            }
        }
    }
    return false;
}
int main()
{
    memset(head, -1, sizeof(head));
    scanf("%d%d", &n, &k);
    for (int i = 1; i <= k; i++)
        scanf("%d%d", &tmpx, &tmpy), addpath(tmpx, tmpy);
    for (int i = 1; i <= n; i++)
        if (dfs(i, i))
            ans++;
    printf("%d", ans);
    return 0;
}