// LOJ2162.cpp
#include <bits/stdc++.h>

using namespace std;

const int MAX_N = 1e5 + 200, MAX_E = 1e6 + 200;

int n, m, head[MAX_N], current, deg[MAX_N], mem[MAX_N], cur[MAX_N], dir[MAX_E], tot;
bool vis[MAX_E], inst[MAX_N];
stack<int> st;
vector<int> ansBox[MAX_N];

struct edge
{
    int to, nxt;
} edges[MAX_E << 1];

void addpath(int src, int dst)
{
    edges[current].to = dst, edges[current].nxt = head[src];
    head[src] = current++;
}

int find(int x) { return mem[x] == x ? x : mem[x] = find(mem[x]); }

void dfs(int u)
{
    for (int &i = cur[u]; i != -1; i = edges[i].nxt)
        if (!vis[i >> 1])
        {
            int curt = i;
            vis[i >> 1] = true;
            dfs(edges[i].to), dir[curt >> 1] = curt & 1;
        }
}

void DFS(int u)
{
    st.push(u), inst[u] = true;
    for (int &i = head[u]; i != -1; i = edges[i].nxt)
        if (!inst[u])
            return;
        else if ((i & 1) == dir[i >> 1])
        {
            if (inst[edges[i].to])
            {
                ansBox[++tot].push_back(edges[i].to);
                int p = 0;
                do
                {
                    p = st.top(), st.pop(), ansBox[tot].push_back(p), inst[p] = false;
                } while (p != edges[i].to);
                st.push(edges[i].to), inst[edges[i].to] = true;
            }
            else
                DFS(edges[i].to);
        }
}

int main()
{
    memset(head, -1, sizeof(head));
    scanf("%d%d", &n, &m);
    for (int i = 1; i <= n; i++)
        mem[i] = i;
    for (int i = 1, u, v, s, t; i <= m; i++)
    {
        scanf("%d%d%d%d", &u, &v, &s, &t);
        if (s != t)
        {
            addpath(u, v), addpath(v, u), deg[u]++, deg[v]++;
            if (find(u) != find(v))
                mem[find(u)] = find(v);
        }
    }
    for (int i = 1; i <= n; i++)
        if (deg[i] & 1)
            puts("NIE"), exit(0);
    memcpy(cur, head, sizeof(head));
    for (int i = 1; i <= n; i++)
        if (find(i) == i)
            dfs(i);
    for (int i = 1; i <= n; i++)
        DFS(i);
    printf("%d\n", tot);
    for (int i = 1; i <= tot; i++)
    {
        printf("%lld ", 1LL * ansBox[i].size() - 1);
        for (int v : ansBox[i])
            printf("%d ", v);
        puts("");
    }
    return 0;
}