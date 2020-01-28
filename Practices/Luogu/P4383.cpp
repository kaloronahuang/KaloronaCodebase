// P4383.cpp
#include <bits/stdc++.h>

using namespace std;

const int MAX_N = 3e5 + 200;

typedef long long ll;

int n, limit, head[MAX_N], current;
ll weight_tot;

struct edge
{
    int to, nxt, weight;
} edges[MAX_N << 1];

struct ray
{
    ll x, y;
    bool operator<(const ray &rhs) const { return x < rhs.x || (x == rhs.x && y > rhs.y); }
    ray operator+(const ray &rhs) { return ray{x + rhs.x, y + rhs.y}; }
    ray operator+(const ll &rhs) { return ray{x + rhs, y}; }
} dp[MAX_N][3];

void addpath(int src, int dst, int weight)
{
    edges[current].to = dst, edges[current].nxt = head[src];
    edges[current].weight = weight, head[src] = current++;
}

ray util(ray curt, ll coeff) { return ray{curt.x - coeff, curt.y + 1}; }

void dfs(int u, int fa, ll coeff)
{
    dp[u][2] = max(dp[u][2], ray{-coeff, 1});
    for (int i = head[u]; i != -1; i = edges[i].nxt)
        if (edges[i].to != fa)
        {
            dfs(edges[i].to, u, coeff);
            dp[u][2] = max(dp[u][2] + dp[edges[i].to][0], util(dp[edges[i].to][1] + dp[u][1] + edges[i].weight, coeff));
            dp[u][1] = max(dp[u][1] + dp[edges[i].to][0], dp[u][0] + dp[edges[i].to][1] + edges[i].weight);
            dp[u][0] = dp[u][0] + dp[edges[i].to][0];
        }
    dp[u][0] = max(dp[u][0], max(util(dp[u][1], coeff), dp[u][2]));
}

int check(ll coeff)
{
    memset(dp, 0, sizeof(dp)), dfs(1, 0, coeff);
    return dp[1][0].y;
}

int main()
{
    memset(head, -1, sizeof(head));
    scanf("%d%d", &n, &limit), limit++;
    for (int i = 1, u, v, w; i <= n - 1; i++)
        scanf("%d%d%d", &u, &v, &w), addpath(u, v, w), addpath(v, u, w), weight_tot += abs(w);
    ll l = -weight_tot, r = weight_tot, res;
    while (l <= r)
    {
        ll mid = (l + r) >> 1;
        if (check(mid) <= limit)
            r = mid - 1, res = mid;
        else
            l = mid + 1;
    }
    check(res);
    printf("%lld\n", dp[1][0].x + l * limit);
    return 0;
}