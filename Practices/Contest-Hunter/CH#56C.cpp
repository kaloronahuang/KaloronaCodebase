// CH#56C.cpp
#include <bits/stdc++.h>
#define ll long long
using namespace std;

const int MAX_N = 1e5 + 200;

int head[MAX_N], current, dfn[MAX_N], antidfn[MAX_N], dep[MAX_N], fa[20][MAX_N], n, m, ptot;
ll dist[20][MAX_N];
char opt[20];
set<int> st;

struct edge
{
    int to, nxt;
    ll weight;
} edges[MAX_N << 1];

void addpath(int src, int dst, ll weight)
{
    edges[current].to = dst, edges[current].nxt = head[src];
    edges[current].weight = weight, head[src] = current++;
}

ll getLCA(int x, int y)
{
    ll ans = 0;
    if (dep[x] < dep[y])
        swap(x, y);
    for (int i = 19; i >= 0; i--)
        if (dep[fa[i][x]] >= dep[y])
            ans += dist[i][x], x = fa[i][x];
    if (x == y)
        return ans;
    for (int i = 19; i >= 0; i--)
        if (fa[i][x] != fa[i][y])
            ans += dist[i][x] + dist[i][y], x = fa[i][x], y = fa[i][y];
    return ans + dist[0][x] + dist[0][y];
}

void dfs(int u, int fat)
{
    fa[0][u] = fat, dep[u] = dep[fat] + 1, dfn[u] = ++ptot, antidfn[ptot] = u;
    for (int i = head[u]; i != -1; i = edges[i].nxt)
        if (edges[i].to != fat)
            dist[0][edges[i].to] = edges[i].weight, dfs(edges[i].to, u);
}

inline set<int>::iterator goLeft(set<int>::iterator x) { return (x == st.begin()) ? (--st.end()) : (--x); }
inline set<int>::iterator goRight(set<int>::iterator x) { return (x == --st.end()) ? (st.begin()) : (++x); }

int main()
{
    memset(head, -1, sizeof(head));
    scanf("%d", &n);
    ll tmpw;
    for (int i = 1, u, v; i <= n - 1; i++)
        scanf("%d%d%lld", &u, &v, &tmpw), addpath(u, v, tmpw), addpath(v, u, tmpw);
    dfs(1, 0);
    for (int i = 1; i < 20; i++)
        for (int j = 1; j <= n; j++)
            fa[i][j] = fa[i - 1][fa[i - 1][j]], dist[i][j] = dist[i - 1][j] + dist[i - 1][fa[i - 1][j]];
    scanf("%d", &m);
    ll current_ans = 0;
    while (m--)
    {
        int x;
        scanf("%s", opt + 1);
        if (opt[1] == '?')
            printf("%lld\n", current_ans >> 1);
        else if (opt[1] == '+')
        {
            scanf("%d", &x);
            if (!st.empty())
            {
                set<int>::iterator it = st.lower_bound(dfn[x]);
                if (it == st.end())
                    it = st.begin();
                int y = *goLeft(it);
                current_ans += getLCA(x, antidfn[y]) + getLCA(x, antidfn[*it]) - getLCA(antidfn[y], antidfn[*it]);
            }
            st.insert(dfn[x]);
        }
        else
        {
            scanf("%d", &x);
            set<int>::iterator it = st.find(dfn[x]);
            int y = *(goLeft(it)), z = *(goRight(it));
            current_ans -= getLCA(x, antidfn[y]) + getLCA(x, antidfn[z]) - getLCA(antidfn[y], antidfn[z]);
            st.erase(dfn[x]);
        }
    }
    return 0;
}