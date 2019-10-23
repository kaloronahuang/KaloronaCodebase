// LOJ2155.cpp
#include <bits/stdc++.h>

using namespace std;

const int MAX_N = 1e6 + 200;

struct edge
{
    int to, nxt;
} edges[MAX_N * 50];

int head[MAX_N], n, current, aff[MAX_N], dfn[MAX_N], low[MAX_N], ptot;
int stk[MAX_N], tail, ncnt, ans[MAX_N], cnt[MAX_N], conflict[MAX_N];
bool mat[5050][5050], inst[MAX_N];

void addpath(int src, int dst)
{
    edges[current].to = dst, edges[current].nxt = head[src];
    head[src] = current++;
}

void tarjan(int u)
{
    dfn[u] = low[u] = ++ptot, inst[u] = true, stk[++tail] = u;
    for (int i = head[u]; i != -1; i = edges[i].nxt)
        if (dfn[edges[i].to] == 0)
            tarjan(edges[i].to), low[u] = min(low[edges[i].to], low[u]);
        else if (inst[edges[i].to])
            low[u] = min(low[u], dfn[edges[i].to]);
    if (low[u] == dfn[u])
    {
        ncnt++;
        do
        {
            aff[stk[tail]] = ncnt, inst[stk[tail]] = false;
        } while (stk[tail--] != u);
    }
}

int pt1(int p) { return p << 1; }

int pt2(int p) { return (p << 1) | 1; }

int main()
{
    memset(head, -1, sizeof(head));
    scanf("%d", &n);
    for (int i = 1, v, tmp; i <= n; i++)
    {
        scanf("%d", &tmp);
        while (tmp--)
            scanf("%d", &v), mat[i][v] = mat[v][i] = true;
    }
    for (int i = 1; i <= n; i++)
        for (int j = 1; j < i; j++)
            if (mat[i][j])
                addpath(pt2(i), pt1(j)), addpath(pt2(j), pt1(i));
            else
                addpath(pt1(i), pt2(j)), addpath(pt1(j), pt2(i));
    for (int i = 2; i <= (n << 1); i++)
        if (dfn[i] == 0)
            tarjan(i);
    for (int i = 1; i <= n; i++)
        if (aff[pt1(i)] == aff[pt2(i)])
            printf("0"), exit(0);
    int cnt1 = 0, cnt2 = 0, res = 0;
    for (int i = 1; i <= n; i++)
    {
        ans[i] = (aff[pt1(i)] > aff[pt2(i)]);
        if (ans[i])
            cnt2++;
        else
            cnt1++;
    }
    res = cnt1 && cnt2;
    int swap_1 = 0, swap_2 = 0;
    for (int i = 1; i <= n; i++)
        if (ans[i])
        {
            for (int j = 1; j <= n; j++)
                if (i != j && ans[j] == 0 && mat[i][j] == false)
                    cnt[i]++, conflict[i] = j;
        }
        else
        {
            for (int j = 1; j <= n; j++)
                if (i != j && ans[j] && mat[i][j])
                    cnt[i]++, conflict[i] = j;
        }
    for (int i = 1; i <= n; i++)
        if (ans[i] == 0)
        {
            if (cnt[i] == 0 && cnt1 > 1)
                res++;
            if (cnt[i] == 0)
                swap_1++;
            // only conflict;
            if (cnt[i] == 1 && ((conflict[conflict[i]] == i && cnt[conflict[i]] == 1 && i < conflict[i]) || cnt[conflict[i]] == 0))
                res++;
        }
        else
        {
            if (cnt[i] == 0 && cnt2 > 1)
                res++;
            if (cnt[i] == 0)
                swap_2++;
            // only conflict;
            if (cnt[i] == 1 && ((conflict[conflict[i]] == i && cnt[conflict[i]] == 1 && i < conflict[i]) || cnt[conflict[i]] == 0))
                res++;
        }
    res += swap_1 * swap_2;
    printf("%d", res);
    return 0;
}