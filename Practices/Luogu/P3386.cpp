// P3386.cpp
#include <bits/stdc++.h>
using namespace std;
const int MAX_N = 1200;
int n, m, e, current, head[MAX_N], match[MAX_N], dfn[MAX_N];
int tmpx, tmpy;
inline int read()
{
    int s = 0, w = 1;
    char ch = getchar();
    while (ch < '0' || ch > '9')
    {
        if (ch == '-')
            w = -1;
        ch = getchar();
    }
    while (ch >= '0' && ch <= '9')
        s = s * 10 + ch - '0', ch = getchar();
    return s * w;
}
struct edge
{
    int to, nxt;
} edges[MAX_N * MAX_N];
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
    n = read(), m = read(), e = read();
    while (e--)
    {
        tmpx = read(), tmpy = read();
        if (tmpx <= n && tmpy <= m)
            addpath(tmpx, tmpy);
    }
    int ans = 0;
    for (int i = 1; i <= n; i++)
        if (dfs(i, i))
            ans++;
    printf("%d", ans);
    return 0;
}