// B_ext.cpp
#include <bits/stdc++.h>
#define lowbit(x) (x & -x);
#define ll long long
#define pr pair<ll, ll>
using namespace std;
const int MAX_N = 202000;
int n, x_1, x_2, y_1, y_2, head[MAX_N], current, indeg[MAX_N], dp[MAX_N];
vector<int> vec;
struct edge
{
    int to, nxt;
} edges[(2020) * (2020 - 1) / 2];
void addpath(int src, int dst)
{
    edges[current].to = dst, edges[current].nxt = head[src];
    head[src] = current++;
}
pr weaks[MAX_N];
bool validiate(pr back, pr front)
{
    int dotaX = front.first - back.first, dotaY = front.second - back.second;
    if (dotaX < 0 || dotaY < 0)
        return false;
    double curt = (1.0 * dotaY) / (1.0 * dotaX);
    double lbound = (1.0 * x_1) / (1.0 * y_1), ubound = (1.0 * x_2) / (1.0 * y_2);
    if (lbound > ubound)
        swap(lbound, ubound);
    if (curt <= ubound && curt >= lbound)
        return true;
    return false;
}
void print()
{
    for (int pt = 1; pt <= n; pt++)
        for (int i = head[pt]; i != -1; i = edges[i].nxt)
            printf("%d %d\n", pt, edges[i].to);
}
int dfs(int u)
{
    if (dp[u] != -1)
        return dp[u];
    int ans = 0;
    for (int i = u; i <= n; i++)
        if (u != i && validiate(weaks[u], weaks[i]))
            ans = max(ans, dfs(i));
    dp[u] = ans + 1;
    return dp[u];
}
int main()
{
    freopen("shield.in", "r", stdin);
    freopen("shield.out", "w", stdout);
    memset(head, -1, sizeof(head));
    scanf("%d%d%d%d%d", &n, &x_1, &y_1, &x_2, &y_2);
    for (int i = 1; i <= n; i++)
        scanf("%lld%lld", &weaks[i].first, &weaks[i].second), vec.push_back(weaks[i].first), vec.push_back(weaks[i].second);
    if (x_1 == 1 && y_1 == 0 && x_2 == 0 && y_2 == 1)
    {
        memset(dp, -1, sizeof(dp));
        sort(vec.begin(), vec.end()), vec.erase(unique(vec.begin(), vec.end()), vec.end());
        for (int i = 1; i <= n; i++)
            weaks[i].first = lower_bound(vec.begin(), vec.end(), weaks[i].first) - vec.begin() + 1,
            weaks[i].second = lower_bound(vec.begin(), vec.end(), weaks[i].second) - vec.begin() + 1;
        sort(weaks + 1, weaks + 1 + n);
        int ans = 0;
        for (int i = 1; i <= n; i++)
            ans = max(ans, dfs(1));
        printf("%d", ans);
        return 0;
    }
    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= n; j++)
            if (i != j && weaks[i] < weaks[j] && validiate(weaks[i], weaks[j]))
                addpath(i, j), indeg[j]++;
    queue<int> q;
    for (int i = 1; i <= n; i++)
        if (indeg[i] == 0)
            q.push(i), dp[i] = 1;
    int answer = 0;
    while (!q.empty())
    {
        int curt = q.front();
        q.pop();
        answer = max(answer, dp[curt]);
        for (int i = head[curt]; i != -1; i = edges[i].nxt)
            if (dp[edges[i].to] < dp[curt] + 1)
                dp[edges[i].to] = dp[curt] + 1, q.push(edges[i].to);
    }
    printf("%d", answer);
    return 0;
}