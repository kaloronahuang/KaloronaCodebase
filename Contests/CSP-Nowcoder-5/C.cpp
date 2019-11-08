// C.cpp
#include <bits/stdc++.h>
typedef long long ll;

using namespace std;

const int MAX_N = 3e5 + 200;

int head[MAX_N], current, n, m, lft[MAX_N], rig[MAX_N], ptot, fa[MAX_N], upweight[MAX_N];
int deg[MAX_N], seq[MAX_N], pcur;
ll suffix[MAX_N];

struct edge
{
    int to, nxt, weight;
} edges[MAX_N << 1];

void addpath(int src, int dst, int weight)
{
    edges[current].to = dst, edges[current].nxt = head[src];
    edges[current].weight = weight, head[src] = current++;
}

void dfs(int u, int fat)
{
    lft[u] = ++ptot, fa[u] = fat;
    for (int i = head[u]; i != -1; i = edges[i].nxt)
        if (edges[i].to != fat)
            upweight[edges[i].to] = edges[i].weight, dfs(edges[i].to, u);
    rig[u] = ptot;
}

int tmp[MAX_N], cur;

void subtask1()
{
    dfs(1, 0);
    while (m--)
    {
        int st, ed;
        scanf("%d%d", &st, &ed);
        if (lft[st] <= lft[ed] && lft[ed] <= rig[st])
        {
            long long ans = cur = 0, ted = ed;
            while (ed != st)
                tmp[++cur] = fa[ed], ed = fa[ed];
            reverse(tmp + 1, tmp + 1 + cur), tmp[cur + 1] = ted, tmp[cur + 2] = 0;
            for (int i = 2, cpt = tmp[1]; i <= cur + 1; i++)
            {
                ans += 1LL * upweight[tmp[i]] * cpt;
                if (cpt > tmp[i])
                    cpt = tmp[i];
            }
            printf("%lld\n", ans);
        }
        else
            puts("-1");
    }
}

void dfs2(int u, int fat)
{
    seq[++pcur] = u;
    for (int i = head[u]; i != -1; i = edges[i].nxt)
        if (edges[i].to != fat)
            dfs2(edges[i].to, u);
}

void subtask2()
{
    dfs2(1, 0), dfs(1, 0);
    // you got the sequence;
    for (int i = n, mx_pt; i >= 1; i--)

}

int main()
{
    memset(head, -1, sizeof(head));
    scanf("%d%d", &n, &m);
    int cnt1 = 0, cnt2 = 0, cntn = 0;
    for (int i = 1, u, v, w; i < n; i++)
    {
        scanf("%d%d%d", &u, &v, &w), addpath(u, v, w), addpath(v, u, w), deg[u]++, deg[v]++;
        if (deg[u] == 1)
            cnt1++;
        else if (deg[u] == 2)
            cnt1--, cnt2++;
        else
            cnt2--, cntn++;

        if (deg[v] == 1)
            cnt1++;
        else if (deg[v] == 2)
            cnt1--, cnt2++;
        else
            cnt2--, cntn++;
    }
    if (cnt1 == 2 && cnt2 == n - 2)
        subtask2();
    else
        subtask1();
    return 0;
}