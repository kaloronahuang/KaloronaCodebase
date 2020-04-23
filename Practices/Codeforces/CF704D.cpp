// CF704D.cpp
#include <bits/stdc++.h>

using namespace std;

const int MAX_N = 2e5 + 200, MAX_E = 1e6 + 2000;

typedef long long ll;

const ll INF = 0x3f3f3f3f3f3f3f3f;

int n, m, head[MAX_N], red, blue, xi[MAX_N], yi[MAX_N], gS, gT;
int start_pos, end_pos, current, unit, ptid, dep[MAX_N], cur[MAX_N], idx[MAX_N];
ll di[MAX_N];
bool swapped, fuckflag;
map<int, int> mpx, mpy, cntx, cnty, constx, consty;

struct edge
{
    int to, nxt;
    ll weight;
} edges[MAX_E << 1];

void addpath(int src, int dst, ll weight)
{
    edges[current].to = dst, edges[current].nxt = head[src];
    edges[current].weight = weight, head[src] = current++;
}

void addtube(int src, int dst, ll weight)
{
    addpath(src, dst, weight);
    addpath(dst, src, 0);
}

void addtube(int src, int dst, ll lower, ll upper)
{
    if (lower > upper)
    {
        puts("-1");
        if (fuckflag)
            puts("Fuck void addtube() :: occured for the illegal interval.");
        exit(0);
    }
    addtube(src, dst, upper - lower), di[src] -= lower, di[dst] += lower;
}

bool bfs()
{
    memset(dep, 0, sizeof(dep));
    queue<int> q;
    q.push(start_pos), dep[start_pos] = 1;
    while (!q.empty())
    {
        int u = q.front();
        q.pop();
        for (int i = head[u]; i != -1; i = edges[i].nxt)
            if (dep[edges[i].to] == 0 && edges[i].weight > 0)
                dep[edges[i].to] = dep[u] + 1, q.push(edges[i].to);
    }
    return dep[end_pos] != 0;
}

ll dfs(int u, ll flow)
{
    if (u == end_pos || flow == 0)
        return flow;
    for (int &i = cur[u]; i != -1; i = edges[i].nxt)
        if (edges[i].weight > 0 && dep[edges[i].to] == dep[u] + 1)
            if (ll di = dfs(edges[i].to, min(flow, edges[i].weight)))
            {
                edges[i].weight -= di, edges[i ^ 1].weight += di;
                return di;
            }
    return 0;
}

ll dinic()
{
    ll ret = 0;
    while (bfs())
    {
        memcpy(cur, head, sizeof(cur));
        while (ll di = dfs(start_pos, INF))
            ret += di;
    }
    return ret;
}

int main()
{
    memset(head, -1, sizeof(head));
    scanf("%d%d%d%d", &n, &m, &red, &blue);
    // fuckflag |= (n == 100000 && m == 100000 && red == 341412296 && blue == 266451126);
    if (red < blue)
        swapped = true, swap(red, blue);
    // attempt that red > blue;
    unit = blue - red, gS = n + m + 1, gT = n + m + 2, ptid = n;
    for (int i = 1; i <= n; i++)
        scanf("%d%d", &xi[i], &yi[i]), cntx[xi[i]]++, cnty[yi[i]]++;
    for (int i = 1, opt, x, d; i <= m; i++)
    {
        scanf("%d%d%d", &opt, &x, &d);
        if (opt == 1)
        {
            if (!mpx.count(x))
                mpx[x] = ++ptid;
            if (!constx.count(x))
                constx[x] = d;
            else
                constx[x] = min(constx[x], d);
        }
        else
        {
            if (!mpy.count(x))
                mpy[x] = ++ptid;
            if (!consty.count(x))
                consty[x] = d;
            else
                consty[x] = min(consty[x], d);
        }
    }
    for (auto curt : constx)
        if (cntx[curt.first] <= curt.second)
            addtube(gS, mpx[curt.first], 0, INF);
        else
            addtube(gS, mpx[curt.first], (cntx[curt.first] - curt.second + 1) >> 1, (cntx[curt.first] + curt.second) >> 1);
    for (auto curt : consty)
        if (cnty[curt.first] <= curt.second)
            addtube(mpy[curt.first], gT, 0, INF);
        else
            addtube(mpy[curt.first], gT, (cnty[curt.first] - curt.second + 1) >> 1, (cnty[curt.first] + curt.second) >> 1);
    for (int i = 1; i <= n; i++)
    {
        idx[i] = current;
        if (mpx.count(xi[i]))
            addtube(mpx[xi[i]], i, 1);
        else
            addtube(gS, i, 1);
        if (mpy.count(yi[i]))
            addtube(i, mpy[yi[i]], 1);
        else
            addtube(i, gT, 1);
    }
    start_pos = n + m + 3, end_pos = start_pos + 1;
    ll sum = 0;
    for (int i = 1; i <= n + m + 2; i++)
        if (di[i] > 0)
            addtube(start_pos, i, di[i]), sum += di[i];
        else if (di[i] < 0)
            addtube(i, end_pos, -di[i]);
    addtube(gT, gS, INF);
    ll ret = dinic();
    bool flag = sum == ret;
    if (flag == false)
    {
        puts("-1");
        if (fuckflag)
            puts("Fuck int main() :: if (flag == false), occured at the illegal network.");
        exit(0);
    }
    ret = edges[current - 1].weight;
    edges[current - 1].weight = edges[current - 2].weight = 0;
    start_pos = gS, end_pos = gT, ret += dinic();
    ll ans = 1LL * ret * unit + 1LL * n * red;
    printf("%lld\n", ans);
    for (int i = 1; i <= n; i++)
        if (edges[idx[i]].weight == 0)
            putchar(swapped ? 'r' : 'b');
        else
            putchar(swapped ? 'b' : 'r');
    return 0;
}