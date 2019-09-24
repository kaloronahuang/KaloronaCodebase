// CH6401.cpp
#include <bits/stdc++.h>
#define pr pair<int, int>
using namespace std;

const int MAX_N = 1e6 + 20;

int head[MAX_N], current;
int n, ai[MAX_N], deg[MAX_N], mem[MAX_N], dp[MAX_N][2], A, B;
bool tag[MAX_N];
vector<pr> links;

struct edge
{
    int to, nxt;
} edges[MAX_N << 1];

void addpath(int src, int dst)
{
    edges[current].to = dst, edges[current].nxt = head[src];
    head[src] = current++;
}

int find(int x) { return x == mem[x] ? x : mem[x] = find(mem[x]); }

void dfs(int u)
{
    int pans = 0x3f3f3f3f;
    dp[u][0] = 0, dp[u][1] = 1;
    for (int i = head[u]; i != -1; i = edges[i].nxt)
    {
        if (u == B && edges[i].to == A)
            continue;
        dfs(edges[i].to);
        dp[u][0] += max(dp[edges[i].to][0], dp[edges[i].to][1]);
        dp[u][1] += max(dp[edges[i].to][0], dp[edges[i].to][1]);
        pans = min(pans, max(dp[edges[i].to][0], dp[edges[i].to][1]) - dp[edges[i].to][0]);
    }
    if (tag[u])
        pans = 0;
    else if (pans == 0x3f3f3f3f)
        pans = 1;
    dp[u][1] -= pans;
}

int main()
{
    memset(head, -1, sizeof(head));
    scanf("%d", &n);
    for (int i = 1; i <= n; i++)
        mem[i] = i;
    for (int i = 1; i <= n; i++)
    {
        scanf("%d", &ai[i]);
        addpath(ai[i], i);
        if (find(ai[i]) != find(i))
            mem[find(ai[i])] = find(i);
        else
            links.push_back(make_pair(i, ai[i]));
    }
    // find a loop side;
    int ans = 0;
    for (int i = 0, siz = links.size(); i < siz; i++)
    {
        pr side = links[i];
        A = side.first, B = side.second;
        int pans = 0;
        dfs(A), pans = max(pans, max(dp[A][0], dp[A][1]));

        tag[B] = true;
        dfs(A), pans = max(pans, dp[A][0]);
        ans += pans;
    }
    printf("%d", ans);
    return 0;
}