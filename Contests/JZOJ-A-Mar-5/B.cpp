// B.cpp
#include <bits/stdc++.h>
#define ll long long
using namespace std;
const int MAX_N = 502000;
int head[MAX_N << 1], current, n, m, dfn[MAX_N], low[MAX_N], aff[MAX_N];
int tot, stk[MAX_N], cur, afftot, indeg[MAX_N << 1], tmpx, tmpy, s;
ll cnt[MAX_N << 1], dp[MAX_N << 1], answer;
bool inst[MAX_N], mark[MAX_N];
struct edge
{
    int to, nxt;
} edges[MAX_N << 1];
void addpath(int src, int dst)
{
    edges[current].to = dst;
    edges[current].nxt = head[src], head[src] = current++;
}
void tarjan(int u)
{
    dfn[u] = low[u] = ++tot, stk[++cur] = u, inst[u] = true;
    for (int i = head[u]; i != -1; i = edges[i].nxt)
        if (dfn[edges[i].to] == 0)
            tarjan(edges[i].to), low[u] = min(low[u], low[edges[i].to]);
        else if (inst[edges[i].to])
            low[u] = min(low[u], dfn[edges[i].to]);
    if (low[u] == dfn[u])
    {
        int j, nd = ++afftot;
        do
        {
            j = stk[cur], inst[j] = false;
            aff[j] = nd;
        } while (stk[cur--] != u);
    }
}
void toposort()
{
    queue<int> q;
    q.push(aff[s]), dp[aff[s]] = cnt[aff[s]];
    while (!q.empty())
    {
        int u = q.front();
        q.pop();
        for (int i = head[u]; i != -1; i = edges[i].nxt)
        {
            dp[edges[i].to] = max(dp[edges[i].to], dp[u] + cnt[edges[i].to]);
            if ((--indeg[edges[i].to]) == 0)
                q.push(edges[i].to);
        }
    }
}
int main()
{
    memset(head, -1, sizeof(head));
    scanf("%d%d", &n, &m);
    for (int i = 1; i <= m; i++)
        scanf("%d%d", &tmpx, &tmpy), addpath(tmpx, tmpy);
    afftot = n;
    for (int i = 1; i <= n; i++)
        if (aff[i] == 0)
            tarjan(i);
    for (int i = 1; i <= n; i++)
        scanf("%lld", &cnt[i]);
    for (int u = 1; u <= n; u++)
    {
        cnt[aff[u]] += cnt[u];
        for (int i = head[u]; i != -1; i = edges[i].nxt)
            if (aff[u] != aff[edges[i].to])
                addpath(aff[u], aff[edges[i].to]), indeg[aff[edges[i].to]]++;
    }
    scanf("%d%d", &s, &tmpx);
    for (int i = 1; i <= tmpx; i++)
        scanf("%d", &tmpy), mark[aff[tmpy]] = true;
    toposort();
    for (int i = n + 1; i <= afftot; i++)
        if (mark[i])
            answer = max(answer, dp[i]);
    printf("%lld", answer);
    return 0;
}