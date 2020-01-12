// B.cpp
#include <bits/stdc++.h>

using namespace std;

const int MAX_N = 1e6 + 200;

int head[MAX_N], current, n, siz[MAX_N], root, answer[MAX_N], acc, limit_id;
vector<int> vec;

struct edge
{
    int to, nxt;
} edges[MAX_N << 1];

void fileIO()
{
    freopen("flea.in", "r", stdin);
    freopen("flea.out", "w", stdout);
}

bool compare(int a, int b) { return siz[a] > siz[b]; }

void addpath(int src, int dst)
{
    edges[current].to = dst, edges[current].nxt = head[src];
    head[src] = current++;
}

void dfs(int u, int fa)
{
    int max_son = 0;
    siz[u] = 1;
    for (int i = head[u]; i != -1; i = edges[i].nxt)
        if (edges[i].to != fa)
            dfs(edges[i].to, u), siz[u] += siz[edges[i].to], max_son = max(max_son, siz[edges[i].to]);
    max_son = max(max_son, n - siz[u]);
    if (max_son <= (n >> 1))
        root = u;
}

void getAns(int u, int fa)
{
    answer[u] = limit_id - (siz[u] + acc >= (n >> 1)) + 1;
    for (int i = head[u]; i != -1; i = edges[i].nxt)
        if (edges[i].to != fa)
            getAns(edges[i].to, u);
}

int main()
{
    // fileIO();
    memset(head, -1, sizeof(head));
    scanf("%d", &n);
    for (int i = 1, u, v; i <= n - 1; i++)
        scanf("%d%d", &u, &v), addpath(u, v), addpath(v, u);
    dfs(1, 0), dfs(root, 0);
    for (int i = head[root]; i != -1; i = edges[i].nxt)
        vec.push_back(edges[i].to);
    sort(vec.begin(), vec.end(), compare);
    limit_id = -1;
    for (int i = 0, siz_ = vec.size(); i < siz_; i++)
    {
        acc += siz[vec[i]];
        if (acc >= (n >> 1))
        {
            limit_id = i;
            break;
        }
    }
    for (int i = 0; i <= limit_id; i++)
        acc -= siz[vec[i]], getAns(vec[i], root), acc += siz[vec[i]];
    if (limit_id != -1)
        acc -= siz[vec[limit_id]];
    for (int i = limit_id + 1, siz_ = vec.size(); i < siz_; i++)
        getAns(vec[i], root);
    for (int i = 1; i <= n; i++)
        printf("%d\n", answer[i]);
    return 0;
}