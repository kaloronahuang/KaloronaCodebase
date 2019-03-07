// POJ1741.cpp
#include <cstdio>
#include <vector>
#include <algorithm>
#include <iostream>
#include <cstring>
using namespace std;
const int MAX_N = 10100, INF = 0x3f3f3f3f;
int head[MAX_N], current, k, n, tmpx, tmpy, tmpz, root, rootKey, son[MAX_N];
int from[MAX_N], dist[MAX_N], cnt[MAX_N];
bool done[MAX_N];
long long answer = 0;
vector<int> vec;
struct edge
{
    int to, nxt, weight;
} edges[MAX_N << 1];
bool compare(int a, int b) { return dist[a] < dist[b]; }
void addpath(int src, int dst, int weight)
{
    edges[current].to = dst, edges[current].nxt = head[src];
    edges[current].weight = weight, head[src] = current++;
}
// root finding functions;
void dfs1(int u, int fa, int siz)
{
    son[u] = 1;
    int res = 0;
    for (int i = head[u]; i != -1; i = edges[i].nxt)
    {
        if (edges[i].to == fa || done[edges[i].to])
            continue;
        dfs1(edges[i].to, u, siz);
        son[u] += son[edges[i].to];
        res = max(res, son[edges[i].to] - 1);
    }
    res = max(res, siz - son[u]);
    if (res < rootKey)
        root = u, rootKey = res;
}
void findRoot(int src, int siz)
{
    root = src, rootKey = siz;
    dfs1(src, 0, siz);
}
// the calc one;
void dfs(int u, int fa)
{
    vec.push_back(u);
    for (int i = head[u]; i != -1; i = edges[i].nxt)
        if (edges[i].to != fa && !done[edges[i].to])
        {
            cnt[from[u]]++;
            dist[edges[i].to] = dist[u] + edges[i].weight;
            from[edges[i].to] = from[u];
            dfs(edges[i].to, u);
        }
}
void pdq(int curt, int siz)
{
    memset(son, 0, sizeof(son));
    memset(cnt, 0, sizeof(cnt));
    findRoot(curt, siz);
    dist[root] = 0, done[root] = true;
    vec.clear(), vec.push_back(root), from[root] = root;
    cnt[root]++;
    for (int i = head[root]; i != -1; i = edges[i].nxt)
        if (!done[edges[i].to])
        {
            from[edges[i].to] = edges[i].to, cnt[edges[i].to]++;
            dist[edges[i].to] = edges[i].weight;
            dfs(edges[i].to, root);
        }
    sort(vec.begin(), vec.end(), compare);
    cnt[from[vec[0]]]--;
    int l = 0, r = vec.size() - 1;
    while (l < r)
    {
        while (dist[vec[l]] + dist[vec[r]] > k)
            cnt[from[vec[r--]]]--;
        answer += r - l - cnt[from[vec[l]]];
        cnt[from[vec[++l]]]--;
    }
    int pos = root;
    for (int i = head[pos]; i != -1; i = edges[i].nxt)
        if (!done[edges[i].to])
            pdq(edges[i].to, son[edges[i].to]);
}
int main()
{
    while (scanf("%d%d", &n, &k) && n != 0)
    {
        answer = 0;
        memset(head, -1, sizeof(head)), current = 0;
        for (int i = 1; i <= n - 1; i++)
            scanf("%d%d%d", &tmpx, &tmpy, &tmpz), addpath(tmpx, tmpy, tmpz), addpath(tmpy, tmpx, tmpz);
        memset(done, false, sizeof(done));
        pdq(1, n);
        printf("%lld\n", answer);
    }
    return 0;
}