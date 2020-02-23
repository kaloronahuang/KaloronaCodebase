// BZ3677.cpp
#include <bits/stdc++.h>

using namespace std;

const int MAX_N = 501000;
const long long INF = 0x3f3f3f3f3f3f3f3f;

typedef long long ll;

int n, head[MAX_N], current;
ll dp[MAX_N][2], f[MAX_N], upweight[MAX_N];
vector<pair<ll, ll> /**/> g[MAX_N][2];

struct edge
{
    int to, nxt, weight;
} edges[MAX_N << 1];

void addpath(int src, int dst, int weight)
{
    edges[current].to = dst, edges[current].nxt = head[src];
    edges[current].weight = weight, head[src] = current++;
}

void calc(int u, int fa)
{
    dp[u][0] = 0, dp[u][1] = -INF;
    ll max1 = -INF, max2 = -INF;
    for (int i = head[u]; i != -1; i = edges[i].nxt)
        if (edges[i].to != fa)
        {
            upweight[edges[i].to] = edges[i].weight;
            calc(edges[i].to, u), dp[u][0] += max(dp[edges[i].to][0], edges[i].weight + dp[edges[i].to][1]);
            ll tmp = dp[edges[i].to][0] + edges[i].weight - max(dp[edges[i].to][0], dp[edges[i].to][1] + upweight[edges[i].to]);
            if (tmp > max1)
                swap(max1, max2), max1 = tmp;
            else if (tmp > max2)
                max2 = tmp;
        }
    dp[u][1] = dp[u][0] + max1;
    for (int i = head[u]; i != -1; i = edges[i].nxt)
        if (edges[i].to != fa)
        {
            g[u][0].push_back(make_pair(dp[u][0] - max(dp[edges[i].to][0], dp[edges[i].to][1] + edges[i].weight), 0));
            ll tmp = dp[edges[i].to][0] + edges[i].weight - max(dp[edges[i].to][0], dp[edges[i].to][1] + upweight[edges[i].to]);
            if (tmp == max1)
                g[u][1].push_back(make_pair(g[u][0].back().first + max2, max2));
            else
                g[u][1].push_back(make_pair(g[u][0].back().first + max1, max1));
        }
}

void update(int u, int fa)
{
    for (int i = head[u], ptr = 0; i != -1; i = edges[i].nxt)
        if (edges[i].to != fa)
        {
            dp[u][0] = g[u][0][ptr].first, dp[u][1] = g[u][1][ptr].first;
            if (fa)
            {
                dp[u][0] += max(dp[fa][1] + upweight[u], dp[fa][0]);
                dp[u][1] = dp[u][0] + max(g[u][1][ptr].second, dp[fa][0] + upweight[u] - max(dp[fa][0], dp[fa][1] + upweight[u]));
            }
            f[edges[i].to] = dp[edges[i].to][0] + max(dp[u][0], dp[u][1] + upweight[edges[i].to]);
            update(edges[i].to, u), ptr++;
        }
}

int main()
{
    memset(head, -1, sizeof(head));
    scanf("%d", &n);
    if (n == 1 || n == 2)
        puts("0"), exit(0);
    for (int i = 1, u, v, w; i <= n - 1; i++)
        scanf("%d%d%d", &u, &v, &w), addpath(u, v, w), addpath(v, u, w);
    calc(1, 0), update(1, 0);
    ll gans = 0;
    for (int i = 1; i <= n; i++)
        gans = max(gans, f[i]);
    printf("%lld\n", gans);
    return 0;
}