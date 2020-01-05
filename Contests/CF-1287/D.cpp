// D.cpp
#include <bits/stdc++.h>

using namespace std;

int read()
{
    int x = 0, f = 1;
    char ch = getchar();
    while (!isdigit(ch))
    {
        if (ch == '-')
            f = -1;
        ch = getchar();
    }
    while (isdigit(ch))
        x = (x << 3) + (x << 1) + (ch - '0'), ch = getchar();
    return x * f;
}

const int MAX_N = 2020;

int n, pi[MAX_N], ci[MAX_N], head[MAX_N], current, root, siz[MAX_N], ai[MAX_N];
deque<int> vec[MAX_N];

struct edge
{
    int to, nxt;
} edges[MAX_N << 1];

void addpath(int src, int dst)
{
    edges[current].to = dst, edges[current].nxt = head[src];
    head[src] = current++;
}

void dfs(int u)
{
    siz[u] = 1;
    for (int i = head[u]; i != -1; i = edges[i].nxt)
        dfs(edges[i].to), siz[u] += siz[edges[i].to];
    if (ci[u] >= siz[u])
        puts("NO"), exit(0);
    for (int i = head[u]; i != -1; i = edges[i].nxt)
        for (int j = 0, siz = vec[edges[i].to].size(); j < siz; j++)
            vec[u].push_back(vec[edges[i].to][j]);
    if (ci[u] == 0)
        vec[u].push_front(u);
    else
        vec[u].insert(vec[u].begin() + ci[u], u);
}

int main()
{
    memset(head, -1, sizeof(head));
    scanf("%d", &n);
    for (int i = 1; i <= n; i++)
    {
        scanf("%d%d", &pi[i], &ci[i]);
        if (pi[i] == 0)
            root = i;
        else
            addpath(pi[i], i);
    }
    dfs(root);
    puts("YES");
    for (int i = 1; i <= n; i++)
        ai[vec[root][i - 1]] = i;
    for (int i = 1; i <= n; i++)
        printf("%d ", ai[i]);
    puts("");
    return 0;
}