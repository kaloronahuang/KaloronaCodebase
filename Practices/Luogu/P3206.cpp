// P3206.cpp
#include <bits/stdc++.h>
#define ll long long

using namespace std;

const int MAX_N = 21000, MAX_E = 5e4 + 200;

int n, m, q, mem[MAX_N], weights[MAX_E], rpos[MAX_E];
ll ans[MAX_E];

struct edge
{
    int from, to, weight, id;
    bool operator<(const edge &rhs) const { return weight < rhs.weight; }
} edges[20][MAX_E], tmp[MAX_E], stk[MAX_E];

struct query
{
    int id, val;
} queries[MAX_E];

inline char gc()
{
    static const int IN_LEN = 1000000;
    static char buf[IN_LEN], *s, *t;
    return (s == t ? t = (s = buf) + fread(buf, 1, IN_LEN, stdin), (s == t ? -1 : *s++) : *s++);
}

int read()
{
    int x = 0, f = 1;
    char ch = gc();
    while (!isdigit(ch))
    {
        if (ch == '-')
            f = -1;
        ch = gc();
    }
    while (isdigit(ch))
        x = (x << 3) + (x << 1) + (ch - '0'), ch = gc();
    return x * f;
}

int find(int x) { return mem[x] == x ? x : mem[x] = find(mem[x]); }

void unite(int x, int y)
{
    if (find(x) != find(y))
        mem[find(x)] = find(y);
}

void reset(int tot, edge *arr)
{
    for (int i = 1; i <= tot; i++)
        mem[arr[i].from] = arr[i].from, mem[arr[i].to] = arr[i].to;
}

ll contraction(int &tot)
{
    int top = 0;
    sort(tmp + 1, tmp + 1 + tot);
    for (int i = 1; i <= tot; i++)
        if (find(tmp[i].from) != find(tmp[i].to))
            unite(tmp[i].from, tmp[i].to), stk[++top] = tmp[i];
    reset(top, stk);
    ll val = 0;
    for (int i = 1; i <= top; i++)
        if (stk[i].weight != INT_MIN && find(stk[i].from) != find(stk[i].to))
            unite(stk[i].from, stk[i].to), val += stk[i].weight;
    top = 0;
    for (int i = 1; i <= tot; i++)
        if (find(tmp[i].from) != find(tmp[i].to))
        {
            stk[++top] = tmp[i];
            stk[top].from = find(tmp[i].from), stk[top].to = find(tmp[i].to);
            rpos[tmp[i].id] = top;
        }
    reset(tot, tmp), tot = top;
    for (int i = 1; i <= top; i++)
        tmp[i] = stk[i];
    return val;
}

void reduction(int &tot)
{
    int top = 0;
    sort(tmp + 1, tmp + 1 + tot);
    for (int i = 1; i <= tot; i++)
        if (find(tmp[i].from) != find(tmp[i].to))
        {
            unite(tmp[i].from, tmp[i].to);
            stk[++top] = tmp[i], rpos[tmp[i].id] = top;
        }
        else if (tmp[i].weight == INT_MAX)
            stk[++top] = tmp[i], rpos[tmp[i].id] = top;
    reset(tot, tmp), tot = top;
    for (int i = 1; i <= tot; i++)
        tmp[i] = stk[i];
}

void solve(int l, int r, int dep, int tot, ll val)
{
    if (l == r)
        weights[queries[l].id] = queries[l].val;
    for (int i = 1; i <= tot; i++)
    {
        edges[dep][i].weight = weights[edges[dep][i].id];
        tmp[i] = edges[dep][i], rpos[edges[dep][i].id] = i;
    }
    if (l == r)
    {
        ans[l] = val;
        sort(tmp + 1, tmp + 1 + tot);
        for (int i = 1; i <= tot; i++)
            if (find(tmp[i].from) != find(tmp[i].to))
            {
                unite(tmp[i].from, tmp[i].to);
                ans[l] += tmp[i].weight;
            }
        reset(tot, tmp);
        return;
    }
    for (int i = l; i <= r; i++)
        tmp[rpos[queries[i].id]].weight = INT_MIN;
    val += contraction(tot);
    for (int i = l; i <= r; i++)
        tmp[rpos[queries[i].id]].weight = INT_MAX;
    reduction(tot);
    for (int i = 1; i <= tot; i++)
        edges[dep + 1][i] = tmp[i];
    int mid = (l + r) >> 1;
    solve(l, mid, dep + 1, tot, val);
    solve(mid + 1, r, dep + 1, tot, val);
}

int main()
{
    scanf("%d%d%d", &n, &m, &q);
    for (int i = 1; i <= m; i++)
    {
        scanf("%d%d%d", &edges[0][i].from, &edges[0][i].to, &edges[0][i].weight);
        edges[0][i].id = i, weights[i] = edges[0][i].weight;
    }
    for (int i = 1; i <= q; i++)
        scanf("%d%d", &queries[i].id, &queries[i].val);
    for (int i = 1; i <= n; i++)
        mem[i] = i;
    solve(1, q, 0, m, 0);
    for (int i = 1; i <= q; i++)
        printf("%lld\n", ans[i]);
    return 0;
}