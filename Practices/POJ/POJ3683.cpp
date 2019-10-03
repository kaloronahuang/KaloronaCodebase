// POJ3683.cpp
#include <iostream>
#include <cstdio>
#include <cstring>
#include <queue>
#include <cstdlib>

using namespace std;

const int MAX_N = 2020, MAX_E = 3000010;

int n, head[MAX_N], current, dfn[MAX_N], low[MAX_N], ptot, ncnt;
int aff[MAX_N], opp[MAX_N], val[MAX_N], archive_x[MAX_E], archive_y[MAX_E];
int deg[MAX_N], stk[MAX_N], tail, S[MAX_N], T[MAX_N], D[MAX_N];
bool inst[MAX_N];

struct edge
{
    int to, nxt;
} edges[MAX_E << 1];

void addpath(int src, int dst)
{
    edges[current].to = dst, edges[current].nxt = head[src];
    head[src] = current++, archive_x[current] = src, archive_y[current] = dst;
}

void tarjan(int u)
{
    dfn[u] = low[u] = ++ptot, inst[u] = true, stk[++tail] = u;
    for (int i = head[u]; i != -1; i = edges[i].nxt)
        if (dfn[edges[i].to] == 0)
            tarjan(edges[i].to), low[u] = min(low[u], low[edges[i].to]);
        else if (inst[edges[i].to])
            low[u] = min(low[u], dfn[edges[i].to]);
    if (dfn[u] == low[u])
    {
        int color = ++ncnt;
        do
        {
            aff[stk[tail]] = color, inst[stk[tail]] = false;
        } while (stk[tail--] != u);
    }
}

char opt[10];

int getTime()
{
    scanf("%s", opt + 1);
    return (opt[1] - '0') * 600 + (opt[2] - '0') * 60 + (opt[4] - '0') * 10 + (opt[5] - '0');
}

bool intersect(int a, int b, int c, int d)
{
    if (a >= c && a < d || b > c && b <= d || a <= c && b >= d)
        return 1;
    return 0;
}

void toposort()
{
    memset(val, -1, sizeof(val));
    for (int i = 1, tmp = current; i <= tmp; i++)
        if (aff[archive_x[i]] != aff[archive_y[i]])
            addpath(aff[archive_y[i]], aff[archive_x[i]]), deg[aff[archive_x[i]]]++;
    queue<int> q;
    for (int i = n + 1; i <= ncnt; i++)
        if (deg[i] == 0)
            q.push(i);
    while (!q.empty())
    {
        int u = q.front();
        q.pop();
        if (val[u] == -1)
            val[u] = 0, val[opp[u]] = 1;
        for (int i = head[u]; i != -1; i = edges[i].nxt)
            if (--deg[edges[i].to] == 0)
                q.push(edges[i].to);
    }
    for (int i = 1; i <= n; i++)
        if (val[aff[i]] == 0)
            printf("%02d:%02d %02d:%02d\n",
                   S[i] / 60, S[i] % 60,
                   (S[i] + D[i]) / 60, (S[i] + D[i]) % 60);
        else
            printf("%02d:%02d %02d:%02d\n",
                   (T[i] - D[i]) / 60, (T[i] - D[i]) % 60,
                   T[i] / 60, T[i] % 60);
}

int main()
{
    memset(head, -1, sizeof(head));
    scanf("%d", &n), ncnt = n;
    for (int i = 1; i <= n; i++)
    {
        int sh, sm, th, tm;
        scanf("%d:%d %d:%d %d", &sh, &sm, &th, &tm, &D[i]);
        S[i] = sh * 60 + sm;
        T[i] = th * 60 + tm;
    }
    for (int i = 1; i <= n; i++)
        for (int j = i + 1; j <= n; j++)
        {
            if (intersect(S[i], S[i] + D[i], S[j], S[j] + D[j]))
                addpath(i, n + j), addpath(j, n + i);
            if (intersect(S[i], S[i] + D[i], T[j] - D[j], T[j]))
                addpath(i, j), addpath(n + j, n + i);
            if (intersect(T[i] - D[i], T[i], S[j], S[j] + D[j]))
                addpath(n + i, n + j), addpath(j, i);
            if (intersect(T[i] - D[i], T[i], T[j] - D[j], T[j]))
                addpath(n + i, j), addpath(n + j, i);
        }
    for (int i = 1; i <= (n << 1); i++)
        if (!dfn[i])
            tarjan(i);
    for (int i = 1; i <= n; i++)
    {
        if (aff[i] == aff[i + n])
            puts("NO"), exit(0);
        opp[aff[i]] = aff[i + n], opp[aff[i + n]] = aff[i];
    }
    puts("YES");
    toposort();
    return 0;
}